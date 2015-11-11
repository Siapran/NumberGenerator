#include <stdio.h>
#include <stdlib.h>
#include "node_eval.h"
#include "vector.h"

static size_t size = 0;
static int *input = NULL;

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

#define foreach(head, root) for (head = root; head != NULL; head = head->next)

void read_input() {
	size_t i;
	scanf("%u", &size);
	input = malloc(size * sizeof(*input));
	for (i = 0; i < size; ++i)
	{
		scanf("%d", &input[i]);
	}
}

List *get_all_trees() {

}

int main()
{

	return 0;
}

List_Node *getOpTrees(Vector *values) {

	List_Node
	*root, *head,
	*leftTree_root, *leftTree_head,
	*rightTree_root, *rightTree_head,;

	Node *node;
	Operator op;

	size_t index, i, j;
	Vector leftlist, rightlist;

	if (values.size == 1)
	{
		return List_New_node(NULL, IntNode_New(values->data[0]));
	}

	for (index = 1; index < values->size; ++index) {
		leftlist = Vector_Get_Subvector(values, 0, index);
		rightlist = Vector_Get_Subvector(values, index, values->size);

		leftTree_root = getOpTrees(leftlist);
		rightTree_root = getOpTrees(rightlist);

		foreach (leftTree_head, leftTree_root) {
			foreach (rightTree_head, rightTree_root) {
				for (op = PLUS; op <= DIVIDE; ++op) {
					node = OperatorNode_New(leftTree_head->node, op, rightTree_head->node);
				}
			}
		}

		List_Delete(leftTree_root);
		List_Delete(rightTree_root);
	}
}
