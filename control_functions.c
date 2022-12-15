#include "control_functions.h"

COORD get_cur_pos()
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ), &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
}
void color(int x){
    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleTextAttribute(console, x);
}
void display_res(int *width, int *height) {
    *height = GetSystemMetrics(SM_CYSCREEN);
    *width = GetSystemMetrics(SM_CXSCREEN);
}
void setcursorpos(int x,int y){
    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition( console, cord );
}
void setcursorpos2(COORD cord){
    HANDLE console = GetStdHandle( STD_OUTPUT_HANDLE );
    SetConsoleCursorPosition( console, cord );
}
void *size_control(struct window_data *win_data){

    int width,height;
    RECT rect;
    HWND hwnd2;
    while(true){
        pthread_mutex_lock(&mutex);
        hwnd2 = GetForegroundWindow();
        while((*win_data->hwnd)!=hwnd2){
            hwnd2 = GetForegroundWindow();
            Sleep(500);
        }
        pthread_mutex_unlock(&mutex);

        if(GetWindowRect(*win_data->hwnd, &rect))
        {
          width = rect.right - rect.left;
          height = rect.bottom - rect.top;
        }
        if(width<win_data->width||height<win_data->height){
            pthread_mutex_lock(&mutex);
            status=1;
            SetWindowPos(*win_data->hwnd ,0,win_data->pos_x,win_data->pos_y,win_data->width,win_data->height ,SWP_SHOWWINDOW);
            COORD cord = get_cur_pos();
            setcursorpos(0,0);
            printf(" ");
            setcursorpos2(cord);
            pthread_mutex_unlock(&mutex);
        }
        else{
            pthread_testcancel();
        }
        Sleep(100);

    }

    return;
}
void change_size(struct window_data *win_data,int height,int width){
    win_data->width=width;
    win_data->height=height;
    win_data->pos_x=(display_x-width)/2;
    win_data->pos_y=(display_y-height)/2;
    if( *win_data->hwnd != NULL ){ SetWindowPos(*win_data->hwnd ,0,win_data->pos_x,win_data->pos_y,win_data->width,win_data->height,SWP_SHOWWINDOW); }
}
void *thread_getch(){
    char c;
    c = getch();
    pthread_mutex_lock(&mutex_getch);
    status_getch=0;
    thread_char = c;
    pthread_mutex_unlock(&mutex_getch);
}
char** allocate_string_array(int size){
    char **n;
    n=(char **)malloc(size*sizeof(*n));

    for(int i=0;i<size;i++){
        n[i]=(char *)malloc(100*sizeof(n));
    }
    return n;

}
