#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define SIZE 100
#define TRUE 1
#define FALSE 0


#include "queue.h"
#include "avltree.h"



int main(int argc, char *argv[])
{

AVLTree myAVLTree;
myAVLTree=createTree();

myAVLTree=readData(argv[1]);// I am taking the file name as an argument.


printf("Welcome to Data Analysis @ Instagram\n");
printf("============================================\n\n");
printf("Data Processed:\n");
printf("===================\n");

displayPosts(myAVLTree);
mostReach(myAVLTree);

int maxEngage=findMostEngagedValue(myAVLTree);
mostEngaged(myAVLTree,maxEngage);


    return 0;
}

AVLTree createTree()
{
    return NULL;
}
AVLTree readData(char fileName[])
{
    FILE *outFile; //I opened my file as read mode to get the data in it//
    outFile=fopen(fileName,"r");
    if(outFile==NULL)
    {
        printf("File could not opened for read mode!!\n\n");
        exit(1);
    }
    else
        printf("The insta.txt file has been loaded successfully\n\n");

    //those are my post variables
    int postID1;
    int postID2;
    char permaLink[SIZE];
    int totalReach;
    int engagedUsers;
    char type[SIZE];
    int postDay;
    int postMonth;
    int postYear;
    int postHour;
    int postMinute;

    int i;
    AVLTree tmp;
    tmp=createTree();

    // Until the file reached end, I take the information from file, then I called insertPost to insert these values to my tree.
    for(i=0;((fscanf(outFile,"%d_%d; %[^;]; %d; %d; %[^;]; %d/%d/%d %d:%d\n",&postID1,&postID2,permaLink,&totalReach,&engagedUsers,type,&postDay,&postMonth,&postYear,&postHour,&postMinute)!=EOF));i++)//this loop takes data until it reaches EOF//
	{

        tmp=insertPost(tmp,postID1,postID2,permaLink,totalReach,engagedUsers,type,postDay,postMonth,postYear,postHour,postMinute);
    }


    fclose(outFile);
    return tmp; //after inserting my temporary tree,I return it.
}
AVLTree insertPost(AVLTree t,int postID1,int postID2,char permaLink[SIZE],int reachVal,int engagedUsers,char type[SIZE],int postDay,int postMonth,int postYear,int postHour,int postMinute)
{

    if(t == NULL)
    {
        t=(struct AVLTreeNode*)malloc(sizeof(struct AVLTreeNode));
        if(t == NULL)
        {
            printf("File could not opened for read mode!!\n\n");
            exit(2);
        }
        else
        {
            t->postID1=postID1;
            t->postID2=postID2;
            strcpy(t->permaLink,permaLink);
            t->totalReach=reachVal;
            t->engagedUsers=engagedUsers;
            strcpy(t->type,type);
            t->postDay=postDay;
            t->postMonth=postMonth;
            t->postYear=postYear;
            t->postHour=postHour;
            t->postMinute=postMinute;
            t->left=NULL;
            t->right=NULL;
            t->same=NULL;
            t->height=0;
        }
     }
     else if(reachVal < t->totalReach)
     {
         t->left=insertPost(t->left,postID1,postID2,permaLink,reachVal,engagedUsers,type,postDay,postMonth,postYear,postHour,postMinute);
         if(AVLTreeHeight(t->left) - AVLTreeHeight(t->right) == 2)
         {
             if(reachVal < t->left->totalReach)
                t=SingleRotateWithLeft(t);
             else
             {
                t=DoubleRotateWithLeft(t);
             }
         }

     }
     else if(reachVal > t->totalReach)
     {
         t->right=insertPost(t->right,postID1,postID2,permaLink,reachVal,engagedUsers,type,postDay,postMonth,postYear,postHour,postMinute);
         if(AVLTreeHeight(t->right) - AVLTreeHeight(t->left) == 2)
         {
             if(reachVal > t->right->totalReach)
                t=SingleRotateWithRight(t);
             else
             {
                t=DoubleRotateWithRight(t);
             }
         }
     }
     else//When there comes a same reach value data,I entered this else part.
     {

        struct AVLTreeNode *sameTmp;// I am creating a temporary tree called sameTmp, which holds the data of post that has same reach value with any other post
        sameTmp=(struct AVLTreeNode*)malloc(sizeof(struct AVLTreeNode));
        if(sameTmp==NULL)
        {
            printf("Out of memory!\n");
            exit(3);
        }
        else
        {
            sameTmp->postID1=postID1;
            sameTmp->postID2=postID2;
            strcpy(sameTmp->permaLink,permaLink);
            sameTmp->totalReach=reachVal;
            sameTmp->engagedUsers=engagedUsers;
            strcpy(sameTmp->type,type);
            sameTmp->postDay=postDay;
            sameTmp->postMonth=postMonth;
            sameTmp->postYear=postYear;
            sameTmp->postHour=postHour;
            sameTmp->postMinute=postMinute;

            struct AVLTreeNode *traverseTmp = t;// here, I created temporary pointer called traversTmp, then I assign it to my tree

            while(traverseTmp->same != NULL)// while traversTmp is not null, it iterates the travesTmp
                traverseTmp=traverseTmp->same;

            traverseTmp->same=sameTmp;//and finally, I make the connection between sameTmp and traversTmp.
            sameTmp->left=NULL;
            sameTmp->right=NULL;
            sameTmp->same=NULL;
        }

    }

     t->height=maxOfTwoValue(AVLTreeHeight(t->left) , AVLTreeHeight(t->right)) + 1;

    return t;
}



