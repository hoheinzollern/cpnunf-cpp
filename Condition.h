#ifndef CONDITION_H
#define CONDITION_H

#include "History.h"
#include "Relation.h"
#include "netconv.h"
#include <vector>
#include <map>

using namespace std;

class Event;

class Condition {
	static int count;

public:
	Event *pre;
	vector <Event *> postset;
	vector <Event *> readarcs;
	place_t *origin;
	int num;
	int mark;
	map<History *, Relation *>coPrivate;
	Condition(Event *_pre, place_t *_origin);
};

#endif
