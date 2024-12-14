//=============================================================================
// avl.c - AVL-tree based on binary search tree (bst.h/bst.c)
//=============================================================================
#include "avl.h"
#define DEBUG 0
//=============================================================================
// local prototypes
//-----------------------------------------------------------------------------
static AVL srr(AVL T);
static AVL slr(AVL T);
static AVL drr(AVL T);
static AVL dlr(AVL T);
static int get_balance(AVL T);
//=============================================================================
// Public functions, exported via .h-file
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// avl_add: adds the value val to AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_add(AVL T, int val)
{
	if(DEBUG)printf("avl_add (%d)\n",val);

	T = bst_add(T, val);
	T = balance(T);

	return T;
}
//-----------------------------------------------------------------------------
// avl_rem: removes the value val from AVL T in a balanced fashion
//-----------------------------------------------------------------------------
AVL avl_rem(AVL T, int val)
{
	if(DEBUG)printf("avl_rem (%d)\n",val);
	
	T = bst_rem(T, val);
	T = balance(T);
	
	return T;
}
//-----------------------------------------------------------------------------
// balance: balances the AVL tree T if needed
//-----------------------------------------------------------------------------
AVL balance(AVL T)
{
	if (!T)
		return T;

	int balance_factor = get_balance(T);
	// Single right rotation, AKA Right-Right Rotation
	if (balance_factor > 1 && get_balance(get_LC(T)) >= 0)
	{
		T = srr(T);
	}
	// Single left rotation, AKA Left-Left Rotation
	if (balance_factor < -1 && get_balance(get_RC(T)) <= 0)
	{
		T = slr(T);
	}
	// Double right rotation, AKA Right-Left Rotation
	if (balance_factor > 1 && get_balance(get_LC(T)) < 0)
	{
		T = drr(T);
	}
	// Double left rotation, AKA Left-Right Rotation
	if (balance_factor < -1 && get_balance(get_RC(T)) > 0)
	{
		T = dlr(T);
	}
	return T;
}
//=============================================================================
// Private functions, for local use only
//-----------------------------------------------------------------------------
static AVL srr(AVL T)
{
	if(DEBUG)printf("srr\n");

	AVL new_root = get_LC(T);
    set_LC(T, get_RC(new_root));
    set_RC(new_root, T);

	return new_root;
}
static AVL slr(AVL T)
{
	if(DEBUG)printf("slr\n");
	AVL new_root = get_RC(T);
    set_RC(T, get_LC(new_root));
    set_LC(new_root, T);

	return new_root;
}
// Double right rotation, AKA Right-Left Rotation
static AVL drr(AVL T)
{
	if(DEBUG)printf("drr\n");

	AVL leftChild = get_LC(T);
    set_LC(T, slr(leftChild));

    return srr(T);

}
// Double left rotation, AKA Left-Right Rotation
static AVL dlr(AVL T)
{
	if(DEBUG)printf("dlr\n");

	AVL rightChild = get_RC(T);
    set_RC(T, srr(rightChild));

    return slr(T);

}

// If return value >0 the tree is left heavy, If return value <0 the tree is right heavy
int get_balance(AVL T) 
{
    return height(get_LC(T)) - height(get_RC(T));
}