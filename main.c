#include <time.h>
#include "control_functions.h"
#include "menu.h"
#include "drawing_boards.h"
#include "history.h"

bool set_x_y(char p[3],int *x,int *y){
    if(p[0]<97||p[0]>106||p[1]<49||p[1]>57)
        return false;

    *y = p[0]-97;
    if(p[2]==48)*x=9;
    else *x=p[1]-49;

    return true;

}
void get_field(int x,int y,char p[3],char s[]){
    menu_one_line(x,y,7,s);
    int mod_x=strlen(s)+x;
    for(int k=0;k<3;k++){
        setcursorpos(mod_x+k,y);
        p[k] = getch();

        printf("%c",p[k]);
        if(p[k]=='\r'){
            break;
        }

        if(p[k]==8){
            setcursorpos(mod_x+k-1,y);
            printf(" ");
            if(k>0)k-=2;
            else k--;
        }
    }
}
void declare(char b[10][10]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            b[i][j]=' ';
        }
    }
}
void declare_bot_ship_counter(int ships[4],int bot_ship_count[2][4][2]){
    for(int i=0;i<2;i++){
        for(int j=0;j<4;j++){
            bot_ship_count[i][j][0]=ships[j];
            bot_ship_count[i][j][1]=0;
        }
    }
}

void save_statek(char b[10][10],int s,int r,int x,int y){
    char c='#';
    char e=(c==' '?' ':'#');
    char d=(c==' '?' ':'a');
    for(int i=0;i<s;i++){
        if(r==0){
            b[x][y+i]=e;
            if(x<9)b[x+1][y+i]=d;
            if(x>0)b[x-1][y+i]=d;
            for(int j=0;j<((x<9&&x>0)?3:2);j++){
                if(y>0)b[x+j-1+(x<1?1:0)][y-1]=d;
                if(y+s<10)b[x+j-1+(x<1?1:0)][y+s]=d;
            }
        }
        else {
            b[x+i][y]=e;
            if(y<9)b[x+i][y+1]=d;
            if(y>0)b[x+i][y-1]=d;
            for(int j=0;j<((y<9&&y>0)?3:2);j++){
                if(x>0)b[x-1][y+j-1+(y<1?1:0)]=d;
                if(x+s<10)b[x+s][y+j-1+(y<1?1:0)]=d;
            }
        }
    }
}
bool check(char b[10][10],int s,int r,int x,int y){
    if(x<0||(r==0?x:x+s-1)>9||y<0||(r==0?y+s-1:y)>9){
            return false;
    }
    else{
        for(int i=0;i<s;i++){
            if(r==0){
                if(b[x][y+i]!=' '){
                    return false;
                }
            }
            else {
                if(b[x+i][y]!=' '){
                    return false;
                }
            }
        }
    }
    return true;
}
bool move_statek(char b[10][10],char b2[10][10],int s,int *r,int *x,int *y,char c){
    bool correct=true;
    bool correct2=true;
    int tmpx=*x,tmpy=*y,tmpr=*r;
    if(c=='w')tmpx-=1;
    else if(c=='a')tmpy-=1;
    else if(c=='s')tmpx+=1;
    else if(c=='d')tmpy+=1;
    else if(c=='r')tmpr=((*r)==0?1:0);

    correct = check(b,s,tmpr,tmpx,tmpy);

    if(correct){
        if(c=='w')(*x)-=1;
        else if(c=='a')(*y)-=1;
        else if(c=='s')(*x)+=1;
        else if(c=='d')(*y)+=1;
        else if(c=='r')(*r)=((*r)==0?1:0);

    }else{
        correct2 = check(b,s,*r,*x,*y);
    }
    if(correct2)save_statek(b2,s,*r,*x,*y);
    return correct;
}