AVLTree SingleRotateWithLeft(AVLTree k2)
{
    AVLTree k1;

    k1=k2->left;
    k2->left=k1->right;
    k1->right=k2;



    k1->height= maxOfTwoValue(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right)) + 1;
    k2->height= maxOfTwoValue(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right)) + 1;

    return k1;
}
AVLTree SingleRotateWithRight(AVLTree k1)
{
    AVLTree k2;

    k2=k1->right;
    k1->right=k2->left;
    k2->left=k1;

    k2->height= maxOfTwoValue(AVLTreeHeight(k2->left),AVLTreeHeight(k2->right)) + 1;
    k1->height= maxOfTwoValue(AVLTreeHeight(k1->left),AVLTreeHeight(k1->right)) + 1;

    return k2;
}
AVLTree DoubleRotateWithLeft(AVLTree k3)
{
    k3->left=SingleRotateWithRight(k3->left);

    return SingleRotateWithLeft(k3);
}
AVLTree DoubleRotateWithRight(AVLTree k3)
{
    k3->right=SingleRotateWithLeft(k3->right);

    return SingleRotateWithRight(k3);
}

int AVLTreeHeight(AVLTree t)
{
    if(t == NULL)
        return -1;
    else
        return t->height;
}
int maxOfTwoValue(int x,int y)
{
    if(x >= y)
        return x;
    else
        return y;
}

void displayPosts(AVLTree t)
{
    if(t == NULL)
        return;

    else
    {
        displayPosts(t->right);
        printf("Post ID: %d_%d\n",t->postID1,t->postID2);
        printf("Total Reach: %d  Engaged Users: %d\n",t->totalReach,t->engagedUsers);
        if(t->same != NULL)//If the current tree node has same part, i will display it until there does not exist any same part.
            displayPosts(t->same);
        displayPosts(t->left);
    }
}



/**

The complexity of mostReach function is O (log n).As we are searching the rightest node of the
tree to find the post which has highest reach value, we traversing just the right part of the tree.

Best case will be O(1). If there exist just 1 post, we do not need to traverse.

There is no way to improve the complexity.Because we have already an increasing order while
traversing to right. So we at least have O(log n) time complexity.



**/


void mostReach(AVLTree t)//As I insert tree with total reach values, the most total reach value of a post is the rightest post of the tree

{
    struct AVLTreeNode *tmp=t;
    if(t==NULL)
    {
        printf("Tree is empty!\n");//if tree is empty, I give an error message and return
        return;
    }

    while( tmp->right != NULL)//here I am iterating tmp until it's right will become NULL
        tmp=tmp->right;

    printf("\nMaximum Total Reach:\n");
    printf("=========================\n");
    printf("Post ID: %d_%d\n",tmp->postID1,tmp->postID2);
    printf("Permalink: %s\n",tmp->permaLink);
    printf("Type: %s\n",tmp->type);
    printf("Posted: %d/%d/%d %d:%d\n",tmp->postDay,tmp->postMonth,tmp->postYear,tmp->postHour,tmp->postMinute);
    printf("Total Reach: %d\n",tmp->totalReach);
    printf("Engaged Users: %d\n",tmp->engagedUsers);

    while(tmp->same != NULL)//here , same approach with display.If current tree node has a same reach value post, it will be displayed.
    {
        printf("\nMaximum Total Reach:\n");
        printf("=========================\n");
        printf("Post ID: %d_%d\n",tmp->same->postID1,tmp->same->postID2);
        printf("Permalink: %s\n",tmp->same->permaLink);
        printf("Type: %s\n",tmp->same->type);
        printf("Posted: %d/%d/%d %d:%d\n",tmp->same->postDay,tmp->same->postMonth,tmp->same->postYear,tmp->same->postHour,tmp->same->postMinute);
        printf("Total Reach: %d\n",tmp->same->totalReach);
        printf("Engaged Users: %d\n",tmp->same->engagedUsers);

        tmp=tmp->same;//if there are more than one same posts, I iterate the tmp.
    }
}



