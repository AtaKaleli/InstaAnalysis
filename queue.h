#ifndef QUEUE_H
#define QUEUE_H
#include "avltree.h"
/*

===============================================================
                    FUNCTION DEFINITIONS

-createQueue = creates a queue

-makeEmptyQueue = makes the queue empty

-isEmptyQueue = checks whether queue is empty or not

-enqueue = enqueues the AVL Tree to a queue

-dequeue = dequeues the AVL Tree from the queue


*/

struct Node
{
    AVLTree element;
    struct Node *next;

};

struct QueueRecord
{
    struct Node *front;
    struct Node *rear;
    int size;
};

typedef struct QueueRecord *Queue;

Queue createQueue();
void makeEmptyQueue(Queue);
int isEmptyQueue(Queue);
void enqueue(Queue,AVLTree);
AVLTree dequeue(Queue);



#endif // QUEUE_H

