#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>



typedef struct Node
{
	void (**vtable)();
} Node;

int Evaluate(Node *self);

typedef struct IntNode
{
	void (**vtable)();
	int value;
} IntNode;

void IntNode_Delete(IntNode *self);
int IntNode_Evaluate(IntNode *self);

typedef enum Operator
{
	PLUS, MINUS, TIMES, DIVIDE
} Operator;

typedef struct OperatorNode
{
	void (**vtable)();
	Node *left;
	Node *right;
	Operator operator;
} OperatorNode;

void OperatorNode_Delete(OperatorNode *self);
int OperatorNode_Evaluate(OperatorNode *self);

enum {Call_Delete = 0, Call_Evaluate};
void (*IntNode_Vtable[])() = {
	&IntNode_Delete,
	&IntNode_Evaluate
};
void (*OperatorNode_Vtable[])() = {
	&OperatorNode_Delete,
	&OperatorNode_Evaluate
};

IntNode *IntNode_New(int value) {
	IntNode *self = malloc(sizeof(*self));
	self->vtable = IntNode_Vtable;
	self->value = value;
	return self;
}

OperatorNode *OperatorNode_New(Node *left, Node *right, Operator operator) {
	OperatorNode *self = malloc(sizeof(*self));
	self->vtable = OperatorNode_Vtable;
	self->left = left;
	self->right = right;
	self->operator = operator;
	return self;
}

void Delete(Node *self) {
	self->vtable[Call_Delete](self);
}

void IntNode_Delete(IntNode *self) {
	free(self);
}

void OperatorNode_Delete(OperatorNode *self) {
	Delete(self->left);
	Delete(self->right);
	free(self);
}

static int Evaluation_Error = 0;
enum {
	NOT_DIVIDER = 1,
	DIVIDE_BY_ZERO = 2,
	UNKNOWN_OPERATOR = 4,
};

typedef int (*Evaluate_Function)(Node *self);

int Evaluate(Node *self) {
	return ((Evaluate_Function) self->vtable[Call_Evaluate])(self);
}

int IntNode_Evaluate(IntNode *self) {
	return self->value;
}


int OperatorNode_Evaluate(OperatorNode *self) {
	int left = Evaluate(self->left);
	int right = Evaluate(self->right);
	switch (self->operator) {
	case PLUS:
		return left + right;
		break;
	case MINUS:
		return left - right;
		break;
	case TIMES:
		return left * right;
		break;
	case DIVIDE:
		if (right == 0)
		{
			Evaluation_Error |= DIVIDE_BY_ZERO;
			return 0;
		}
		if (left % right != 0)
		{
			Evaluation_Error |= NOT_DIVIDER;
			return 0;
		}
		return left / right;
		break;
	default:
		Evaluation_Error |= UNKNOWN_OPERATOR;
		return 0;
		break;
	}
}

int main(int argc, char const *argv[])
{
	
	return 0;
}