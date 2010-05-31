#include "Condition.h"

int Condition::count = 0;

Condition::Condition(Event *_pre, place_t *_origin)
{
	num = count++;
	pre = _pre;
	origin = _origin;
	mark = 0;
}
