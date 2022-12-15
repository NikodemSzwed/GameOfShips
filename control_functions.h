#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <windows.h>

pthread_mutex_t mutex;
pthread_mutex_t mutex_getch;
int status,status_getch;
char thread_char;
int display_x,display_y;

struct window_data{
    HWND *hwnd;
    int width;
    int height;
    int pos_x;
    int pos_y;
};

void color(int);
void display_res(int*, int*);
void setcursorpos(int,int);
void setcursorpos2(COORD cord);
void *size_control(struct window_data*);
void change_size(struct window_data*,int ,int);
void *thread_getch();
char** allocate_string_array(int);
