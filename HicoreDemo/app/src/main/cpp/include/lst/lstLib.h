#ifndef _LST_LIB_H
#define _LST_LIB_H


#if defined( __cplusplus )
extern "C" {
#endif

typedef struct node     /* node of a linked list. */
{
    struct node* next;  /* Points at the next node in the list */
    struct node* previous;  /* Points at the previous node in the list */
} NODE;

typedef struct      /* Header for a linked list. */
{
    NODE node;  /* Header list node */
    int count;  /* Number of nodes in list */
} LIST;

#define LIST_FOR_EACH(type,var,list) for(var = (type*)lstFirst(list); var != NULL; var=(type*)lstNext(&var->node))


/**
 * lstInit - initialize a list descriptor
 *
 * This routine initializes a specified list to an empty list.
 *
 * RETURNS: N/A
 */
void lstInit(LIST* pList);

/**
 * lstInsert - insert a node in a list after a specified node
 *
 * This routine inserts a specified node in a specified list.
 * The new node is placed following the list node <pPrev>.
 * If <pPrev> is NULL, the node is inserted at the head of the list.
 *
 * RETURNS: N/A
 */
void lstInsert(LIST *pList, NODE *pPrev, NODE *pNode);

/**
 * lstAdd - add a node to the end of a list
 *
 * This routine adds a specified node to the end of a specified list.
 *
 * RETURNS: N/A
 */
void lstAdd(LIST *pList, NODE *pNode);

/**
 * Function: lstConcat
 * Description:  This routine concatenates the second list to \n
 *                  the end of the first list. \n
 *                  The second list is left empty.  Either list (or both) can be \n
 *                  empty at the beginning of the operation.\n
 * \param[in]  pDstList  - A pointer to the destination list
 * \param[in]  pAddList  - A pointer to the list to be appended
 * \return:  N/A
 * \note ...
 */
void lstConcat(LIST *pDstList,LIST *pAddList);

/**
 * Function: lstExtract
 * Description:  extract a sublist from a list\n
 *               This routine extracts the sublist that starts with <pStartNode> and ends\n
 *               with <pEndNode> from a source list.  It places the extracted list in\n
 *               <pDstList>.
 * \param[in]  pSrcList   - A pointer to the specified list
 * \param[in]  pStartNode - A pointer to the start node
 * \param[in]  pEndNode   - A pointer to the end node
 * \param[out] pDstList   - A pointer to the list to append extracted sublist
 * \return:  N/A
 * \note ...
 */
void lstExtract(LIST *pSrcList,NODE *pStartNode, NODE *pEndNode,LIST *pDstList);

/**
 *
 * lstDelete - delete a specified node from a list
 *
 * This routine deletes a specified node from a specified list.
 *
 * RETURNS: N/A
 */
void lstDelete(LIST *pList,NODE *pNode);

/**
 * Function: lstCount
 * Description: report the number of nodes in a list
 * \param[in]  pList  - A pointer to the list to conut
 * \return:   The number of nodes in the list.
 * \note ...
 */
int lstCount(LIST *pList);

/**
 *
 * lstNext - find the next node in a list
 *
 * This routine locates the node immediately following a specified node.
 *
 * RETURNS:
 * A pointer to the next node in the list, or
 * NULL if there is no next node.
 */
NODE *lstNext(NODE *pNode);

/**
 * Function: lstPrevious
 * Description:  find the previous node in a list
 *              This routine locates the node immediately preceding the node pointed to 
 *              by <pNode>.
 * \param[in]  pNode  - A pointer to the node
 * \return: A pointer to the previous node in the list
 * \note ...
 */
NODE *lstPrevious(NODE *pNode);

/**
 *
 * lstFirst - find first node in list
 *
 * This routine finds the first node in a linked list.
 *
 * RETURNS
 * A pointer to the first node in a list, or
 * NULL if the list is empty.
 */
NODE *lstFirst(LIST *pList);

/**
 * Function: lstLast
 * Description:  find the last node in a list
 * \param[in]  pList  - A pointer to the list
 * \return:  A pointer to the last node in the list
 * \note ...
 */
NODE *lstLast(LIST *pList);

/**
 * Function: lstGet
 * Description: delete and return the first node from a list
 * \param[in]  pList  - A pointer to the list to get first node
 * \return:    A pointer to the node gotten
 * \note ...
 */
NODE *lstGet(LIST *pList);

/**
 * Function: lstFind
 * Description:  find a node in a list
 *              This routine returns the node number of a specified node (the first node is 1)
 * \param[in]  pList  - A pointer to the list
 * \param[in]  pNode  - A pointer to the pNode to find
 * \return: The node number or -1 if the node is not found.
 * \note ...
 */
int lstFind(LIST *pList,NODE *pNode);

/**
 * Function: lstFree
 * Description:  free up a list
 *              This routine turns any list into an empty list It also frees up memory used for nodes
 * \param[in]  pList  - A pointer to the list to be freed
 * \return: N/A
 * \note ...
 */
void lstFree(LIST *pList);

/**
 * Function: lstNth
 * Description:  find the Nth node in a list
 *              This routine returns a pointer to the node specified by a number <nodenum>
 *              where the first node in the list is numbered 1.
 *              Note that the search is optimized by searching forward from the beginning
 *              if the node is closer to the head, and searching back from the end
 *              if it is closer to the tail
 * \param[in]  pList  - A pointer to the list
 * \param[in]  nodenum  - 
 * \return: a pointer to the node specified by nodenum
 * \note ...
 */
NODE *lstNth(LIST *pList,int nodenum);

/**
 * Function: lstNStep
 * Description:  find a list node <nStep> steps away from a specified node
 *              This routine locates the node <nStep> steps away in either direction from 
 *              a specified node.  If <nStep> is positive, it steps toward the tail.  If
 *              <nStep> is negative, it steps toward the head.  If the number of steps is
 *              out of range, NULL is returned.
 * \param[in]  pNode  - A pointer to the node to start to find
 * \param[in]  nStep  - 
 * \return: A pointer to the node <nStep> steps away
 * \note ...
 */
NODE *lstNStep(NODE *pNode, int nStep);

#if defined( __cplusplus )
}
#endif


#endif /* end of _LST_LIB_H */
