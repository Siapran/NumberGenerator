#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

Vector *get_all_trees(Vector *values) {

	Vector *results;
	Vector *leftresults, *rightresults;

	size_t index, i, j;
	Vector leftlist, rightlist;

	results = Vector_New(0);

	if (values->size == 1)
	{
		Vector_Push(results, values->data[0]);
		Vector_Push(results, -values->data[0]);
		return results;
	}


	for (index = 1; index < values->size; ++index) {
		leftlist = Vector_Get_Subvector(values, 0, index);
		rightlist = Vector_Get_Subvector(values, index, values->size);

		leftresults = get_all_trees(&leftlist);
		rightresults = get_all_trees(&rightlist);

		foreach (i, leftresults) {
			foreach (j, rightresults) {

				Vector_Push(results, leftresults->data[i] + rightresults->data[j]);
				Vector_Push(results, leftresults->data[i] - rightresults->data[j]);
				Vector_Push(results, leftresults->data[i] * rightresults->data[j]);
				if ( rightresults->data[j] == 0 /*|| leftresults->data[i] % rightresults->data[j] != 0*/ ) { break; }
				Vector_Push(results, leftresults->data[i] / rightresults->data[j]);
			}
		}

		Vector_Delete(leftresults);
		Vector_Delete(rightresults);
	}



	return results;
}

int main()
{
	size_t i, size;
	int result;
	Vector *input;
	Vector *results;
	Vector *indexer;

	scanf("%u", &size);
	input = Vector_New(size);
	for (i = 0; i < input->size; ++i)
	{
		scanf("%d", &input->data[i]);
	}

	results = get_all_trees(input);
	indexer = Vector_New(0);

	foreach (i, results) {
		if (results->data[i] >= 0) {
			printf("%d\n", results->data[i]);
			Vector_Set(indexer, results->data[i], 1);
		}
	}

	Vector_Delete(results);

	i = 0;

	while (Vector_Get(indexer, i) != 0) {
		++i;
	}

	printf("%d\n", i);

	Vector_Delete(indexer);

	return 0;
}
