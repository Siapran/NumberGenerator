#include <stdio.h>
#include <stdlib.h>
#include "node_eval.h"
#include "vector.h"

typedef struct List_Node
{
	Node *node;
	struct List_Node *next;
} List_Node;


List_Node *List_New_node(List_Node *prev, Node *node) {
	List_Node *self = malloc(sizeof(*self));
	self->node = node;
	self->next = NULL;
	if (prev != NULL)
	{
		prev->next = self;
	}
	return self;
}

void List_Delete(List_Node *self) {
	List_Node *old_self;
	while (self != NULL) {
		old_self = self;
		self = self->next;
		free(old_self);
	}
}

void List_Add(List_Node **root, List_Node **head, Node *node) {
	if (*head == NULL)
	{
		*root = *head = List_New_node(NULL, node);
	} else {
		*head = List_New_node(*head, node);
	}
}

#define foreach(head, root) for (head = root; head != NULL; head = head->next)

List_Node *get_all_trees(Vector *values) {

	List_Node
	*root = NULL, *head = NULL,
	*leftTree_root, *leftTree_head,
	*rightTree_root, *rightTree_head;

	Node *node;
	Operator op;

	size_t index, i, j;
	Vector leftlist, rightlist;

	if (values->size == 1)
	{
		List_Add(&root, &head, IntNode_New(values->data[0]));
		List_Add(&root, &head, IntNode_New(-values->data[0]));
		return root;
	}

	for (index = 1; index < values->size; ++index) {
		leftlist = Vector_Get_Subvector(values, 0, index);
		rightlist = Vector_Get_Subvector(values, index, values->size);

		leftTree_root = get_all_trees(&leftlist);
		rightTree_root = get_all_trees(&rightlist);

		foreach (leftTree_head, leftTree_root) {
			foreach (rightTree_head, rightTree_root) {
				for (op = PLUS; op < OPERATOR_LAST; ++op) {
					node = OperatorNode_New(leftTree_head->node, op, rightTree_head->node);
					List_Add(&root, &head, node);
				}
			}
		}

		List_Delete(leftTree_root);
		List_Delete(rightTree_root);
	}

	return root;
}

int main()
{
	size_t i, size;
	Vector *input;
	List_Node *root, *head;

	scanf("%u", &size);
	input = Vector_New(size);
	for (i = 0; i < input->size; ++i)
	{
		scanf("%d", &input->data[i]);
	}

	root = get_all_trees(input);

	Print(root->node);

	// Node *node = OperatorNode_New(
	// 	OperatorNode_New(
	// 		IntNode_New(5),
	// 		PLUS,
	// 		IntNode_New(6)),
	// 	DIVIDE,
	// 	OperatorNode_New(
	// 		IntNode_New(7),
	// 		MINUS,
	// 		IntNode_New(8)));

	// Print(node);

	return 0;
}