void set_fire(char p[3],char b[2][10][10], int *fire,int player,int mode,bool bot_random_shot,struct _2wayList **moves){
    bool correct_position = true;
    int x,y;
    correct_position = set_x_y(p,&x,&y);

    player=(player==0?1:0);

    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(bot_random_shot&&b[player][i][j]=='b')b[player][i][j]='X';
            if(b[player][i][j]=='c')b[player][i][j]='O';
        }
    }

    if(correct_position){
        if(b[player][x][y]=='#'){
            if(mode==3||mode==4||mode==2&&player==0) b[player][x][y]='b';
            else b[player][x][y]='X';
            *fire=1;
        }
        else if(b[player][x][y]=='X'||b[player][x][y]=='O'||b[player][x][y]=='b'){
            *fire=4;
        }
        else if(b[player][x][y]=='a'&&(mode==3||mode==2&&player==0)){
            *fire=2;
            for(int i=-1;i<2;i++){
                for(int j=-1;j<2;j++){
                    if(b[player][x+i][y+j]=='X'){
                        *fire=5;
                    }
                }
            }
        }
        else *fire=2;

        if(*fire==2){
            if(mode==3||mode==4||mode==2&&player==0){
                b[player][x][y]='c';
            }
            else b[player][x][y]='O';
        }

    }
    else *fire=3;

    player=(player==0?1:0);
    if((*fire==1||*fire==2)&&mode!=4){
        char s[6];
        s[0]=(char)(player+48);
        s[1]=p[0];
        s[2]=p[1];
        s[3]=p[2]=='0'?'0':' ';
        s[4]=(char)(bot_random_shot+48);
        s[5]='\0';
        push_back(moves,s);
    }
}
void bot_move(char boa[2][10][10],int *fire,int player,int mode,int bot_data[8],int bot_ship_count[4][2],enum game_state gstate,struct _2wayList **moves){
    if(gstate==end) return;

    char p[3];
    bool random1;
    int random=0;
    int m=10;

    int *xb,*yb,*xbm,*ybm,*xb_org,*yb_org,*lob,*lb1;

    xb=&bot_data[0];
    yb=&bot_data[1];
    xbm=&bot_data[2];
    ybm=&bot_data[3];
    xb_org=&bot_data[4];
    yb_org=&bot_data[5];
    lob=&bot_data[6];
    lb1=&bot_data[7];


    for (int i=0;i<4;i++){
        if(bot_ship_count[i][0]<=m&&bot_ship_count[i][1]<i+1){
            m=bot_ship_count[i][0];
            break;
        }
    }


    do{
        int xbn,ybn;
        random1 = false;

        if((*xb!=-1||*yb!=-1)&&*lob!=4&&*lb1<m){
            if(*xbm==0&&*ybm==0)
                *xbm=-1;

            xbn = *xb + *xbm;
            ybn = *yb + *ybm;
        }else{
            random1 = true;
            random++;
            xbn = rand()%10+1;
            ybn = rand()%10+97;
            *xb_org = xbn;
            *yb_org = ybn;
            *xb=-1;
            *yb=-1;
            *xbm=0;
            *ybm=0;
            *lob=0;
            if(*lb1>0){
                for(int i=0;i<4;i++){
                    if(bot_ship_count[i][0]==*lb1)bot_ship_count[i][1]++;
                }
            }
            *lb1=0;
        }

        p[0] = ybn;
        if(xbn<10){
            p[1]=xbn+48;
            p[2]=' ';
        }
        else{
            p[1]=49;
            p[2]=48;
        }
        set_fire(p,boa,fire,player,mode,random1,moves);

        if(*fire==1){
            *lob=0;
            *xb=xbn;
            *yb=ybn;
            (*lb1)++;
        }
        else if(!random1&&(*fire==2||*fire==3||*fire==4)&&*lb1>1)
        {
            *xb=*xb_org;
            *yb=*yb_org;
            (*lob)++;
            if(*xbm==0){
                *ybm=(*ybm==-1?1:-1);
            }else{
                *xbm=(*xbm==-1?1:-1);
            }
        }
        else if(*lb1<2){
            (*lob)++;
            if(*xbm==-1){
                *xbm=1;
                *ybm=0;
            }
            else if(*xbm==1){
                *xbm=0;
                *ybm=-1;
            }
            else if(*ybm==-1){
                *xbm=0;
                *ybm=1;
            }
            else if(*ybm==1){
                *xbm=0;
                *ybm=0;
            }
        }
        else{
            (*lob)++;
            if(*xbm==0){
                *ybm=(*ybm==-1?1:-1);
            }else{
                *xbm=(*xbm==-1?1:-1);
            }
        }
    }while(*fire==3||*fire==4||*fire==5);
}


