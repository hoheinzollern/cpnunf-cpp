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

#endif