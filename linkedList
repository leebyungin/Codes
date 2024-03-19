#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct USERDATA
{
        int age;
        char *name;
        char *phone_number;
}USERDATA;

typedef struct NODE
{
        USERDATA *user;
        struct NODE * next;
        struct NODE * before;
}NODE;

USERDATA* createUserData(const int para_age,const char* para_name,const char* para_num);
int printUser(const USERDATA *const user);
void printUserHeader(void);
int isTheUser(const USERDATA* const user,const USERDATA* const find);
void destroyUser(USERDATA* const user);

NODE * createNode(const USERDATA* const userdata);
NODE * appendNode(NODE *const dest ,NODE *const src);
//NODE * detachNode(NODE *const dest, NODE *const src);
NODE * getNodeTail(NODE *node);
NODE * findNode(const NODE* node,const USERDATA *const find);
NODE * insertNode(NODE *const front, NODE *const back);
NODE * insertList(NODE *const dest, NODE *const src);
void destroyNode(NODE **const node);
int printNodeList(const NODE * const node);

void error_handler(const char* msg);

int main(void)
{
        USERDATA* user1=createUserData(20,"kim","010-1111-2222");
        USERDATA* user2=createUserData(21,"lee","010-1234-5678");
        USERDATA* user3=createUserData(22,"park","010-3333-5555");

        NODE * node1=createNode(user1);
        NODE * node2=createNode(user2);
        NODE * node3=createNode(user3);

        // node1->node2->node3
        appendNode(node1,node2);
        appendNode(node1,node3);
        printNodeList(node1);

        USERDATA* user4=createUserData(30,"anold","011-7777-8888");
        USERDATA* user5=createUserData(31,"andrew","011-8888-9999");

        NODE * node4=createNode(user4);
        NODE * node5=createNode(user5);

        // node4->node5
        appendNode(node4,node5);
        printNodeList(node4);

        // node1->node4->node5->node2->node3
        insertList(node1,node4);
        printf("print list(5)\n");
        printNodeList(node1);

        // node5->node2->node3
        printNodeList(findNode(node1,user5));

        // node1->node5->node2->node3
        printf("destroy anold\n");
        destroyNode(&node4);
        printNodeList(node1);

        printf("destroy lee\n");
        destroyNode(&node2);
        printNodeList(node1);
        printf("destroy park\n");
        destroyNode(&node3);
        printNodeList(node1);
        printf("destroy andrew\n");
        destroyNode(&node5);
        printNodeList(node1);
        printf("destroy kim\n");
        destroyNode(&node1);
        printNodeList(node1);
}

/* 구조체 참조용
   typedef struct USERDATA
   {
   int age;
   char *name;
   char *phone_number;
   }USERDATA;
 */

int isTheUser(const USERDATA* const user,const USERDATA* const find)
{
        if(user->age==find->age)
                if(!strcmp(user->name,find->name))
                        if(!strcmp(user->phone_number,find->phone_number))
                                return 1;
        return 0;
}

USERDATA* createUserData(const int para_age,const char* para_name,const char* para_num)
{
        int name_len,num_len;

        name_len=strlen(para_name);
        num_len=strlen(para_num);

        USERDATA * new_user=(USERDATA*)malloc(sizeof(USERDATA));
        new_user->name= (char*)malloc(name_len+1);
        new_user->phone_number= (char*)malloc(num_len+1);

        new_user->age=para_age;
        strcpy(new_user->name,para_name);
        strcpy(new_user->phone_number,para_num);

        return new_user;
}

int printUser(const USERDATA *const user)
{
        if(user==NULL)
                return -1;

        printf(" %-10s %d%*s%s\n",user->name, user->age,5,"", user->phone_number);
        return 0;
}

/* 구조체 참조용
   typedef struct NODE
{
        USERDATA *user;
        struct NODE * next;
        struct NODE * before;
}NODE;

 */

NODE * createNode(const USERDATA* const userdata)
{
        NODE * new_node=(NODE*)malloc(sizeof(NODE));

        new_node->user=userdata;
        new_node->next=NULL;
        new_node->before=NULL;

        return new_node;
}

NODE * appendNode(NODE *const front ,NODE *const back)
{

        if(front->next==NULL)
        {
                front->next=back;
                back->next=NULL;

                back->before=front;
        }
        else
        {
                NODE *front_tail=getNodeTail(front);

                insertNode(front_tail,back);
        }

        return front;
}

NODE * insertNode(NODE *const front, NODE *const back)
{
        front->next=back;
        back->before=front;

        return front;
}
NODE * insertList(NODE *const dest, NODE *const src)
{
        NODE *temp;
        NODE *src_tail;
        NODE *dest_tail;

        if(dest==NULL)
                return src;

        dest_tail=getNodeTail(dest);
        src_tail=getNodeTail(src);

        temp=dest->next;
        dest->next=src;
        src->before=dest;

        src_tail->next=temp;
        dest_tail->next=NULL;
        temp->before=src_tail;

        return dest;
}

NODE * getNodeTail(NODE *node)
{
        NODE * temp=node;

        while(temp->next!=NULL)
        {
                temp=temp->next;
        }

        return temp;
}

NODE * findNode(const NODE* node,const USERDATA *const find)
{
        while(node!=NULL)
        {
                if(isTheUser(node->user,find))
                        return node;
                node=node->next;
        }

        return NULL;
}


int printNodeList(const NODE * const node)
{
        int ret=0;
        NODE *temp=node;

        printUserHeader();

        if(temp==NULL)
        {
                printf("empty list~\n");
                return ret;
        }

        while(temp->next!=NULL)
        {
                ret=printUser(temp->user);
                if(ret==-1)
                        return ret;
                temp=temp->next;
        }
        ret=printUser(temp->user);

        return ret;
}

void destroyUser(USERDATA* const user)
{
        free(user->name);
        free(user->phone_number);
        free(user);
}

void destroyNode(NODE **const node)
{
        destroyUser((*node)->user);

        if((*node)->next!=NULL)
        {
                ((*node)->before)->next=(*node)->next;
                ((*node)->next)->before=(*node)->before;

                free(*node);
        }
        else
        {
                if((*node)->before!=NULL)
                        ((*node)->before)->next=NULL;
                free(*node);
        }

        *node=NULL;
}

void printUserHeader(void)
{
        printf("|%*sname%*s|age|%*sphone number%*s|\n",3,"",3,"",2,"",2,"");
}

void error_handler(const char* msg)
{
        fputs(msg,stderr);
        exit(1);
}
