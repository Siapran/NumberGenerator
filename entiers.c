#include <stdio.h>
#include <stdlib.h>
#include "node_eval.h"


int main(int argc, char const *argv[])
{
	Node *node =
	    OperatorNode_New(
	        IntNode_New(32),
	        DIVIDE,
	        OperatorNode_New(
	            IntNode_New(-8),
	            PLUS,
	            IntNode_New(0)));
	printf("%d\n", Evaluate(node));
	Delete(node);
	return 0;
}