Queue createQueue()
{
    Queue q;


    q=(struct QueueRecord*)malloc(sizeof(struct QueueRecord));
    if(q==NULL)
    {
        printf("Out of memory!");
        exit(4);
    }
    makeEmptyQueue(q);
    return q;


}
void makeEmptyQueue(Queue q)
{
    q->front=(struct Node*)malloc(sizeof(struct Node));
    if(q->front==NULL)
    {
        printf("Out of memory!");
        exit(5);
    }
    q->front->next=NULL;
    q->rear=q->front;
    q->size=0;
}
int isEmptyQueue(Queue q)
{
    if(q->size==0)
        return TRUE;
    else
        return FALSE;

}
void enqueue(Queue q,AVLTree t)
{
    struct Node *newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL)
    {
        printf("Out of memory!");
        exit(6);
    }

    newNode->element=t;
    newNode->next=NULL;

    q->rear->next=newNode;
    q->rear=newNode;
    q->size++;
}
AVLTree dequeue(Queue q)
{

    struct Node *remove;
    AVLTree t;

    remove=q->front->next;
    t=remove->element;

    q->front->next=remove->next;
    free(remove);
    q->size--;

    if(q->size==0)
        q->rear=q->front;


    return t;

}

int findMostEngagedValue(AVLTree t)
{
    int maxEngage=-1;

    if(t==NULL)
    {
        printf("Tree is empty!\n");
        exit(7);
    }
    else
    {
        struct AVLTreeNode *tmp = t;
        Queue q;
        q=createQueue();
        enqueue(q,tmp);

        while(!isEmptyQueue(q))
        {
            tmp=dequeue(q);
            if(tmp->engagedUsers > maxEngage) // here , I compare posts and decide which one has the most engage value
                maxEngage=tmp->engagedUsers;
            if(tmp->left != NULL)
                enqueue(q,tmp->left);
            if(tmp->right != NULL)
                enqueue(q,tmp->right);
            if(tmp->same != NULL)
                enqueue(q,tmp->same);

        }
    }



return maxEngage;// I return the maxEngage value, which will be taken as parameter in mostEngaged function

}


/**

The complexity of mostEngaged function is O (log n).As we are searching a node which has highest engaged value,
we have to traverse the whole tree. This is because any node can have the maximum engaged value. So the time
complexity should be at least  O(log2n) as a worst case.

Best case will be O(1). If there exist just 1 post, we do not need to traverse.

There is no way to improve the complexity.As I mentioned above, any node should have maximum engaged value, and we
can not know which node is this , if we do not traverse the whole tree.

**/
void mostEngaged(AVLTree t, int maxEngage)
{



    if(t->engagedUsers == maxEngage)//if t->engagedUsers = MaxEngage, it simply print the data, else , I traverse the children of the tree
    {
        printf("\nMaximum Engaged Users:\n");
        printf("=========================\n");
        printf("Post ID: %d_%d\n",t->postID1,t->postID2);
        printf("Permalink: %s\n",t->permaLink);
        printf("Type: %s\n",t->type);
        printf("Posted: %d/%d/%d %d:%d\n",t->postDay,t->postMonth,t->postYear,t->postHour,t->postMinute);
        printf("Total Reach: %d\n",t->totalReach);
        printf("Engaged Users: %d\n",t->engagedUsers);
    }
    if(t->same != NULL)//after finding a post which has maximum engage value, I check whether this post has another posts connected with it.
        mostEngaged(t->same,maxEngage);//if yes, I check them
    if(t->left != NULL)
         mostEngaged(t->left,maxEngage);
    if(t->right != NULL)
        mostEngaged(t->right,maxEngage);

}



























