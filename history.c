#include "history.h"

void check_exist_dir(char s[]){
    DIR *d;
    d = opendir(s);
    if (d);
    else if (ENOENT == errno){
        char s2[50] = "md ";
        strcat(s2,s);
        system(s2);
    }
}

void get_dir(char s[],struct _2wayList **saves,int *count){
    DIR *d;
    struct dirent *dir;
    d = opendir(s);
    (*count)=0;
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if(strcmp(dir->d_name,".")!=0&&strcmp(dir->d_name,"..")!=0){
                push_back(saves,dir->d_name);
                (*count)++;
            }
        }
        closedir(d);
    }

}
void save_to_file(char file_name[],struct _2wayList* list,char save_mode[]){
    FILE *file = fopen(file_name,save_mode);
    for(list = get_first(list);list!=NULL;list=list->next)
    {
        fprintf(file,"%s\n",list->s);
    }
    fclose(file);
}
void get_ships_from_file(FILE *save,struct _2wayList **boards,char board[2][10][10],int ships[4]){
    char s[8],c,p[3];
    for (int l=0;l<2;l++){
        int x=0,y=0,r=0,i=0,j=0;
        for(int ship_counter=10;ship_counter>0;ship_counter--){
            if(j>i){i++;j=1;}
            else {j++;}

            for (int k=0;k<7;k++){
                c = fgetc(save);
                if(c==10)c=' ';
                s[k] = c;
            }
            s[7] = '\0';

            push_back(boards,s);

            p[0]=s[1];
            p[1]=s[2];
            p[2]=s[3];
            r=(s[4]=='r'?1:0);
            set_x_y(p,&x,&y);
            save_statek(board[l],ships[i],r,x,y);
        }
    }
}
