#include "heapheader.h"

struct heap* headNextFit;

void initFreeList(){
        freeList=(struct heap*)malloc(sizeof(struct heap));                            //if initially free list is considered as one whole block of memory
        freeList->blockSize = initialSize;
        freeList->next=NULL;
        headNextFit=freeList;
        printf("Free list initialized to given size\n");
}

void traverseList(struct heap* head){
    printf("The given list has following sizes of memory\n");
    while(head!=NULL){
        printf("%d\n",head->blockSize);
        head=head->next;
    }
    printf("\n");
}

void insertAllocList(struct heap* headAlloc, int allocSize){
    struct heap* temp;
    temp=(struct heap*)malloc(sizeof(struct heap));
    temp->blockSize=allocSize;                      //new node created and added to alloc list
    temp->next=NULL;
    if(headAlloc==NULL){
        allocList=temp;
    }
    else{
        while(headAlloc->next!=NULL){
            headAlloc=headAlloc->next;
        }
        headAlloc->next = temp;
    }
}

void allocFirstFit(int allocSize, struct heap* head){
    while((head!=NULL) && (head->blockSize < allocSize)){
        head=head->next;
    }
    if(head==NULL){
        printf("No suitable block available for given size of memory, cant allocate\n");
    }
    else{
        insertAllocList(allocList, allocSize);
        head->blockSize=head->blockSize-allocSize;
    }
}

void allocNextFit(int allocSize){
    while((headNextFit!=NULL) && (headNextFit->blockSize < allocSize)){
        headNextFit=headNextFit->next;
    }
    if(headNextFit==NULL){
        printf("No suitable block available for given size of memory, cant allocate\n");
    }
    else{
        insertAllocList(allocList, allocSize);
        headNextFit->blockSize-=allocSize;
    }
}

void allocBestFit(int allocSize){
    struct heap* head=freeList;
    struct heap* min=freeList;
    while(head->next!=NULL){
        if(head->blockSize >= allocSize && min->blockSize > head->blockSize){
            min=head;
        }
        head=head->next;
    }
    if(min->blockSize < allocSize){
        printf("No suitable block available for given size of memory, cant allocate\n");
    }
    else{
        insertAllocList(allocList, allocSize);
        min->blockSize-=allocSize;
    }
}

void DeleteNode(struct heap* head, int x){
    if(head->blockSize==x){
        allocList=allocList->next;
        free(head);
    }
    else{
        struct heap* prev=head;
        head=head->next;
        while((head!=NULL) && (head->blockSize!=x)){
            prev=prev->next;
            head=head->next;
        }
        if(head==NULL){
            printf("No such block of given size was found in allocated list\n");
        }
        else{
            prev->next=head->next;
            free(head);
        }
    }
}

void deAlloc(struct heap* head1, struct heap* head2, int deAllocSize){
    struct heap* temp;
    while(head2->next!=NULL){
        head2=head2->next;
    }
    while(head1!=NULL && head1->blockSize!=deAllocSize){
        head1=head1->next;
    }
    if(head1=NULL){
        printf("No such block of given size was found in allocated list\n");
    }
    else{
        temp=(struct heap*)malloc(sizeof(struct heap));
        temp->blockSize=deAllocSize;
        temp->next=NULL;
        head2->next=temp;
        DeleteNode(allocList, deAllocSize);
    }
}

void  main(){
    int x,s;
    printf("Enter the initial size of memory to manage\n");
    scanf("%d",&x);
    initialSize=x;
    initFreeList();
    while(x!=7){
        printf("Choose among following operations:\n1. Print free list\n2. Print alloc list\n3. Allocate memory using first fit method\n4. Allocate memory using best fit method\n5. Allocate memory using next fit method\n6. Deallocate memory\n7. Exit\n");
        scanf("%d",&x);
        switch(x){
            case 1: traverseList(freeList);
                    break;
            case 2: traverseList(allocList);
                    break;
            case 3: printf("Enter the size to allocate\n");
                    scanf("%d",&s);
                    allocFirstFit(s, freeList);
                    break;
            case 4: printf("Enter the size to allocate\n");
                    scanf("%d",&s);
                    allocBestFit(s);
                    break;
            case 5: printf("Enter the size to allocate\n");
                    scanf("%d",&s);
                    allocNextFit(s);
                    break;
            case 6: printf("Enter the size to deallocate\n");
                    scanf("%d",&s);
                    deAlloc(allocList, freeList, s);
                    break;
            case 7: x=7;
        }
    }

}









//By Shikhin Dahikar
