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
	int result;
	Vector *input;
	Vector *results;
	List_Node *root, *head;

	scanf("%u", &size);
	input = Vector_New(size);
	for (i = 0; i < input->size; ++i)
	{
		scanf("%d", &input->data[i]);
	}

	results = Vector_New(8);

	root = get_all_trees(input);

	// foreach (head, root) {
	// 	Print(head->node);
	// 	Evaluation_Error = 0;
	// 	result = Evaluate(head->node);
	// 	printf("\t [%d]", Evaluation_Error);
	// 	if (result < 0 || Evaluation_Error != 0)
	// 	{
	// 		printf("\t -> NOT VALID\n");
	// 	} else {
	// 		printf("\t = %d\n", result);
	// 	}
	// }

	foreach (head, root) {
		Reset_Error();
		result = Evaluate(head->node);
		if (result >= 0 && Get_Error() == 0)
		{
			Vector_Set(results, result, Vector_Get(results, result) + 1);
		}
		// Delete(head->node);
	}
	// List_Delete(root);

	i = 0;

	while (Vector_Get(results, i) != 0) {
		++i;
	}

	printf("%d\n", i);

	return 0;
}
