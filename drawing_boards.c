#include "drawing_boards.h"
#include "menu.h"

void clear_board(int x,int y){
    COORD cord;
    cord.X=x;
    cord.Y=y;

    setcursorpos(cord.X-1,cord.Y-1);
    for(int i=0;i<10;i++){
        printf("%3c",65+i);
    }

    for(int i=0;i<10;i++){
        setcursorpos(cord.X-3,cord.Y+i);
        printf("%2d ",i+1);
    }

    for(int i=0;i<10;i++){
        setcursorpos2(cord);
        cord.Y++;
        for(int j=0;j<10;j++){
           printf("[ ]");
        }
    }

}
void draw_board(int x,int y,char b[10][10],int colour,bool set_ships,bool clean){
    COORD cord;
    cord.X=x+1;
    cord.Y=y;
    if(colour!=0)color(colour);
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            setcursorpos2(cord);
            if(colour==0){
                if (b[i][j]=='#')color(10);
                if (b[i][j]=='O')color(11);
                if (b[i][j]=='X')color(12);
                if (b[i][j]=='a')color(12);
                if (b[i][j]=='b')color(5);
                if (b[i][j]=='c')color(6);
            }

            if(!set_ships&&clean)printf(" ");
            else if(b[i][j]=='a')printf(" ");
            else if(b[i][j]=='b')printf("X");
            else if(b[i][j]=='c')printf("O");
            else if(set_ships&&b[i][j]!=' ') printf("%c",b[i][j]);
            else if(b[i][j]!='#'&&b[i][j]!=' ')printf("%c",b[i][j]);
            else if(set_ships&&clean)printf(" ");

            cord.X+=3;
        }
        cord.X-=30;
        cord.Y++;
    }
    color(7);
    setcursorpos2(cord);
}
void draw_available_ships(int x,int y,int s[4],int ship_counter){
    COORD cord;
    cord.X=x;
    cord.Y=y;
    int k=0,l=3;

    for(int i=0;i<=10;i++){
        for(int j=0;j<s[0]+3;j++){
            printf(" ");
        }
        setcursorpos(cord.X,cord.Y+i);
    }

    cord.Y+=ship_counter-1;
    setcursorpos2(cord);
    color(11);
    printf("> ");
    color(10);
    cord.Y-=ship_counter-1;
    cord.X+=2;
    for(int i=0;i<ship_counter;i++){
        setcursorpos2(cord);
        if(k>l){l--;k=1;}
        else {k++;}

        for(int j=0;j<s[0]-s[l];j++)
            printf(" ");
        for(int j=0;j<s[l];j++)
            printf("#");

        cord.Y++;
    }
}


void print_board_set_ships(int x,int y,char b[10][10],char b2[10][10],int s[4],int ship_counter,int mode,int player,int menu,bool com){
    setcursorpos(x-2,y-3);
    if(mode==3||mode==2&&player==1)printf("Setting up ships - Bot no.: %d.",player+1);
    else printf("Setting up ships - Player no.: %d.",player+1);
    draw_available_ships(x+32,y,s,ship_counter);
    draw_board(x,y,b,7,false,true);
    draw_board(x,y,b,10,true,false);
    draw_board(x,y,b2,11,true,false);
    if(menu==0)menu1(0,y+10,com);
    else menu2(0,y+10,com);
}

void print_board_game(int x,int y,char b[2][10][10],int player,int mode,enum game_state gstate,char save_name[],int current_move,int max_moves){
    if(mode==4){
        setcursorpos(x+3,y-7);
        printf("History of game: %s",save_name);
        setcursorpos(x+3,y-6);
        printf("%*c", 50,' ');
        setcursorpos(x+3,y-6);
        printf("Move no.: %d of %d",current_move,max_moves);
    }
    setcursorpos(x+3,y-5);
    printf("%*c", 40,' ');
    setcursorpos(x+3,y-5);
    if(gstate!=end){
        if(mode==3) printf("Bot %d turn.",player+1);
        else if(mode==2&&player==1) printf("Bot turn.");
        else printf("Player %d turn.",player+1);
    }
    else {
        if(mode==3)printf("Bot %d is the winner!!!",player+1);
        else if(mode==2&&player==1)printf("Bot is the winner!!!");
        else printf("Player %d is the winner!!!",player+1);
    }

    setcursorpos(x+5,y-3);
    printf("%*c", 70,' ');
    setcursorpos(x+5,y-3);
    if(mode==4)      printf("Board of Player 1:                       Board of Player 2:");
    else if(mode==3) printf(" Board of Bot 1:                          Board of Bot 2:");
    else if(mode==2) printf("   Your board:                             Board of Bot:");
    else             printf("   Your board:                           Board of player %d:",player==0?2:1);

    if(mode==4){
        draw_board(x,y,b[0],0,true,true);
        draw_board(x+40,y,b[1],0,true,true);
    }
    else if(mode==3){
        draw_board(x,y,b[0],0,true,false);
        draw_board(x+40,y,b[1],0,true,false);
    }
    else if(mode==2){
        draw_board(x,y,b[0],0,true,false);
        draw_board(x+40,y,b[1],0,gstate==end?true:false,false);
    }
    else{
        draw_board(x,y,b[player],0,true,false);
        draw_board(x+40,y,b[player==0?1:0],0,gstate==end?true:false,false);
    }

    if(gstate!=end&&mode==4){
        menu4(x-2,y+12);
    }
    else if(gstate==end){
        menu3(x-2,y+12,mode);
    }
}

void print_board_loading_file(int x,int y,char b[2][10][10],struct _2wayList **saves){
    setcursorpos(x-2,y-2);
    printf("Saved games:");
    setcursorpos(x+30,y-2);
    printf("Preview of boards:");

    setcursorpos(x-2,y);
    color(11);
    printf(">");
    color(7);
    color(12);
    setcursorpos(x+10,y-1);
    if((*saves)->prev!=NULL)printf("v");
    else printf(" ");
    setcursorpos(x+10,y+5);
    if((*saves)->next!=NULL)printf("^");
    else printf(" ");
    color(7);

    for(int n=0;n<5;n++){
        setcursorpos(x,y+n);
        printf("%*c", 30,' ');
    }
    for(int n=0;n<5;n++){
        setcursorpos(x,y+n);
        printf("%s",(*saves)->s);
        if((*saves)->next==NULL)break;
        (*saves) = get_next(*saves);
    }
    draw_board(x+32,y+1,b[0],0,true,true);
    draw_board(x+72,y+1,b[1],0,true,true);

    menu5(x,y+12);
}
void clean_up_draw(int board_x1,int board_y1,char board[2][10][10],int player,int mode,enum game_state gstate,char save_name[],int current_move,int max_moves){
    pthread_mutex_lock(&mutex);
    if(status){
        system("cls");
        clear_board(board_x1,board_y1);
        clear_board(board_x1+40,board_y1);
        print_board_game(board_x1,board_y1,board,player,mode,gstate,save_name,current_move,max_moves);
        status = 0;
    }
    pthread_mutex_unlock(&mutex);
}
