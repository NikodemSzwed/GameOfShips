#pragma once
#include "control_functions.h"
#include "list.h"

enum game_state{start,end};

void clear_board(int,int);
void print_board_set_ships(int x,int y,char[10][10],char[10][10],int[4],int,int,int,int,bool);
void print_board_game(int x,int y,char[2][10][10],int,int,enum game_state,char*,int,int);
void print_board_loading_file(int,int,char[2][10][10],struct _2wayList **);
void clean_up_draw(int,int,char[2][10][10],int,int,enum game_state,char*,int,int);
