#ifndef AVLTREE_H
#define AVLTREE_H

/*

================================================================
                        FUNCTION DEFINITIONS


-createTree = Creates an AVL Tree and returns NULL

-readData = This function will mainly process the external file. As an input, it will take the file
name and it will return an AVL tree.

-insertPost = This function will take an AVL tree, and the details of a post, and then it will
insert the post to the AVL tree. The post will be interested into the tree based on the
total reach value.

-SingleRotateWithLeft = This function does single rotation with left if needed in insertPost function

-SingleRotateWithRight = This function does single rotation with right if needed in insertPost function

-DoubleRotateWithLeft = This function does double rotation with left if needed in insertPost function

-DoubleRotateWithRight = This function does double rotation with right if needed in insertPost function

-AVLTreeHeight = This function returns the height of the AVL Tree

-maxOfTwoValue = This function returns the max of two integer value

-displayPosts = This function will mainly take an AVL tree and display the data in the tree in
descending order according to the total reach value.

-mostReach = This function will mainly take an AVL tree and display the details of the posts
with the maximum total reach value.

-findMostEngagedValue = This function puts AVL Tree in a queue. Then it will make enqueue and dequeue operations to find the maximum engaged value
in the AVL Tree. Finally, it will return to this maximum engaged number and is used in mostEngaged function

-mostEngaged = This function will mainly take an AVL tree and an integer value which I take from findMostEngagedValue, then it will display the post with the
maximum engaged users.

-maxOfTwoValue = Compares two integer value, then returns the greater one.


*/


struct AVLTreeNode
{
    int postID1;//I divided postID in to two categories. Before the _ and after the _ .
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
    struct AVLTreeNode *left;// left of the tree
    struct AVLTreeNode *right;//right of the tree
    struct AVLTreeNode *same;//if there exist same reach value, data will be connected via *same
    int height;
};

typedef struct AVLTreeNode *AVLTree;

AVLTree createTree();
AVLTree readData(char[]);
AVLTree insertPost(AVLTree,int,int,char[SIZE],int,int,char[SIZE],int,int,int,int,int);

AVLTree SingleRotateWithLeft(AVLTree);
AVLTree SingleRotateWithRight(AVLTree);
AVLTree DoubleRotateWithLeft(AVLTree);
AVLTree DoubleRotateWithRight(AVLTree);

int AVLTreeHeight(AVLTree);
void displayPosts(AVLTree);
void mostReach(AVLTree);
int findMostEngagedValue(AVLTree);
void mostEngaged(AVLTree,int);
int maxOfTwoValue(int,int);

#endif // AVLTREE_H

