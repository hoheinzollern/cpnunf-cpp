#ifndef ORDER_H
#define ORDER_H

typedef struct parikh_t
{
	unsigned short int tr_num;
	unsigned short int appearances;
} parikh_t;

void size_mark(hist_t *hist);
int pe_compare (hist_t *pe1, hist_t *pe2);
int parikh_compare (parikh_t *pv1, parikh_t *pv2);
void parikh_init();
void parikh_finish();

#endif
