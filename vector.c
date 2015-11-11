#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

Vector *Vector_New(size_t size) {
	Vector *self = malloc(sizeof(*self));
	self->data = NULL;
	self->size = 0;
	self->capacity = 0;
	Vector_Resize(self, size);
	return self;
}

void Vector_Delete(Vector *self) {
	free(self->data);
	free(self);
}

size_t next_pow2(size_t value) {
	if (value == 0)
	{
		return 1;
	}
	--value;
	value |= value >> 1;
	value |= value >> 2;
	value |= value >> 4;
	value |= value >> 8;
	value |= value >> 16;
	++value;
	return value;
}

#define min(a, b) ((a) < (b) ? (a) : (b))

void Vector_Resize(Vector *self, size_t size) {
	size_t capacity = next_pow2(size);
	int *data;
	if (self->capacity != capacity)
	{
		data = calloc(capacity, sizeof(*data));
		memcpy(data, self->data, min(self->size, size));
		free(self->data);
		self->data = data;
		self->capacity = capacity;
	}
	self->size = size;
}

int Vector_Get(Vector *self, size_t index) {
	if (index >= self->size)
	{
		Vector_Resize(self, index + 1);
	}
	return self->data[index];
}

void Vector_Set(Vector *self, size_t index, int value) {
	if (index >= self->size)
	{
		Vector_Resize(self, index + 1);
	}
	self->data[index] = value;
}

Vector Vector_Get_Subvector(Vector *self, size_t start, size_t end) {
	Vector res = {
		.data = self->data + start,
		.size = end - start,
		.capacity = -1
	};
	return res;
}
