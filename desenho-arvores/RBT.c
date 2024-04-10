#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "RBT.h"

RBT* newRBT() {

    RBT* abb = (RBT*) malloc( sizeof( RBT ) );
    abb->root = NULL;
    abb->size = 0;

    return abb;

}

void rbtPut( RBT* rbt, int key ) {
    rbt->root = rbtPutR( rbt->root, key );
}

RBTNode* rbtPutR( RBTNode* node, int key ) {

    if ( node == NULL ) {

        RBTNode* newNode = (RBTNode*) malloc( sizeof(RBTNode) );
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->key = key;
        newNode->color = RBT_COLOR_RED;
        newNode->rank = 0;
        newNode->level = 0;
        newNode->blackLevel = 0;

        return newNode;

    } else {
        if ( key < node->key ) {
            node->left = rbtPutR( node->left, key );
        } else if ( key > node->key ) {
            node->right = rbtPutR( node->right, key );
        } else {
            // value update if storing value
        }
    }

    if ( rbtIsRed( node->right ) && !rbtIsRed( node->left ) ) {
        node = rbtRotateLeft( node );
    }

    if ( rbtIsRed( node->left ) && rbtIsRed( node->left->left ) ) {
        node = rbtRotateRight( node );
    }

    if ( rbtIsRed( node->left ) && rbtIsRed( node->right ) ) {
        rbtFlipColors( node );
    }

    return node;

}

RBTNode* rbtRotateLeft( RBTNode *node ) {

    RBTNode *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    temp->color = node->color;
    node->color = RBT_COLOR_RED;

    return temp;

}

RBTNode* rbtRotateRight( RBTNode *node ) {

    RBTNode *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    temp->color = node->color;
    node->color = RBT_COLOR_RED;

    return temp;

}

void rbtFlipColors( RBTNode *node ) {
    node->color = RBT_COLOR_RED;
    node->left->color = RBT_COLOR_BLACK;
    node->right->color = RBT_COLOR_BLACK;
}

bool rbtIsRed( RBTNode *node ) {
    if ( node == NULL ) {
        return false;
    }
    return node->color == RBT_COLOR_RED;
}

void rbtPreOrder( RBTNode* node ) {
    if ( node != NULL ) {
        rbtPrintNode( node );
        rbtPreOrder( node->left );
        rbtPreOrder( node->right );
    }
}

void rbtInOrder( RBTNode* node ) {
    if ( node != NULL ) {
        rbtInOrder( node->left );
        rbtPrintNode( node );
        rbtInOrder( node->right );
    }
}

void rbtPostOrder( RBTNode* node ) {
    if ( node != NULL ) {
        rbtPostOrder( node->left );
        rbtPostOrder( node->right );
        rbtPrintNode( node );
    }
}

void rbtProcess( RBTNode* node, int* currentRank, int level, int *redNodeCount, int *maxBlackLevel ) {
    if ( node != NULL ) {

        if ( node->color == RBT_COLOR_RED ) {
            (*redNodeCount)++;
        }

        rbtProcess( node->left, currentRank, level + 1, redNodeCount, maxBlackLevel );
        node->rank = *currentRank;
        node->level = level;
        node->blackLevel = level - *redNodeCount;
        (*currentRank)++;
        rbtProcess( node->right, currentRank, level + 1, redNodeCount, maxBlackLevel );

        if ( node->color == RBT_COLOR_RED ) {
            (*redNodeCount)--;
        }

        if ( *maxBlackLevel < node->blackLevel ) {
            *maxBlackLevel = node->blackLevel;
        }

    }
}

void rbtDraw( RBT *rbt, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {
    if ( rbt != NULL && rbt->root != NULL ) {
        rbtDrawEdgesR( rbt->root, marginLeft, marginTop, radius, spacing );
        rbtDrawNodesR( rbt->root, marginLeft, marginTop, radius, spacing, fontSize );
    }
}

void rbtDrawNodesR( RBTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {
    if ( node != NULL ) {
        rbtDrawNodesR( node->left, marginLeft, marginTop, radius, spacing, fontSize );
        rbtDrawNode( node, marginLeft, marginTop, radius, spacing, fontSize );
        rbtDrawNodesR( node->right, marginLeft, marginTop,  radius, spacing, fontSize );
    }
}

void rbtDrawNode( RBTNode *node, int marginLeft, int marginTop, int radius, int spacing, int fontSize ) {

    int xc = marginLeft + (node->rank+1) * (radius * 2 + spacing);
    int yc = marginTop + (node->blackLevel+2) * radius * 2;

    DrawCircle( xc, yc, radius, BLACK );
    DrawCircle( xc, yc, radius - 2, LIGHTGRAY );

    if ( fontSize > 0 ) {
        const char *label = TextFormat( "%d", node->key );
        int w = MeasureText( label, fontSize );
        DrawText( label, xc - w/2, yc-fontSize/2, fontSize, BLACK );
    }

}

void rbtDrawEdgesR( RBTNode *node, int marginLeft, int marginTop, int radius, int spacing ) {
    if ( node != NULL ) {
        rbtDrawEdgesR( node->left, marginLeft, marginTop, radius, spacing );
        rbtDrawEdge( node, node->left, marginLeft, marginTop, radius, spacing );
        rbtDrawEdge( node, node->right, marginLeft, marginTop, radius, spacing );
        rbtDrawEdgesR( node->right, marginLeft, marginTop, radius, spacing );
    }
}

void rbtDrawEdge( RBTNode *node1, RBTNode *node2, int marginLeft, int marginTop, int radius, int spacing ) {

    if ( node2 != NULL ) {

        Vector2 p1 = {
            marginLeft + (node1->rank+1) * (radius * 2 + spacing),
            marginTop + (node1->blackLevel+2) * radius * 2
        };

        Vector2 p2 = {
            marginLeft + (node2->rank+1) * (radius * 2 + spacing),
            marginTop + (node2->blackLevel+2) * radius * 2
        };

        DrawLineEx( 
            p1, p2, 
            node2->color == RBT_COLOR_RED ? 6 : 2,
            node2->color == RBT_COLOR_RED ? RED : BLACK );

    }

}

void rbtPrintNode( RBTNode *node ) {
    printf( "%d %c (%d/%d) ", 
            node->key, 
            node->color == RBT_COLOR_RED ? 'R' : 'B',
            node->rank, 
            node->level );
}