#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAP_WIDTH_TYPE int

//width * width 크기의 공간을 저장하는 구조체
typedef struct
{
        int* ptr;
        MAP_WIDTH_TYPE width;
}MAP;

//달팽이 그리기를 위한 구조체 (x,y)쌍
typedef struct
{
        MAP_WIDTH_TYPE x;
        MAP_WIDTH_TYPE y;
}VECTOR;

//달팽이를 그릴 공간 생성
MAP* createMap(int width,int init);
//공간 반환
void destroyMap(MAP *map);
//공간을 화면에 출력
void printMap(const MAP *const map);
//공간에 달팽이 그리기
int drawSnail(MAP *const map);
//에러 처리용
void error_handler(const char* msg);
//두 값이 같으면 1. 아니면 0
int isBigger(MAP_WIDTH_TYPE steps,MAP_WIDTH_TYPE max);
//map의 position에 있는 달팽이가 오른쪽으로 width 만큼 이동. 지나가면서 배열에 stpes를 표기함.
int moveRight(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps);
int moveDown(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps);
int moveLeft(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps);
int moveUp(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps);
int main(int argc, const char* argv[])
{
        if(argc!=2)
        {
                printf("Usage: %s <snaile Size>\n",argv[0]);
                exit(1);
        }

        MAP *snail=createMap(atoi(argv[1]),0);
        if(drawSnail(snail))
        {
                error_handler("drawSnail() error!\n");
        }
        printMap(snail);
        destroyMap(snail);
}

MAP* createMap(int width,int init)
{
        int allocSize=sizeof(int)*width*width;
        MAP* new_map=(MAP*)malloc(sizeof(MAP));

        new_map->ptr=(int*)malloc(allocSize);
        new_map->width=width;

        memset(new_map->ptr,init,allocSize);

        return new_map;
}

int drawSnail(MAP *const map)
{
        MAP_WIDTH_TYPE width=map->width;
        MAP_WIDTH_TYPE steps=1;
        MAP_WIDTH_TYPE max_steps=width*width;
        VECTOR position={0,0};

        //바운드 체크하고 movve(*m,*p,w,*s) map의 p위치에서 w칸 이동. s를 칸에 표시

        // s가 최대치에 도착 했는지 if문으로 확인
        while(1)
        {
                if(!isBigger(steps,max_steps))
                {
                        //달팽이가 오른쪽으로 이동합니다.
                        moveRight(map,&position,width,&steps);
                        position.y=position.y+1;
                        width-=1;
                }
                if(!isBigger(steps,max_steps))
                {
                        //달팽이가 내려갑니다.
                        moveDown(map,&position,width,&steps);
                        position.x=position.x-1;
                }
                if(!isBigger(steps,max_steps))
                {
                        //달팽이가 왼쪽으로 갑니다.
                        moveLeft(map,&position,width,&steps);
                        position.y=position.y-1;
                        width-=1;
                }
                if(!isBigger(steps,max_steps))
                {
                        //달팽이가 올라갑니다.
                        moveUp(map,&position,width,&steps);
                        position.x=position.x+1;
                }
                if(isBigger(steps,max_steps))
                        break;
        }

        return 0;
}

void printMap(const MAP * const map)
{
        MAP_WIDTH_TYPE width=map->width;

        for(MAP_WIDTH_TYPE i=0; i<width; i++)
        {
                for(MAP_WIDTH_TYPE j=0; j<width; j++)
                {
                        printf("%2d ", (map->ptr)[i*width+j]);
                }
                printf("\n");
        }

        return;
}

void error_handler(const char* msg)
{
        fputs(msg,stderr);
        exit(1);
}

void destroyMap(MAP *map)
{
        free(map->ptr);
        free(map);
}

int isBigger(MAP_WIDTH_TYPE steps,MAP_WIDTH_TYPE max)
{
        return steps>max;
}

//map의 position에 있는 달팽이가 방향으로 width 만큼 이동. 지나가면서 배열에 stpes 
를 표기함.
int moveRight(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps)
{
        for(MAP_WIDTH_TYPE i=0;i<width;i++)
        {
                *((map->ptr)+ (position->y)*(map->width)+ position->x)=*steps;     
                (position->x)++;
                (*steps)++;
        }
        (position->x)--;

        return 0;
}

int moveDown(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps)
{
        for(MAP_WIDTH_TYPE i=0;i<width;i++)
        {
                *((map->ptr)+ (position->y)*(map->width)+ position->x)=*steps;     
                (position->y)++;
                (*steps)++;
        }
        (position->y)--;

        return 0;
}
int moveLeft(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps)
{
        for(MAP_WIDTH_TYPE i=0;i<width;i++)
        {
                *((map->ptr)+ (position->y)*(map->width)+ position->x)=*steps;     
                (position->x)--;
                (*steps)++;
        }
        (position->x)++;

        return 0;
}
int moveUp(MAP* map,VECTOR* position, MAP_WIDTH_TYPE width, MAP_WIDTH_TYPE *steps) 
{
        for(MAP_WIDTH_TYPE i=0;i<width;i++)
        {
                *((map->ptr)+(position->y)*(map->width)+ position->x)=*steps;      
                (position->y)--;
                (*steps)++;
        }
        (position->y)++;

        return 0;
}
