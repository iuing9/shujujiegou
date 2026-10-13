
#ifndef SET_H
#define SET_H

#define SET_MAX_STR 64
#define SET_MAX_CAP 1024

typedef struct Set Set;

Set *set_create(void);

void set_destroy(Set *s);

void set_clear(Set *s);

int set_add(Set *s, const char *elem);

int set_remove(Set *s, const char *elem);

int set_contains(const Set *s, const char *elem);

int set_size(const Set *s);

Set *set_union(const Set *a, const Set *b);
Set *set_intersect(const Set *a, const Set *b);
Set *set_diff(const Set *a, const Set *b);

int set_subset(const Set *a, const Set *b);

void set_print(const Set *s, const char *name);

#endif
