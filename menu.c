#include "menu.h"

void *main_menu_animation(void *vargp){
    char title[]=
    "  ______                                                      ______        c"
    " /      \\                                                    /      \\       c"
    "/$$$$$$  |  ______   _____  ____    ______          ______  /$$$$$$  |      c"
    "$$ | _$$/  /      \\ /     \\/    \\  /      \\        /      \\ $$ |_ $$/       c"
    "$$ |/    | $$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      /$$$$$$  |$$   |          c"
    "$$ |$$$$ | /    $$ |$$ | $$ | $$ |$$    $$ |      $$ |  $$ |$$$$/           c"
    "$$ \\__$$ |/$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ \\__$$ |$$ |            c"
    "$$    $$/ $$    $$ |$$ | $$ | $$ |$$       |      $$    $$/ $$ |            c"
    " $$$$$$/   $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/  $$/             c"
    "              ______   __        __                                         c"
    "             /      \\ /  |      /  |                                        c"
    "            /$$$$$$  |$$ |____  $$/   ______    _______                     c"
    "            $$ \\__$$/ $$      \\ /  | /      \\  /       |                    c"
    "            $$      \\ $$$$$$$  |$$ |/$$$$$$  |/$$$$$$$/                     c"
    "             $$$$$$  |$$ |  $$ |$$ |$$ |  $$ |$$      \\                     c"
    "            /  \\__$$ |$$ |  $$ |$$ |$$ |__$$ | $$$$$$  |                    c"
    "            $$    $$/ $$ |  $$ |$$ |$$    $$/ /     $$/                     c"
    "             $$$$$$/  $$/   $$/ $$/ $$$$$$$/  $$$$$$$/                      c"
    "                                    $$ |                                    c"
    "                                    $$ |                                    c"
    "                                    $$/                                     c";

    char menu[]=
    "  ╔═╗┬ ┬┌─┐┌─┐┌─┐┌─┐  ┌─┐┌─┐┌┬┐┌─┐  ┌┬┐┌─┐┌┬┐┌─┐c"
    "  ║  ├─┤│ ││ │└─┐├┤   │ ┬├─┤│││├┤   ││││ │ ││├┤ c"
    "  ╚═╝┴ ┴└─┘└─┘└─┘└─┘  └─┘┴ ┴┴ ┴└─┘  ┴ ┴└─┘─┴┘└─┘c"
    "┐   ┌─┐┬  ┌─┐┬ ┬┌─┐┬─┐  ┬  ┬┌─┐  ┌─┐┬  ┌─┐┬ ┬┌─┐┬─┐c"
    "│   ├─┘│  ├─┤└┬┘├┤ ├┬┘  └┐┌┘└─┐  ├─┘│  ├─┤└┬┘├┤ ├┬┘c"
    "┴o  ┴  ┴─┘┴ ┴ ┴ └─┘┴└─   └┘ └─┘  ┴  ┴─┘┴ ┴ ┴ └─┘┴└─c"
    "   ┌─┐   ┌─┐┬  ┌─┐┬ ┬┌─┐┬─┐  ┬  ┬┌─┐  ┌┐ ┌─┐┌┬┐c"
    "   ┌─┘   ├─┘│  ├─┤└┬┘├┤ ├┬┘  └┐┌┘└─┐  ├┴┐│ │ │ c"
    "   └─┘o  ┴  ┴─┘┴ ┴ ┴ └─┘┴└─   └┘ └─┘  └─┘└─┘ ┴ c"
    "       ┌─┐   ┌┐ ┌─┐┌┬┐  ┬  ┬┌─┐  ┌┐ ┌─┐┌┬┐c"
    "        ─┤   ├┴┐│ │ │   └┐┌┘└─┐  ├┴┐│ │ │ c"
    "       └─┘o  └─┘└─┘ ┴    └┘ └─┘  └─┘└─┘ ┴ c"
    "    ┬ ┬   ┌─┐┌─┐┌┬┐┌─┐┌─┐  ┬ ┬┬┌─┐┌┬┐┌─┐┬─┐┬ ┬c"
    "    └─┤   │ ┬├─┤│││├┤ └─┐  ├─┤│└─┐ │ │ │├┬┘└┬┘c"
    "      ┴o  └─┘┴ ┴┴ ┴└─┘└─┘  ┴ ┴┴└─┘ ┴ └─┘┴└─ ┴ c"
    "         ╦ ╦┌─┐┬ ┬┬─┐  ┌─┐┬ ┬┌─┐┬┌─┐┌─┐ c"
    "         ╚╦╝│ ││ │├┬┘  │  ├─┤│ │││  ├┤ oc"
    "          ╩ └─┘└─┘┴└─  └─┘┴ ┴└─┘┴└─┘└─┘oc";


    char *n[2];
    char n1[200]=
    "   __  __   c"
    "  /  |/  |  c"
    " _$$ |$$ |_ c"
    "/ $$  $$   |c"
    "$$$$$$$$$$/ c"
    "/ $$  $$   |c"
    "$$$$$$$$$$/ c"
    "  $$ |$$ |  c"
    "  $$/ $$/   c";
    char n2[200]=
    "  __    __  c"
    " /  |  /  | c"
    " $$ |  $$ | c"
    " $$  \\/$$/  c"
    "  $$  $$<   c"
    "   $$$$  \\  c"
    "  $$ /$$  | c"
    " $$ |  $$ | c"
    " $$/   $$/  c";

    n[0]=&n1;
    n[1]=&n2;

    COORD cord;
    while(true){
        pthread_mutex_lock(&mutex);
        if(status){
            status=0;
            pthread_mutex_unlock(&mutex);
        }
        else pthread_mutex_unlock(&mutex);
        system("cls");
        cord.X = 30;
        cord.Y = 23;

        pthread_mutex_lock(&mutex);
        setcursorpos2(cord);
        for(int j=0;j<strlen(menu);j++){
            if(menu[j]=='c'){
                cord.Y++;
                setcursorpos2(cord);
            }
            else printf("%c",menu[j]);

        }

        cord.X = 24;
        cord.Y = 1;
        setcursorpos2(cord);


        for(int j=0;j<strlen(title);j++){
            if(title[j]=='$')color(6);
            if(title[j]=='c'){
                cord.Y++;
                setcursorpos2(cord);
            }
            else printf("%c",title[j]);
            color(7);
        }
        pthread_mutex_unlock(&mutex);


        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
        int tx[4]={2,2,102,102};
        int ty[4]={1,10,10,1};
        int tz[4]={0,0,0,0};
        int p=0;
        while(true){
            for(int i=0;i<4;i++){
                pthread_mutex_lock(&mutex);
                if(status){
                    pthread_mutex_unlock(&mutex);
                    break;
                }
                else pthread_mutex_unlock(&mutex);
                pthread_testcancel();
                cord.X = tx[i];
                cord.Y = ty[i];

                p=tz[i];
                tz[i]=(tz[i]==0?1:0);

                pthread_mutex_lock(&mutex);
                setcursorpos2(cord);
                for(int j=0;j<strlen(n[p]);j++){
                    if(n[p][j]=='$'&&p==0)color(10);
                    else if(n[p][j]=='$'&&p==1)color(12);
                    if(n[p][j]=='c'){
                        cord.Y++;
                        setcursorpos2(cord);
                    }
                    else printf("%c",n[p][j]);
                    color(7);
                }
                pthread_mutex_unlock(&mutex);

                cord.X = 54;
                cord.Y = 43;
                setcursorpos2(cord);
                Sleep(500);
            }
            pthread_mutex_lock(&mutex);
            if(status){
                pthread_mutex_unlock(&mutex);
                break;
            }
            else pthread_mutex_unlock(&mutex);
        }
    }
}
char main_menu(){

    char c=' ';
    COORD cord;
    cord.X = 54;
    cord.Y = 43;

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, main_menu_animation, NULL);
    while(c!='1'&&c!='2'&&c!='3'&&c!='4'){
        pthread_mutex_lock(&mutex);
        pthread_mutex_unlock(&mutex);
        setcursorpos2(cord);
        c = getch();

    }
    pthread_cancel(thread_id);
    pthread_join(thread_id,NULL);

    return c;
}
void menu(int x,int y,bool com,char **n,int ln,char **en,int len){
    COORD cord;
    cord.X=x+4;
    cord.Y=y+1;
    setcursorpos2(cord);

    for(int i=0;i<ln+4;i++){
        printf("%*c", 97,' ');
        setcursorpos(cord.X,cord.Y+i);
    }

    for(int i=0;i<ln-1;i++){
        setcursorpos2(cord);
        printf("%s",n[i]);
        cord.Y++;

    }
    if(!com){
        color(12);
        for(int i=0;i<len;i++){
            setcursorpos2(cord);
            printf("%s",en[i]);
            cord.Y++;
        }

        color(7);
    }
    setcursorpos2(cord);
    printf("%s",n[ln-1]);
    for(int i=0;i<ln;i++){
        free(n[i]);
    }
    free(n);
    for(int i=0;i<len;i++){
        free(en[i]);
    }
    free(en);

}
void menu1(int x,int y,bool com){
    int com_size = 5, err_com_size=1;
    char **n,**en;
    n=allocate_string_array(com_size);
    en=allocate_string_array(err_com_size);

    strcpy(n[0],"Menu:");
    strcpy(n[1],"1.Press 'n' to add new ship.");
    strcpy(n[2],"2.Press 'o' to reset the board.");
    strcpy(n[3],"3.Press Esc to return to main menu.");
    strcpy(n[4],"Your choice: ");
    strcpy(en[0],"The operation cannot be performed because it is against the rules.");

    menu(x,y,com,n,com_size,en,err_com_size);
}
void menu2(int x,int y,bool com){
    int com_size = 6, err_com_size=1;
    char **n,**en;
    n=allocate_string_array(com_size);
    en=allocate_string_array(err_com_size);

    strcpy(n[0],"Menu:");
    strcpy(n[1],"1.Press 'w','a','s','d' to move your ship up,left,down and right.");
    strcpy(n[2],"2.Press 'r' to rotate the ship.");
    strcpy(n[3],"3.Press 'v' to cancel edition of ship.");
    strcpy(n[4],"4.Press 'z' to save position of ship.");
    strcpy(n[5],"Your choice: ");
    strcpy(en[0],"The operation cannot be performed because it is against the rules.");

    menu(x,y,com,n,com_size,en,err_com_size);
}
void menu3(int x,int y,int mode){
    int com_size = (mode==4?3:4), err_com_size=1;
    char **n,**en;
    n=allocate_string_array(com_size);
    en=allocate_string_array(err_com_size);

    strcpy(n[0],"Menu:");
    strcpy(n[1],"1.Press Esc to return to main menu.");
    if(mode==4){
        strcpy(n[2],"Your choice: ");
    }
    else{
        strcpy(n[2],"2.Press 'z' to save the game and return to main menu.");
        strcpy(n[3],"Your choice: ");
    }
    strcpy(en[0],"no_com");

    menu(x,y,true,n,com_size,en,err_com_size);
}
void menu4(int x,int y){
    int com_size = 4, err_com_size=1;
    char **n,**en;
    n=allocate_string_array(com_size);
    en=allocate_string_array(err_com_size);

    strcpy(n[0],"Menu:");
    strcpy(n[1],"1.Press 'a' or 'd' to see each move manually.");
    strcpy(n[2],"2.Press 'c' to automatically move through entire game.");
    strcpy(n[3],"Your choice: ");
    strcpy(en[0],"no_com");

    menu(x,y,true,n,com_size,en,err_com_size);
}
void menu5(int x,int y){
    int com_size = 5, err_com_size=1;
    char **n,**en;
    n=allocate_string_array(com_size);
    en=allocate_string_array(err_com_size);

    strcpy(n[0],"Menu:");
    strcpy(n[1],"1.Press 'w' or 's' to move through saved games.");
    strcpy(n[2],"2.Press 'c' to see entire game.");
    strcpy(n[3],"1.Press Esc to return to main menu.");
    strcpy(n[4],"Your choice: ");
    strcpy(en[0],"no_com");

    menu(x,y,true,n,com_size,en,err_com_size);
}
void menu_one_line(int x,int y,int colour,char com[]){
    setcursorpos(x,y);
    printf("%*c", 97,' ');
    setcursorpos(x,y);
    color(colour);
    printf("%s",com);
    color(7);
}
void menu_one_line_arg(int x,int y,int colour,char com[],int d){
    setcursorpos(x,y);
    printf("%*c", 97,' ');
    setcursorpos(x,y);
    color(colour);
    printf("%s %d",com,d);
    color(7);
    setcursorpos(x,y+1);
}
