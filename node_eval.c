#include <stdio.h>
#include <stdlib.h>
#include "node_eval.h"

void (*IntNode_Vtable[])() = {
	&IntNode_Delete,
	&IntNode_Evaluate,
	&IntNode_Print
};
void (*OperatorNode_Vtable[])() = {
	&OperatorNode_Delete,
	&OperatorNode_Evaluate,
	&OperatorNode_Print
};


IntNode *IntNode_New(int value) {
	IntNode *self = malloc(sizeof(*self));
	self->vtable = IntNode_Vtable;
	self->value = value;
	return self;
}

OperatorNode *OperatorNode_New(Node *left, Operator operator, Node *right) {
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
			Evaluation_Error |= NOT_A_DIVIDER;
		}
		return left / right;
		break;
	default:
		Evaluation_Error |= UNKNOWN_OPERATOR;
		return 0;
		break;
	}
}

void IntNode_Print(IntNode *self) {
	printf("%d ", self->value);
}

static const char *operators[] = {
	"+", "-", "*", "/"
};

void OperatorNode_Print(OperatorNode *self) {
	printf("( ");
	Print(self->left);
	printf("%s ", operators[self->operator]);
	Print(self->right);
	printf(") ");
}

void Print(Node *self) {
	self->vtable[Call_Print](self);
}