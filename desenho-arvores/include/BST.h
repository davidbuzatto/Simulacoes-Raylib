#pragma once

typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
    int rank;
    int level;
} BSTNode;

typedef struct BST {
    BSTNode* root;
    int size;
} BST;

BST* newBST();
void bstPut( BST* abb, int key );
BSTNode* bstPutR( BSTNode* node, int key );

void bstPreOrder( BSTNode* node );
void bstInOrder( BSTNode* node );
void bstPostOrder( BSTNode* node );

void bstProcess( BSTNode* node, int* currentRank, int level, int *maxLevel );

void bstDraw( BST *bst, int marginLeft, int marginTop, int radius, int spacing, int fontSize );
void bstDrawNodesR( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize );
void bstDrawNode( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize );
void bstDrawEdgesR( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing );
void bstDrawEdge( BSTNode *node1, BSTNode *node2, int marginLeft, int marginTop, int radius, int spacing );

void bstPrintNode( BSTNode *node );