#ifndef ARRAY_H
#define ARRAY_H

typedef UNFbool unsigned char;
#define UNF_FALSE 0
#define UNF_TRUE !UNF_FALSE

/**
 * array of pointers
 */
typedef struct array_t {
	void **data;
	int len;
	int count;
} array_t;

extern array_t *array_new(int len);
extern void array_delete(array_t *array);

extern void array_append(array_t *array, void *val);
extern void array_insert(array_t *array, int i, void *val);

/**
 * Ordered insertion: given an ordered array it inserts val at the right
 * position; does not insert duplicate pointers.
 */
extern void array_insert(array_t *array, void *val);
extern void array_sort(array_t *array);
#define array_get(array, i) ((array)->data[(i)])

#endif