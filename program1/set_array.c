
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Set {
    char *elems[SET_MAX_CAP];
    int   size;
};

static char *str_dup(const char *s) {
    size_t n = strlen(s) + 1;
    char *p = (char *)malloc(n);
    if (p) memcpy(p, s, n);
    return p;
}

Set *set_create(void) {
    return (Set *)calloc(1, sizeof(Set));
}

void set_clear(Set *s) {
    if (!s) return;
    for (int i = 0; i < s->size; i++) {
        free(s->elems[i]);
        s->elems[i] = NULL;
    }
    s->size = 0;
}

void set_destroy(Set *s) {
    set_clear(s);
    free(s);
}

int set_contains(const Set *s, const char *elem) {
    if (!s || !elem) return 0;
    for (int i = 0; i < s->size; i++)
        if (strcmp(s->elems[i], elem) == 0) return 1;
    return 0;
}

int set_add(Set *s, const char *elem) {
    if (!s || !elem) return 0;
    if (set_contains(s, elem)) return 1;
    if (s->size >= SET_MAX_CAP) return 0;
    char *copy = str_dup(elem);
    if (!copy) return 0;
    s->elems[s->size++] = copy;
    return 1;
}

int set_remove(Set *s, const char *elem) {
    if (!s || !elem) return 0;
    for (int i = 0; i < s->size; i++) {
        if (strcmp(s->elems[i], elem) == 0) {
            free(s->elems[i]);
            for (int j = i; j < s->size - 1; j++)
                s->elems[j] = s->elems[j + 1];
            s->elems[--s->size] = NULL;
            return 1;
        }
    }
    return 0;
}

int set_size(const Set *s) {
    return s ? s->size : 0;
}

Set *set_union(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a) for (int i = 0; i < a->size; i++) set_add(r, a->elems[i]);
    if (b) for (int i = 0; i < b->size; i++) set_add(r, b->elems[i]);
    return r;
}

Set *set_intersect(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a && b)
        for (int i = 0; i < a->size; i++)
            if (set_contains(b, a->elems[i]))
                set_add(r, a->elems[i]);
    return r;
}

Set *set_diff(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a)
        for (int i = 0; i < a->size; i++)
            if (!(b && set_contains(b, a->elems[i])))
                set_add(r, a->elems[i]);
    return r;
}

int set_subset(const Set *a, const Set *b) {
    if (!a || a->size == 0) return 1;
    if (!b) return 0;
    for (int i = 0; i < a->size; i++)
        if (!set_contains(b, a->elems[i])) return 0;
    return 1;
}

void set_print(const Set *s, const char *name) {
    printf("  %s = {", name ? name : "set");
    int first = 1;
    if (s)
        for (int i = 0; i < s->size; i++) {
            printf("%s%s", first ? "" : ", ", s->elems[i]);
            first = 0;
        }
    printf("}  size=%d\n", s ? s->size : 0);
}
