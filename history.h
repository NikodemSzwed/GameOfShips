#pragma once
#include "control_functions.h"
#include "list.h"
#include <dirent.h>

void get_dir(char*,struct _2wayList**,int*);
void check_exist_dir(char*);
void save_to_file(char*,struct _2wayList*,char*);
void get_ships_from_file(FILE*,struct _2wayList**,char[2][10][10],int[4]);
