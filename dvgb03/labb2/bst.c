//=============================================================================
// bst.c - binary search tree, based on binary tree (bt.h/bt.c)
//=============================================================================
#include "global.h"
#include "bst.h"

//-----------------------------------------------------------------------------
// local function prototypes
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a);
static void _inorder(BST T, int* pos, int* a);
static void _postorder(BST T, int* pos, int* a);
static int _max(int a, int b);
static int get_balance(BST T) __attribute__((unused));
static BST get_min_value_node(BST T) __attribute__((unused));
static BST get_max_value_node(BST T) __attribute__((unused));
//-----------------------------------------------------------------------------
// public functions, exported through bst.h
//-----------------------------------------------------------------------------
// new_BST: creates a new BST
BST new_BST(int val)
{
	return new_BT(val);
}
//-----------------------------------------------------------------------------
// bst_add: adds the value v to the BST T (unless duplicate)
//-----------------------------------------------------------------------------
BST bst_add(BST T, int v)
{
	return	!T            	?	new_BST(v)                            :
		v < get_val(T)	?	cons(add(get_LC(T), v), T, get_RC(T)) :
		v > get_val(T)	?	cons(get_LC(T), T, add(get_RC(T), v)) :
		/* duplicate */		T;
}
//-----------------------------------------------------------------------------
// bst_rem: removes the value val from the BST (if it exists)
//-----------------------------------------------------------------------------
BST bst_rem(BST T, int val)
{
	if (T == NULL)
		return T;
	
	if (get_val(T) > val)
		set_LC(T, bst_rem(get_LC(T), val));  // Update left child pointer
	else if (get_val(T) < val)
		set_RC(T, bst_rem(get_RC(T), val));  // Update right child pointer
	else {
		// If tree only has right child
		if(get_LC(T) == NULL)
		{
			BST temp = get_RC(T);
			free(T);
			return temp;
		}
		// If tree only has left child
		if(get_RC(T) == NULL)
		{
			BST temp = get_LC(T);
			free(T);
			return temp;
		}
		// if tree has 2 childs
		int bal = get_balance(T);
		if (bal < 0)
		{
			BST successor = get_min_value_node(get_RC(T));
			set_val(T, get_val(successor));
			set_RC(T, bst_rem(get_RC(T), get_val(successor)));
		}
		else
		{
			BST successor = get_max_value_node(get_LC(T));
			set_val(T, get_val(successor));
			set_LC(T, bst_rem(get_LC(T), get_val(successor)));
		}
		
	}
	return T;
}
//-----------------------------------------------------------------------------
// preorder: puts the BST T values into array a in preorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void preorder(BST T, int* a)
{
	int pos = 0;
	_preorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// inorder: puts the BST T values into array a in inorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,2,3]      / \  --> [2,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void inorder(BST T, int* a)
{
	int pos = 0;
	_inorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// postorder: puts the BST T values into array a in postorder
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [1,3,2]      / \  --> [3,2]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void postorder(BST T, int* a)
{
	int pos = 0;
	_postorder(T, &pos, a);
}
//-----------------------------------------------------------------------------
// bfs: puts the BST T values into array a in bfs-order, non-nodes
// are indicated by X, as defined in global.h
//-----------------------------------------------------------------------------
//   2                    2
//  / \	--> [2,1,3]      / \  --> [2,X,3]
// 1  3                 *  3
//-----------------------------------------------------------------------------
void bfs(BST T, int* a, int max)
{
	// TODO
}
//-----------------------------------------------------------------------------
// is_member: checks if value val is member of BST T
//-----------------------------------------------------------------------------
bool is_member(BST T, int val)
{
	if (T)
	{
		if (get_val(T) == val)
			return true;
		if (val > get_val(T))
			return is_member(get_RC(T), val);
		return is_member(get_LC(T), val);
	}
	return false;
}
//-----------------------------------------------------------------------------
// height: returns height of BST T
//-----------------------------------------------------------------------------
int height(BST T)
{
	if(T)
		return _max(height(get_LC(T)) + 1,height(get_RC(T)) + 1);
	return 0;
}
//-----------------------------------------------------------------------------
// size: returns size of BST T
//-----------------------------------------------------------------------------
int size(BST T)
{
	if (T)
		return 1 + size(get_LC(T)) + size(get_RC(T));
	return 0;
}
//-----------------------------------------------------------------------------
// private helper functions, not exported
//-----------------------------------------------------------------------------
static void _preorder(BST T, int* pos, int* a)
{
	if (T)
	{
		a[(*pos)++] = get_val(T);
		_preorder(get_LC(T), pos, a);
		_preorder(get_RC(T), pos, a);
	}
}

static void _inorder(BST T, int* pos, int* a)
{
	if (T)
	{
		_inorder(get_LC(T), pos, a);
		a[(*pos)++] = get_val(T);
		_inorder(get_RC(T), pos, a);
	}
}

static void _postorder(BST T, int* pos, int* a)
{
	if (T)
	{
		_postorder(get_LC(T), pos, a);
		_postorder(get_RC(T), pos, a);
		a[(*pos)++] = get_val(T);
	}
}

static int _max(int a, int b)
{
	return (a > b) ? a : b;
}

// If return value >0 the tree is left heavy, If return value <0 the tree is right heavy
static int get_balance(BST T)
{
	return height(get_LC(T)) - height(get_RC(T));
}

static BST get_min_value_node(BST T)
{
	BST current = T;
	while (get_LC(current) != NULL)
		current = get_LC(current);
	return current;
}

static BST get_max_value_node(BST T)
{
	BST current = T;
	while (get_RC(current) != NULL)
		current = get_RC(current);
	return current;
}