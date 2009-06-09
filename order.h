#ifndef ORDER_H
#define ORDER_H

typedef struct parikh_t
{
	unsigned short int tr_num;
	unsigned short int appearances;
} parikh_t;

typedef struct parikh_vec_t
{
	parikh_t *parikh;
	parikh_t *last;
	unsigned int size;
	unsigned short min, max;
	unsigned int count;
} parikh_vec_t;

void size_mark(hist_t *hist);
int pe_compare (hist_t *pe1, hist_t *pe2);

#endif