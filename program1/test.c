
#include "set.h"
#include <stdio.h>

static int pass = 0, fail = 0;

static void check(int cond, const char *desc) {
    printf("[%s] %s\n", cond ? "PASS" : "FAIL", desc);
    if (cond) pass++; else fail++;
}

int main(void) {
    printf("==================== 集合 ADT 测试 ====================\n");

    Set *A = set_create();
    check(A != NULL, "1. 新建空集 A 成功");
    check(set_size(A) == 0, "1. 空集 size = 0");

    check(!set_contains(A, "apple"), "7. 空集中 apple 不存在");

    set_add(A, "apple");
    set_add(A, "banana");
    set_add(A, "cherry");
    set_add(A, "apple");
    check(set_size(A) == 3, "3. 添加 apple/banana/cherry + 重复 apple => size=3");
    check(set_contains(A, "apple"), "3. apple 在 A 中");
    check(!set_contains(A, "grape"), "3. grape 不在 A 中");

    check(set_remove(A, "banana") == 1, "4. 删除存在的 banana => 1");
    check(set_remove(A, "banana") == 0, "4. 再删 banana => 0 (不存在)");
    check(!set_contains(A, "banana"), "4. banana 删除后不在 A 中");
    check(set_size(A) == 2, "4. 删除后 size=2");

    Set *B = set_create();
    set_add(B, "cherry");
    set_add(B, "banana");
    set_add(B, "grape");
    set_add(B, "date");
    set_print(A, "A");
    set_print(B, "B");

    Set *U = set_union(A, B);
    set_print(U, "A∪B ");
    check(set_size(U) == 5, "5. |A∪B| = 5 (apple, cherry, banana, grape, date)");

    Set *I = set_intersect(A, B);
    set_print(I, "A∩B ");
    check(set_size(I) == 1, "5. |A∩B| = 1 (cherry)");
    check(set_contains(I, "cherry"), "5. A∩B 含 cherry");

    Set *AB = set_diff(A, B);
    set_print(AB, "A-B ");
    check(set_size(AB) == 1, "5. |A-B| = 1");
    check(set_contains(AB, "apple"), "5. A-B 含 apple");

    Set *BA = set_diff(B, A);
    set_print(BA, "B-A ");
    check(set_size(BA) == 3, "5. |B-A| = 3 (差集不对称 A-B ≠ B-A)");
    check(set_contains(BA, "banana") &&
          set_contains(BA, "grape") &&
          set_contains(BA, "date"), "5. B-A 含 banana/grape/date");
    check(!set_contains(BA, "apple"), "5. B-A 不含 apple");

    Set *C = set_create();
    set_add(C, "apple");
    check(set_subset(C, A), "6. {apple} ⊆ A => true");
    check(!set_subset(A, C), "6. A ⊆ {apple} => false");
    check(set_subset(A, A), "6. A ⊆ A => true (自反)");

    Set *empty = set_create();
    check(set_subset(empty, A), "6. 空集 ⊆ A => true");
    check(!set_subset(A, empty), "6. A ⊆ 空集 => false");

    Set *su = set_union(A, A);
    check(set_size(su) == set_size(A), "5. |A∪A| = |A| (幂等)");
    set_destroy(su);
    Set *si = set_intersect(A, A);
    check(set_size(si) == set_size(A), "5. |A∩A| = |A| (幂等)");
    set_destroy(si);

    set_clear(A);
    check(set_size(A) == 0, "2. 清空 A 后 size=0");
    check(!set_contains(A, "apple"), "2. 清空后 apple 不在 A 中");
    set_add(A, "zzz");
    check(set_size(A) == 1, "2. 清空后可继续添加 => size=1");

    Set *U2 = set_union(empty, empty);
    check(set_size(U2) == 0, "5. 空∪空 = 空");
    set_destroy(U2);
    Set *I2 = set_intersect(empty, empty);
    check(set_size(I2) == 0, "5. 空∩空 = 空");
    set_destroy(I2);
    Set *D0 = set_diff(empty, empty);
    check(set_size(D0) == 0, "5. 空-空 = 空");
    set_destroy(D0);

    set_destroy(A); set_destroy(B); set_destroy(C);
    set_destroy(U); set_destroy(I);
    set_destroy(AB); set_destroy(BA); set_destroy(empty);

    printf("\n==================== 测试结果 ====================\n");
    printf("通过: %d   失败: %d\n", pass, fail);
    printf("==================================================\n");
    return fail == 0 ? 0 : 1;
}
