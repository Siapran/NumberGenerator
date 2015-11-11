
typedef struct Vector
{
	int *data;
	size_t size;
	size_t capacity;	
} Vector;

Vector *Vector_New(size_t size);
void Vector_Delete(Vector *self);
void Vector_Resize(Vector *self, size_t size);
int Vector_Get(Vector *self, size_t index);
void Vector_Set(Vector *self, size_t index, int value);

Vector *Vector_Get_Subvector(Vector *self, size_t start, size_t end);
