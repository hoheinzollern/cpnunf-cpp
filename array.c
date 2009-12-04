#include "array.h"
#include "glib.h"
#include "common.h"
#include <string.h>

/**
 * functions and structures for managing arrays
 */

/// Creates a new array structure
array_t *array_new(int len)
{
	array_t *array = (array_t *)MYmalloc(sizeof(array_t));
	array->len = len;
	array->count = 0;
	if (len>0)
		array->data = MYmalloc(sizeof(void *) * len);
	else
		array->data = NULL;
	return array;
}

/// Returns a copy of the array
array_t *array_copy(array_t *array)
{
	array_t *res = (array_t *)MYmalloc(sizeof(array_t));
	res->len = array->len;
	res->count = array->count;
	if (res->len>0) {
		res->data = MYmalloc(sizeof(void *) * res->len);
		memcpy(res->data, array->data, sizeof(void *) * res->len);
	} else
		res->data = NULL;
	return res;
}

/// Frees an entire array structure
void array_delete(array_t *array)
{
	if (array->len > 0)
		free(array->data);
	free(array);
}

/// Appends values at the end
void array_append(array_t *array, void *val)
{
	if (array->count == array->len) {
		if (array->len==0) {
			array->data = MYmalloc(sizeof(void *) * 2);
			array->len = 2;
		} else {
			int new_len = array->len * 2;
			void *new_data = MYmalloc(sizeof(void *) * new_len);
			memcpy(new_data, array->data,
			       sizeof(void *) * array->len);
			free (array->data);
			array->data = new_data;
			array->len = new_len;
		}
	}
	array->data[array->count++] = val;
}

/// Insert value val at index i of the array
void array_insert(array_t *array, int i, void *val)
{
	array->data[i] = val;
}

/// Does the binary search for val in the array
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

/// Given that the array is ordered, insert val in the correct place
void array_insert_ordered(array_t *array, void *val)
{
#ifdef __DEBUG__
	g_assert(val!=NULL);
#endif
	int i = 0;
	while (i<array->count && array->data[i]<val)
		i++;
	if (i == array->count) {
		array_append(array, val);
	} else if (array->data[i]!=val) {
		int j = array->count;
		array_append(array, NULL);
		while (j>i) {
			array->data[j] = array->data[j-1];
			--j;
		}
		array->data[i] = val;
	}
}

/// Insertion sort algorithm
void array_sort(array_t *array)
{
	int i, j;
	for (i = 1; i<array->count; i++) {
		j=i-1;
		void *tmp = array_get(array, i);
		while(j>=0 && array_get(array, j) > tmp) {
			array_get(array, j+1) = array_get(array, j);
			--j;
		}
		array_get(array, j+1) = tmp;
	}
}

/// @return UNF_TRUE if array is ordered, UNF_FALSE otherwise
UNFbool array_ordered(array_t *array)
{
	UNFbool ordered = UNF_TRUE;
	int i;
	for (i=0; i<array->count-1 && ordered; i++)
		ordered = array_get(array, i) <= array_get(array, i+1);
	return ordered;
}
