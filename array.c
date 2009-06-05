#include "array.h"
#include "common.h"
#include <string.h>

/**
 * functions and structures for managing arrays
 */

array_t *array_new(int len)
{
	array_t *array = (array_t *)MYmalloc(sizeof(array_t));
	array->len = len;
	array->count = 0;
	array->data = MYmalloc(sizeof(void *) * len);
	return array;
}

void array_delete(array_t *array)
{
	free(array->data);
	free(array);
}

void array_append(array_t *array, void *val)
{
	array->data[array->count++] = val;
	if (array->count == array->len) {
		int new_len = array->len * 2;
		void *new_data = MYmalloc(sizeof(void *) * new_len);
		memcpy(new_data, array->data, sizeof(void *) * array->len);
	}
}

void array_insert(array_t *array, int i, void *val)
{
	array->data[i] = val;
}

int array_binary_search(array_t *array, void *val)
{
	int i = 0, j = array->count-1, k;
	do {
		k = (i+j)/2;
		if (val > array_get(array, k))
			i = k+1;
		else
			j = k-1;
	} while (array_get(array, k)==val || i<j);
	return k;
}

void array_insert_ordered(array_t *array, void *val)
{
	if (val > array_get(array, array->count-1)) {
		array_append(array, val);
		return;
	}
	int i = array_binary_search(array, val);
	if (i<0) i=0;
	if (array_get(array, i)!=val) {
		array_append(array, NULL);
		int j;
		for (j=i; j<array->count-1; j++)
			array_get(array, j+1) = array_get(array, j);
		array_get(array, i) = val;
	}
}

/// Insertion sort algorithm
void array_sort(array_t *array)
{
	int i, j;
	for (i = 1; i<array->count; i++) {
		j=i-1;
		void *tmp = array_get(array, i);
		while(j>0 && array_get(array, j) > tmp) {
			array_get(array, j+1) = array_get(array, j);
			--j;
		}
		array_get(array, j) = tmp;
	}
}
