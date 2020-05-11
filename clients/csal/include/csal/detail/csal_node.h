#ifndef __CSAL_NODE_H__
#define __CSAL_NODE_H__


#ifdef __cplusplus
extern "C"
{
#endif


typedef struct _csal_node_t csal_node_t;

typedef _csal_node_leaf_t csal_node_leaf_t;

typedef _csal_node_branch_t csal_node_branch_t;

int csal_node_cast( csal_node_t* self, csal_uuid_t* uuid, void** ppv );


csal_node_leaf_t* csal_node_leaf_create();
int csal_node_leaf_cast( csal_node_leaf_t* self, csal_uuid_t* uuid, void** ppv );

csal_node_branch_t* csal_node_branch_create();
int csal_node_branch_cast( csal_node_branch_t* self, csal_uuid_t* uuid, void** ppv );

#ifdef __cplusplus
}
#endif


#endif
