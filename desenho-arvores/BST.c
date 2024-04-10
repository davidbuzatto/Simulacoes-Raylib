#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "BST.h"

BST* newBST() {

    BST* abb = (BST*) malloc( sizeof( BST ) );
    abb->root = NULL;
    abb->size = 0;

    return abb;

}

void bstPut( BST* abb, int key ) {
    abb->root = bstPutR( abb->root, key );
}

BSTNode* bstPutR( BSTNode* node, int key ) {

    if ( node == NULL ) {
        BSTNode* newNode = (BSTNode*) malloc( sizeof(BSTNode) );
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->key = key;
        newNode->rank = 0;
        newNode->level = 0;
        return newNode;
    } else {
        if ( key < node->key ) {
            node->left = bstPutR( node->left, key );
        } else if ( key > node->key ) {
            node->right = bstPutR( node->right, key );
        } else {
            // value update if storing value
        }
    }

    return node;

}

void bstPreOrder( BSTNode* node ) {
    if ( node != NULL ) {
        bstPrintNode( node );
        bstPreOrder( node->left );
        bstPreOrder( node->right );
    }
}

void bstInOrder( BSTNode* node ) {
    if ( node != NULL ) {
        bstInOrder( node->left );
        bstPrintNode( node );
        bstInOrder( node->right );
    }
}

void bstPostOrder( BSTNode* node ) {
    if ( node != NULL ) {
        bstPostOrder( node->left );
        bstPostOrder( node->right );
        bstPrintNode( node );
    }
}

void bstProcess( BSTNode* node, int* currentRank, int level, int *maxLevel ) {
    if ( node != NULL ) {
        bstProcess( node->left, currentRank, level+1, maxLevel );
        node->rank = *currentRank;
        node->level = level;
        (*currentRank)++;
        bstProcess( node->right, currentRank, level+1, maxLevel );
        if ( *maxLevel < node->level ) {
            *maxLevel = node->level;
        }
    }
}

void bstDraw( BST *bst, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {
    if ( bst != NULL && bst->root != NULL ) {
        bstDrawEdgesR( bst->root, marginLeft, marginTop, radius, spacing );
        bstDrawNodesR( bst->root, marginLeft, marginTop, radius, spacing, fontSize );
    }
}

void bstDrawNodesR( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {
    if ( node != NULL ) {
        bstDrawNodesR( node->left, marginLeft, marginTop, radius, spacing, fontSize );
        bstDrawNode( node, marginLeft, marginTop, radius, spacing, fontSize );
        bstDrawNodesR( node->right, marginLeft, marginTop, radius, spacing, fontSize );
    }
}

void bstDrawNode( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {

    int xc = marginLeft + (node->rank+1) * (radius * 2 + spacing);
    int yc = marginTop + (node->level+1) * radius * 2;

    DrawCircle( xc, yc, radius, BLACK );
    DrawCircle( xc, yc, radius - 2, LIGHTGRAY );

    if ( fontSize > 0 ) {
        const char *label = TextFormat( "%d", node->key );
        int w = MeasureText( label, fontSize );
        DrawText( label, xc - w/2, yc-fontSize/2, fontSize, BLACK );
    }

}

void bstDrawEdgesR( BSTNode *node, int marginLeft, int marginTop, int radius, int spacing ) {
    if ( node != NULL ) {
        bstDrawEdgesR( node->left, marginLeft, marginTop, radius, spacing );
        bstDrawEdge( node, node->left, marginLeft, marginTop, radius, spacing );
        bstDrawEdge( node, node->right, marginLeft, marginTop, radius, spacing );
        bstDrawEdgesR( node->right, marginLeft, marginTop, radius, spacing );
    }
}

void bstDrawEdge( BSTNode *node1, BSTNode *node2, int marginLeft, int marginTop, int radius, int spacing ) {

    if ( node2 != NULL ) {

        Vector2 p1 = {
            marginLeft + (node1->rank+1) * (radius * 2 + spacing),
            marginTop + (node1->level+1) * radius * 2
        };

        Vector2 p2 = {
            marginLeft + (node2->rank+1) * (radius * 2 + spacing),
            marginTop + (node2->level+1) * radius * 2
        };

        DrawLineEx( p1, p2, 2, BLACK );

    }

}

void bstPrintNode( BSTNode *node ) {
    printf( "%d (%d/%d) ", node->key, node->rank, node->level );
}