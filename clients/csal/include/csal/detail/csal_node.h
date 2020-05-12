#ifndef __CSAL_NODE_H__
#define __CSAL_NODE_H__


#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        CSAL_NODE_TYPE_BRANCH
            , CSAL_NODE_TYPE_LEAF
    } CSAL_NODE_TYPE;

typedef struct _csal_node_t csal_node_t;
#define IID_CSAL_NODE "70cb62ed-70f9-457f-9b39-0a67f7d87563"

typedef struct _csal_node_leaf_t csal_node_leaf_t;
#define IID_CSAL_NODE_LEAF "2803ed60-7c52-494c-940d-3e74e135f393"

typedef struct _csal_node_branch_t csal_node_branch_t;
#define IID_CSAL_NODE_BRANCH "cb39089b-3ce7-4622-87b2-a4d731bd2ee5"

#if 0



int csal_node_cast( csal_node_t* self, csal_uuid_t* uuid, void** ppv );


csal_node_leaf_t* csal_node_leaf_create();
int csal_node_leaf_cast( csal_node_leaf_t* self, csal_uuid_t* uuid, void** ppv );

csal_node_branch_t* csal_node_branch_create();
int csal_node_branch_cast( csal_node_branch_t* self, csal_uuid_t* uuid, void** ppv );
#endif
#ifdef __cplusplus
}
#endif


#endif
