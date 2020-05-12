#if 0
#include "sal.h"
#endif

#include "csal/csal.h"

#if 0





struct _csal_node_t
{
};

struct _csal_node_leaf_t
{
};

struct _csal_node_branch_t
{
};


#include "csal/detail/csal_uuid.h"
#include "csal/detail/csal_node.h"

#if 1


#ifdef __cplusplus
extern "C"
{
#endif

typedef enum  
{
    CSAL_NODE_TYPE_BRANCH          
        , CSAL_NODE_TYPE_LEAF   
} CSAL_NODE_TYPE;    


int csal_node_leaf_cast( csal_node_leaf_t* self, csal_uuid_t* uuid, void** ppv )
{
    int err = 0;
    return err;
}

int csal_node_branch_cast( csal_node_branch_t* self, csal_uuid_t* uuid, void** ppv )
{
    int err = 0;
    return err;
}

csal_node_leaf_t* csal_node_leaf_create()
{
    return 0;
}


csal_node_branch_t* csal_node_branch_create()
{
    return 0;
}




csal_node_branch_t* csal_node_branch_create( const char* pszdescription )
{
    csal_node_branch_t* csal_ptr = new csal_node_branch_t;
    csal_ptr->base.sal_obj_ptr = sal::node::Branch::Ptr( new sal::node::Branch( pszdescription ) );

    return csal_ptr;
}

csal_node_leaf_t* csal_node_leaf_create( const char* pszcls
        , const char* pszgroup
        , uint64_t version
        , csal_bool summary
        , const char* pszdescription )
{
    csal_node_leaf_t* csal_ptr = new csal_node_leaf_t;
    csal_ptr->base.sal_obj_ptr = sal::node::Leaf::Ptr( new sal::node::Leaf( pszcls, pszgroup, version, summary, pszdescription ) );

    return csal_ptr;
}
csal_attrib_t* csal_node_leaf_get( csal_node_leaf_t* self, const char* pszkey )
{
    sal::node::Object::Ptr sal_obj_ptr = self->base.sal_obj_ptr;
    //sal::node::Leaf::Ptr sal_leaf_ptr = sal_obj_ptr.cast< sal::node::Leaf >();
    //sal::object::Attribute::Ptr sal_ptr = sal_leaf_ptr.get( pszkey );

    //csal_attrib_t* csal_ptr = csal_attrib_from_sal( sal_ptr );

    return NULL/*csal_ptr*/;
}














#ifdef __cplusplus
}
#endif
#endif




#endif
