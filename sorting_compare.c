#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

int qsort_count=0;

typedef struct
{
        int* arr;
        int count;
}MY_ARR;

//MY_ARR의 멤버 조작용 함수
int getArrSize(const MY_ARR* const ptr);
int* getArrPtr(const MY_ARR* const ptr,const int index);
int getValueByIndex(const MY_ARR* const ptr,const int i);
void swapByIndex(MY_ARR* const ptr, const int i, const int j);

//MY_ARR 관련 함수
MY_ARR* makeRandArr(int size,time_t seed);
MY_ARR* deepCopy(const MY_ARR* const arr);
void destroyArr(MY_ARR** arr);
void printArr(MY_ARR* ptr,int max_entity);

//정렬 관련 함수
void qsortWrapper(MY_ARR* ptr, int (*comp)(const void*, const void*));
void bubble(MY_ARR* ptr, int (*comp)(const void*, const void*));

int cmpnum(const void *p1, const void *p2)
{
        qsort_count++;
        int ret= *(int*)p1>*(int*)p2;
        return ret;
}

int main(int argc, char* argv[])
{
        //원형  void qsort(void *base, size_t nmemb, size_t size,int (*compar)(const void *, const void *));

        if(argc!=3)
        {
                printf("Usage: %s <size of arr> <count of output>\n",argv[0]);     
                exit(1);
        }

        MY_ARR* randArr1= makeRandArr(atoi(argv[1]),time(NULL));
        MY_ARR* randArr2=deepCopy(randArr1);

        printf("=== before quick sortting ===\n");
        printArr(randArr1,atoi(argv[2]));

        printf("=== after quick sortting ===\n");
        qsortWrapper(randArr1,&cmpnum);
        printf("count of compare: %d\n",qsort_count);
        printArr(randArr1,atoi(argv[2]));
        printf("\n");

        printf("=== before bubble sortting ===\n");
        printArr(randArr2,atoi(argv[2]));

        printf("=== after bubble sortting ===\n");
        bubble(randArr2,NULL);
        printArr(randArr2,atoi(argv[2]));

}

MY_ARR * makeRandArr(int size,time_t seed)
{
        MY_ARR*ptr=(MY_ARR*)malloc(sizeof(MY_ARR));
        ptr->arr=(int*)malloc(sizeof(int)*size);
        ptr->count=size;

        srand(seed);

        for(int i=0;i<size;i++)
        {
                *getArrPtr(ptr,i)=rand()%(3*size);
        }

        return ptr;
}

MY_ARR* deepCopy(const MY_ARR* const arr)
{
        MY_ARR* ret= (MY_ARR*)malloc(sizeof(MY_ARR));

        ret->count=getArrSize(arr);
        ret->arr=(int*)malloc(sizeof(int)* getArrSize(ret));

        memcpy(getArrPtr(ret,0),getArrPtr(arr,0),sizeof(int)* getArrSize(arr));    

        return ret;
}

void printArr(MY_ARR* ptr, int max_entity)
{
        max_entity/=2;

        if(getArrSize(ptr)< max_entity)
                max_entity= getArrSize(ptr)/2;

        // print a 'max_entity' of first
        for(int i=0;i<max_entity;i++)
        {
                printf("%d ",*getArrPtr(ptr,i));
        }

        printf("\n...\n");

        // print a 'max_entity' of last
        for(int i=0;i<max_entity;i++)
        {
                printf("%d ",*getArrPtr(ptr, getArrSize(ptr)-1-i));
        }

        printf("\n");
}
/*
   typedef struct
   {
   int* arr;
   int count;
   }MY_ARR;
 */
void qsortWrapper(MY_ARR* ptr, int (*comp)(const void*, const void*))
{
        qsort(getArrPtr(ptr,0),getArrSize(ptr),sizeof(int),cmpnum);
}

void bubble(MY_ARR* ptr, int (*comp)(const void*, const void*))
{
        const int size=getArrSize(ptr);
        int count=0,temp=0;

        for(int i=0;i<size;i++)
        {
                for(int j=0;j<size-1-i;j++)
                {
                        count++;
                        if(getValueByIndex(ptr,j)>getValueByIndex(ptr,j+1))        
                        {
                                swapByIndex(ptr,j,j+1);
                        }
                }
        }

        printf("count of compare: %d\n",count);
}

/*
   참조용
   typedef struct
{
        int* arr;
        int count;
}MY_ARR;
*/

// ======== MY_ARR 구조체 다루는 함수 =========
int getArrSize(const MY_ARR* const ptr)
{
        return ptr->count;
}

int* getArrPtr(const MY_ARR* const ptr,const int index)
{
        return (ptr->arr)+index;
}
int getValueByIndex(const MY_ARR* const ptr,const int i)
{
        return *((ptr->arr)+i);
}
void swapByIndex(MY_ARR* const ptr, const int i, const int j)
{
        int temp=getValueByIndex(ptr,i);
        *getArrPtr(ptr,i)=*getArrPtr(ptr,j);
        *getArrPtr(ptr,j)=temp;
}

// =================================================
