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
	
	List_Node *list = NULL;
	size_t index, i;
	Vector *leftlist, *rightlist;
	if (values.size == 1)
	{
		return List_New_node(NULL, IntNode_New(values->data[0]));
	}
	for (index = 1; index < values->size; ++index) {

	}
}

