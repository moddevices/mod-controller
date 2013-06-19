
/*
************************************************************************************************************************
*
************************************************************************************************************************
*/

#ifndef NODE_H
#define NODE_H


/*
************************************************************************************************************************
*           INCLUDE FILES
************************************************************************************************************************
*/

#include "config.h" // to MALLOC and FREE macros


/*
************************************************************************************************************************
*           DO NOT CHANGE THESE DEFINES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           CONFIGURATION DEFINES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           DATA TYPES
************************************************************************************************************************
*/

typedef struct NODE_T {
    void *data;
    struct NODE_T *parent, *first_child, *last_child;
    struct NODE_T *prev, *next;
} node_t;


/*
************************************************************************************************************************
*           GLOBAL VARIABLES
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           MACRO'S
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           FUNCTION PROTOTYPES
************************************************************************************************************************
*/

node_t *node_create(void *data);
node_t *node_child(node_t *parent, void *data);
node_t *node_cut(node_t *node);
void node_join(node_t *node1, node_t *node2);
void node_destroy(node_t *node);


/*
************************************************************************************************************************
*           CONFIGURATION ERRORS
************************************************************************************************************************
*/


/*
************************************************************************************************************************
*           END HEADER
************************************************************************************************************************
*/

#endif
