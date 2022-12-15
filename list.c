#include "list.h"

void test_list(){
    struct _2wayList* list2 = NULL;//initializer_dynamic_arg("qwe");
    push_back(&list2,"123456789");
    push_back(&list2,"cde");
    push_back(&list2,"cde");
    bool suc = push(&list2,"qwe",3);
    //
    print_list(list2);
    printf("suc=%d\n1------\n",suc);

    struct _2wayList* list = NULL;
    //list = initializer_dynamic();
    push_back(&list,"abc");
    push_back(&list,"cde");
    push_back(&list,"gfd");
    push_back(&list,"ert");
    push_back(&list,"bggh");
    push(&list,"qwe",3);
    modify_list_data(list,"tak");
    print_list(list);
    printf("2------\n");

    struct _2wayList *iterator=NULL;
    iterator = get_by_index(list,1);
    printf("%s 1\n",iterator->s);
    iterator = get_by_index(iterator,-1);
    printf("%s -1\n",iterator->s);
    printf("%s 3\n",get_by_index(iterator,3)->s);
    printf("%s 9\n",get_by_index(iterator,9)->s);
    printf("3------\n");
    printf("count: %d\n",count_list(list));


    delete_index(&list,0);
    printf("4------\n");
    if(list==NULL)printf("brak danych\n");
    print_list(list);
    printf("5------\n");
    print_back_list(list);
    printf("6------\n");
    list=get_prev(list);
    printf("%s\n",list->s);
    list=get_next(list);
    printf("%s\n",list->s);
    printf("7------\n");
    clear(&list);
    printf("8------\n");
    if(list==NULL)printf("brak danych\n");
    print_list(list);
    //printf("8------\n");

}

struct _2wayList* initializer_dynamic(){
    struct _2wayList* list = (struct _2wayList*)malloc(sizeof(struct _2wayList));
    strncpy(list->s,"",0);
    list->next=NULL;
    list->prev=NULL;
    return list;
}
struct _2wayList* initializer_dynamic_arg(char s[]){
    struct _2wayList* list = initializer_dynamic();
    modify_list_data(list,s);
    return list;
}
void push_back(struct _2wayList** list, char s[])
{
    struct _2wayList *new_list = initializer_dynamic_arg(s);

    if((*list)!=NULL){
        (*list) = get_last(*list);
        new_list->prev = (*list);
        (*list)->next=new_list;
    }

    (*list) = new_list;
}
bool push(struct _2wayList** list, char s[],int index){
    struct _2wayList *new_list = initializer_dynamic_arg(s);

    if((*list)!=NULL){
        (*list) = get_first(*list);
        if(index<1){
            (*list)->prev=new_list;
            new_list->next = (*list);
            (*list)=new_list;
        }else{
            int i;
            for(i=0;i<index-1;i++){
                if((*list)->next==NULL)break;
                (*list)=(*list)->next;
            }
            if((*list)->next!=NULL)(*list)->next->prev = new_list;
            new_list->prev = (*list);
            new_list->next = (*list)->next;
            (*list)->next = new_list;
            (*list)=new_list;
            if(i!=index-1)return false;
        }
        return true;
    }
    else{
        push_back(list,s);
        if(index==0)return true;
        else return false;
    }
}

void print_list(struct _2wayList* list){
    if(list!=NULL){
        list = get_first(list);
        while(list!=NULL){
            printf("%s\n",list->s);
            list=list->next;
        }
    }

}
void print_back_list(struct _2wayList* list){
    if(list!=NULL){
        list = get_last(list);
        while(list!=NULL){
            printf("%s\n",list->s);
            list=list->prev;
        }
    }

}
bool modify_list_data(struct _2wayList* list,char s[]){
    if(list!=NULL){
        strncpy(list->s,s,24);
    }
    else return false;
    return true;
}
int count_list(struct _2wayList* list){
    int licznik=0;
    if(list==NULL)return 0;
    else{
        licznik=1;
        list = get_first(list);
        while(list->next!=NULL){
            list=list->next;
            licznik++;
        }
        return licznik;
    }
}

struct _2wayList* get_by_index(struct _2wayList* list,int index){
    list = get_first(list);
    for(int i=0;i<index;i++){
        if(list->next==NULL)break;
        list=list->next;
    }
    return list;
}
struct _2wayList* get_next(struct _2wayList* list){
    if(list!=NULL&&list->next!=NULL)list=list->next;
    return list;
}
struct _2wayList* get_prev(struct _2wayList* list){
    if(list!=NULL&&list->prev!=NULL)list=list->prev;
    return list;
}
struct _2wayList* get_first(struct _2wayList* list){
    if(list!=NULL){
        while(list->prev!=NULL){
            list=list->prev;
        }
    }
    return list;
}
struct _2wayList* get_last(struct _2wayList* list){
    if(list!=NULL){
        while(list->next!=NULL){
            list=list->next;
        }
    }
    return list;
}
void delete_last(struct _2wayList** list){
    struct _2wayList* p=NULL;
    if((*list)!=NULL){
        (*list) = get_last(*list);

        if((*list)->prev!=NULL){
            (*list)->prev->next=NULL;
            p=(*list)->prev;
        }
        free(*list);
        *list=p;
    }

}
void delete_index(struct _2wayList** list,int index){
    struct _2wayList* p=NULL;
    if((*list)!=NULL){
        (*list) = get_first(*list);
        if(index<1){
            if((*list)->next!=NULL){
               (*list)->next->prev=NULL;
                p=(*list)->next;
            }
            free(*list);
            *list=p;
        }else{
            for(int i=0;i<index-1;i++){
                if((*list)->next==NULL)break;
                (*list)=(*list)->next;
            }
            if((*list)->next!=NULL){
                if((*list)->next->next!=NULL){
                    (*list)->next->next->prev=(*list);
                    p=(*list)->next->next;
                }
                free((*list)->next);
                (*list)->next=p;
                if(p!=NULL)(*list)=p;
            }
        }
    }

}
void clear(struct _2wayList** list){
    while((*list)!=NULL){
        delete_last(list);
    }
}
