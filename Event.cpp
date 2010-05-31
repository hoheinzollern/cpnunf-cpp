#include "Event.h"
#include "Condition.h"

int Event::count = -1;

Event::Event(const vector <Condition *> &_preset,
			 const vector <Condition *> &_readarcs,
			 trans_t *_origin): preset(_preset), readarcs(_readarcs)
{
	origin = _origin;
	num = count++;

	nodelist_t *ps = _origin->postset;
	while (ps) {
		postset.push_back(new Condition(this, (place_t *)ps->node));
		ps = ps->next;
	}
	sort(postset.begin(), postset.end());
}
