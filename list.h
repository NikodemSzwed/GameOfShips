#pragma once
#include <stdbool.h>
#include <string.h>

struct _2wayList{
    char s[25];
    struct _2wayList *next;
    struct _2wayList *prev;
};

void test_list();

struct _2wayList* initializer_dynamic();
struct _2wayList* initializer_dynamic_arg(char*);
void push_back(struct _2wayList**, char*);
bool push(struct _2wayList**, char*,int);
void print_list(struct _2wayList*);
void print_back_list(struct _2wayList*);
bool modify_list_data(struct _2wayList*,char*);
int count_list(struct _2wayList*);
struct _2wayList* get_by_index(struct _2wayList*,int);
struct _2wayList* get_next(struct _2wayList*);
struct _2wayList* get_prev(struct _2wayList*);
struct _2wayList* get_first(struct _2wayList*);
struct _2wayList* get_last(struct _2wayList*);
void delete_last(struct _2wayList**);
void delete_index(struct _2wayList**,int);
void clear(struct _2wayList**);
