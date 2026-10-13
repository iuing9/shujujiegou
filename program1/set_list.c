
#include "set.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ListNode {
    char            *elem;
    struct ListNode *next;
};

struct Set {
    struct ListNode *head;
    int              size;
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
    struct ListNode *cur = s->head;
    while (cur) {
        struct ListNode *nx = cur->next;
        free(cur->elem);
        free(cur);
        cur = nx;
    }
    s->head = NULL;
    s->size = 0;
}

void set_destroy(Set *s) {
    set_clear(s);
    free(s);
}

int set_contains(const Set *s, const char *elem) {
    if (!s || !elem) return 0;
    for (struct ListNode *c = s->head; c; c = c->next)
        if (strcmp(c->elem, elem) == 0) return 1;
    return 0;
}

int set_add(Set *s, const char *elem) {
    if (!s || !elem) return 0;
    if (set_contains(s, elem)) return 1;
    struct ListNode *node = (struct ListNode *)malloc(sizeof(*node));
    if (!node) return 0;
    node->elem = str_dup(elem);
    if (!node->elem) { free(node); return 0; }
    node->next = s->head;
    s->head = node;
    s->size++;
    return 1;
}

int set_remove(Set *s, const char *elem) {
    if (!s || !elem) return 0;
    struct ListNode *prev = NULL, *cur = s->head;
    while (cur) {
        if (strcmp(cur->elem, elem) == 0) {
            if (prev) prev->next = cur->next;
            else       s->head = cur->next;
            free(cur->elem);
            free(cur);
            s->size--;
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

int set_size(const Set *s) {
    return s ? s->size : 0;
}

Set *set_union(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a) for (struct ListNode *c = a->head; c; c = c->next) set_add(r, c->elem);
    if (b) for (struct ListNode *c = b->head; c; c = c->next) set_add(r, c->elem);
    return r;
}

Set *set_intersect(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a && b)
        for (struct ListNode *c = a->head; c; c = c->next)
            if (set_contains(b, c->elem))
                set_add(r, c->elem);
    return r;
}

Set *set_diff(const Set *a, const Set *b) {
    Set *r = set_create();
    if (!r) return NULL;
    if (a)
        for (struct ListNode *c = a->head; c; c = c->next)
            if (!(b && set_contains(b, c->elem)))
                set_add(r, c->elem);
    return r;
}

int set_subset(const Set *a, const Set *b) {
    if (!a || a->size == 0) return 1;
    if (!b) return 0;
    for (struct ListNode *c = a->head; c; c = c->next)
        if (!set_contains(b, c->elem)) return 0;
    return 1;
}

void set_print(const Set *s, const char *name) {
    printf("  %s = {", name ? name : "set");
    int first = 1;
    if (s)
        for (struct ListNode *c = s->head; c; c = c->next) {
            printf("%s%s", first ? "" : ", ", c->elem);
            first = 0;
        }
    printf("}  size=%d\n", s ? s->size : 0);
}
