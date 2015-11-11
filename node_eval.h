typedef struct Node
{
	void (**vtable)();
} Node;

typedef struct IntNode
{
	void (**vtable)();
	int value;
} IntNode;

IntNode *IntNode_New(int value);
void IntNode_Delete(IntNode *self);
int IntNode_Evaluate(IntNode *self);
void IntNode_Print(IntNode *self);

typedef enum Operator
{
	PLUS, MINUS, TIMES, DIVIDE, OPERATOR_LAST
} Operator;

typedef struct OperatorNode
{
	void (**vtable)();
	Node *left;
	Node *right;
	Operator operator;
} OperatorNode;

OperatorNode *OperatorNode_New(Node *left, Operator operator, Node *right);
void OperatorNode_Delete(OperatorNode *self);
int OperatorNode_Evaluate(OperatorNode *self);
void OperatorNode_Print(OperatorNode *self);

enum {Call_Delete = 0, Call_Evaluate, Call_Print};
extern void (*IntNode_Vtable[])();
extern void (*OperatorNode_Vtable[])();
void Delete(Node *self);

extern int Evaluation_Error;
enum {
	NOT_A_DIVIDER = 1,
	DIVIDE_BY_ZERO = 2,
	UNKNOWN_OPERATOR = 4,
};
typedef int (*Evaluate_Function)(Node *self);
int Evaluate(Node *self);

void Print(Node *self);

void Reset_Error();
int Get_Error();