int main()
{
    //test_list();/*
    system("chcp 65001");
    SetConsoleTitle(" Game of Ships");
    srand(time(0));
    char save_folder[20]=".\\saves";
    check_exist_dir(save_folder);

    enum game_state gstate = start;
    int mode;
    display_res(&display_x,&display_y);
    HWND hwnd = GetConsoleWindow();

    struct window_data win_data;
    win_data.hwnd=&hwnd;

    struct _2wayList *saved_boards = NULL;
    struct _2wayList *saved_moves = NULL;
    struct _2wayList *moves = NULL;
    struct _2wayList *boards = NULL;

    while(true){
        gstate=start;
        pthread_t thread_id;

        change_size(&win_data,800,950);
        pthread_create(&thread_id, NULL,size_control, &win_data);

        mode = main_menu()-48;

        pthread_cancel(thread_id);
        pthread_join(thread_id,NULL);

        system("cls");

        char board[2][10][10];
        char tmp_b[10][10];

        declare(board[0]);
        declare(board[1]);
        declare(tmp_b);

        int ships[4]={4,3,2,1};
        int player=1;

        char c=' ',p[3];
        bool correct_position;
        char save_name[100];
        FILE *save=NULL;


        int x=0,y=0,r=0,i=0,j=0;
        int ship_counter=10;
        if(mode==4){
            change_size(&win_data,600,1000);
            pthread_create(&thread_id, NULL,size_control, &win_data);

            struct _2wayList *saves=NULL;
            int count_saves=0;
            int file_num = 0;

            int menu_x=8,menu_y=4;

            get_dir(save_folder,&saves,&count_saves);
            saves = get_first(saves);

            clear_board(menu_x+32,menu_y+1);
            clear_board(menu_x+72,menu_y+1);

            if(count_list(saves)==0){
                setcursorpos(menu_x-2,menu_y);
                color(11);
                printf(">");
                color(7);
                for(int n=0;n<5;n++){
                    setcursorpos(menu_x,menu_y+n);
                    printf("%*c", 30,' ');
                }

                setcursorpos(menu_x,menu_y);
                printf("No saved games!!!");
                Sleep(1000);
                continue;
            }
            while(true){
                saves = get_by_index(saves,file_num);
                strcpy(save_name,save_folder);
                strcat(save_name,"\\");
                strcat(save_name,saves->s);

                save = fopen(save_name,"r");
                if (save == NULL)
                {
                    perror("Save file is corrupted or doesn't exists!!!");
                    return 1;
                }

                declare(board[0]);
                declare(board[1]);
                clear(&boards);
                get_ships_from_file(save,&boards,board,ships);

                fclose(save);
                save=NULL;

                print_board_loading_file(menu_x,menu_y,board,&saves);
                saves = get_by_index(saves,file_num);

                c = getch();
                pthread_mutex_lock(&mutex);
                if(status){
                    system("cls");
                    clear_board(menu_x+32,menu_y+1);
                    clear_board(menu_x+72,menu_y+1);
                    print_board_loading_file(menu_x,menu_y,board,&saves);
                    saves = get_by_index(saves,file_num);
                    status = 0;
                }
                pthread_mutex_unlock(&mutex);

                if(c=='w'&&file_num>0)file_num--;
                else if(c=='s'&&file_num<count_saves)file_num++;
                else if(c=='c'||c==27)break;
            }
            if(c==27)continue;

            save = fopen(save_name,"r");
            if (save == NULL)
            {
                perror("Save file is corrupted or doesn't exists!!!");
                return 1;
            }

            for(int l=0;l<140;l++) c = fgetc(save);
            char s[8];
            clear(&moves);
            while(true){
                for (int k=0;k<6;k++){
                    c = fgetc(save);
                    if(c==EOF)break;
                    if(c==10)c=' ';
                    s[k]=c;
                }
                s[6] = '\0';
                if(c==EOF)break;
                push_back(&moves,s);
            }
            fclose(save);
        }
        else{
            int board_x=33,board_y=4;
            int mod_x=4,mod_y=0;
            change_size(&win_data,500,800);
            pthread_create(&thread_id, NULL,size_control, &win_data);
            clear_board(board_x,board_y);
            for (int l=0;l<2;l++){
                player=(player==1?0:1);
                x=0,y=0,r=0,i=0,j=0;
                ship_counter=10;
                correct_position=true;

                while(true){
                    if(ship_counter==0)break;
                    print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,0,correct_position);

                    c=getch();
                    pthread_mutex_lock(&mutex);
                    if(status){
                        system("cls");
                        clear_board(board_x,board_y);
                        print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,0,correct_position);
                        status = 0;
                    }
                    pthread_mutex_unlock(&mutex);

                    if(c=='n'){
                        if(correct_position)mod_y=16;
                        else mod_y=17;

                        char s[] = "Type field where you want to write the ship: ";

                        get_field( mod_x,board_y+mod_y,p,s);
                        pthread_mutex_lock(&mutex);
                        if(status){
                            system("cls");
                            clear_board(board_x,board_y);
                            print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,0,correct_position);
                            menu_one_line(mod_x,board_y+mod_y,7,s);
                            status = 0;
                        }
                        pthread_mutex_unlock(&mutex);

                        if(p[0]=='\r'||p[1]=='\r')correct_position = false;
                        else correct_position = set_x_y(p,&x,&y);

                        if(!correct_position)continue;

                        r=0;
                        char r_p;
                        char s2[100] = "Press 'r' if you want your ship to be writen vertical if not press enter:";
                        menu_one_line(mod_x,board_y+mod_y+1,7,s2);
                        r_p = getch();
                        pthread_mutex_lock(&mutex);
                        if(status){
                            system("cls");
                            clear_board(board_x,board_y);
                            print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,0,correct_position);
                            menu_one_line(mod_x,board_y+mod_y,7,s);
                            menu_one_line(mod_x,board_y+mod_y+1,7,s2);
                            status = 0;
                        }
                        pthread_mutex_unlock(&mutex);
                        if(r_p=='r')r=1;

                        if(correct_position){
                            if(j>i){i++;j=1;}
                            else {j++;}

                            correct_position=move_statek(board[player],tmp_b,ships[i],&r,&x,&y,'f');

                            if(correct_position){

                                while(true){
                                    print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,1,correct_position);
                                    c = getch();
                                    pthread_mutex_lock(&mutex);
                                    if(status){
                                        system("cls");
                                        clear_board(board_x,board_y);
                                        print_board_set_ships(board_x,board_y,board[player],tmp_b,ships,ship_counter,mode,player,1,correct_position);
                                        status = 0;
                                    }
                                    pthread_mutex_unlock(&mutex);

                                    if(c=='v'){
                                        declare(tmp_b);
                                        j--;
                                        ship_counter++;
                                        break;
                                    }
                                    else if(c=='w'||c=='a'||c=='s'||c=='d'||c=='r'){
                                        declare(tmp_b);
                                        correct_position=move_statek(board[player],tmp_b,ships[i],&r,&x,&y,c);
                                    }
                                    else if(c=='z'){
                                        save_statek(board[player],ships[i],r,x,y);
                                        char s[7];
                                        s[0]='n';
                                        s[1]=(char)(y+97);
                                        s[2]=(char)((x==9?0:x)+49);
                                        s[3]=(x==9?'0':' ');
                                        s[4]=(r==1?'r':' ');
                                        s[5]='z';
                                        s[6]='\0';
                                        push_back(&saved_boards,s);
                                        declare(tmp_b);
                                        break;
                                    }
                                }
                                ship_counter--;
                            }else{
                                if(j==1)i--;
                                else j--;
                            }
                        }
                    }
                    if(c=='o'){
                        i=0;
                        j=0;
                        correct_position = true;
                        ship_counter=10;
                        declare(board[player]);
                        declare(tmp_b);
                        clear_board(board_x,board_y);
                        if(player==0)clear(&saved_boards);
                        else{
                            for(int n=0;n<10;n++){
                                delete_index(&saved_boards,10);
                            }
                        }
                    }
                    if(c==27) break;
                }
                if(c==27) break;
            }
        }

        pthread_cancel(thread_id);
        pthread_join(thread_id,NULL);
        if(c==27){
            clear(&saved_boards);
            system("cls");
            continue;
        }

        change_size(&win_data,800,800);
        pthread_create(&thread_id, NULL,size_control, &win_data);

        player=0;
        int bot_data[2][8]={{-1,-1,0,0,0,0,-1,-1},{-1,-1,0,0,0,0,-1,-1}};
        int bot_ship_count[2][4][2];
        int fire=0;

        int board_x1=17,board_x2=board_x1+40,board_y1=10,board_y2=board_y1;
        declare_bot_ship_counter(ships,bot_ship_count);

        pthread_t thread_for_getch;
        bool random_move = false;

        if(mode<3){
            system("cls");
            menu_one_line_arg(board_x1+3,board_y1-5,7,"Give computer to player no.:",player+1);
            system("pause");
        }
        system("cls");
        clear_board(board_x1,board_y1);
        clear_board(board_x2,board_y2);

        int max_moves=0,current_move=1;
        if(mode==4){
            moves = get_first(moves);
            max_moves = count_list(moves);
        }

        while(true){
            print_board_game(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);

            if(fire==1){
                setcursorpos(board_x1+2,board_y1+11);
                printf("%*c", 40,' ');
                Sleep(200);
                menu_one_line(board_x1+2,board_y1+11,12,"Hit!!!");

                if(mode==3||mode==4)Sleep(300);
                else if(mode==2&&player==1)Sleep(1300);
            }
            else if(fire==2){
                fire=0;

                setcursorpos(board_x1+2,board_y1+11);
                printf("%*c", 40,' ');
                Sleep(200);
                menu_one_line(board_x1+2,board_y1+11,11,"Miss!!!");
                player=(player==1?0:1);

                if(mode==3||mode==4){
                    Sleep(300);
                }else if(mode==2){
                    Sleep(1300);
                }
                else{
                    Sleep(1300);
                    system("cls");
                    menu_one_line_arg(board_x1+3,board_y1-5,7,"Give computer to player no.:",player+1);
                    system("pause");
                    system("cls");
                    clear_board(board_x1,board_y1);
                    clear_board(board_x2,board_y2);
                }
                if(mode!=4){
                    setcursorpos(board_x1+2,board_y1+11);
                    printf("%*c", 40,' ');
                }
                continue;

            }
            else if(fire==4&&mode!=4){
                menu_one_line(board_x1+2,board_y1+11,124,"You've already fired in that place!!!");
            }
            else if(fire==3&&mode!=4){
                menu_one_line(board_x1+2,board_y1+11,124,"Incorrect field!!!");
            }

            if(mode == 4){
                player=moves->s[0]-48;
                p[0]=moves->s[1];
                p[1]=moves->s[2];
                p[2]=moves->s[3];
                random_move = moves->s[5]-48;
                set_fire(p,board,&fire,player,mode,random_move,&saved_moves);

                if(c=='c'){
                    int st=0;

                    moves = get_next(moves);
                    if(current_move<max_moves)current_move++;

                    pthread_mutex_lock(&mutex);
                    pthread_mutex_unlock(&mutex);

                    pthread_mutex_lock(&mutex_getch);
                    if(status_getch==0){
                        st=1;
                        c='s';
                    }
                    pthread_mutex_unlock(&mutex_getch);
                    if(st==1)pthread_join(thread_for_getch,NULL);
                }
                else{
                    do{
                        c=getch();
                        clean_up_draw(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);
                    }while(c!='a'&&c!='d'&&c!='c');

                    if(c=='c'){
                        status_getch=1;
                        pthread_create(&thread_for_getch,NULL,thread_getch,NULL);
                    }
                    else if(c=='a'){
                        moves = get_next(moves);
                        if(current_move<max_moves)current_move++;
                    }
                    else if(c=='d'){
                        struct _2wayList *current;
                        current = moves;
                        moves = get_first(moves);

                        declare(board[0]);
                        declare(board[1]);

                        boards = get_first(boards);
                        for (int l=0;l<2;l++){
                            x=0,y=0,r=0,i=0,j=0;
                            for(ship_counter=10;ship_counter>0;ship_counter--){
                                if(j>i){i++;j=1;}
                                else {j++;}

                                p[0]=boards->s[1];
                                p[1]=boards->s[2];
                                p[2]=boards->s[3];
                                r=(boards->s[4]=='r'?1:0);
                                set_x_y(p,&x,&y);
                                save_statek(board[l],ships[i],r,x,y);
                                boards = get_next(boards);
                            }
                        }

                        while(moves!=current){
                            player=moves->s[0]-48;
                            p[0]=moves->s[1];
                            p[1]=moves->s[2];
                            p[2]=moves->s[3];
                            random_move = moves->s[5]-48;
                            set_fire(p,board,&fire,player,mode,random_move,&saved_moves);
                            moves = get_next(moves);
                        }

                        moves = get_prev(current);
                        if(current_move>1)current_move--;
                        else player=0;
                    }
                }
            }
            else if(player==1&&mode==2||mode==3){
                bot_move(board,&fire,player,mode,bot_data[player],bot_ship_count[player],gstate,&saved_moves);
                pthread_mutex_lock(&mutex);
                pthread_mutex_unlock(&mutex);
            }else{
                char s2[] ="Type field where you want to fire: ";

                get_field(board_x1+2,board_y1+12,p,s2);
                clean_up_draw(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);

                if(p[0]=='\r'||p[1]=='\r'){fire=3;continue;}
                set_fire(p,board,&fire,player,mode,false,&saved_moves);
            }

            int licznik=20;

            for(int i=0;i<10;i++){
                for(int j=0;j<10;j++){
                    if(board[player==0?1:0][i][j]=='X'||board[player==0?1:0][i][j]=='b')licznik--;
                }
            }
            if(licznik==0){
                gstate = end;
                break;
            }

        }

        system("cls");
        clear_board(board_x1,board_y1);
        clear_board(board_x2,board_y2);
        print_board_game(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);
        while(true){
            c=getch();
            clean_up_draw(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);

            if(c==27)break;
            else if(c=='z'){
                char text[100];
                char text2[100]=".\\saves\\";
                time_t now = time(NULL);
                struct tm *t = localtime(&now);

                strftime(text, sizeof(text)-1, "%d_%m_%Y__%H_%M", t);
                strcat(text2,text);
                strcat(text2,".txt");
                save_to_file(text2,saved_boards,"w");
                save_to_file(text2,saved_moves,"a");
                break;
            }
        }
        pthread_cancel(thread_id);
        pthread_join(thread_id,NULL);
        clear(&saved_boards);
        clear(&saved_moves);
        clear(&boards);
        clear(&moves);
    }

    return 0;
}
