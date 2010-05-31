#ifndef HISTORY_H
#define HISTORY_H

#include "Event.h"
#include "Relation.h"
#include "order.h"
#include <vector>

using namespace std;

class Condition;
class Event;
class History;

class Predecessor {
public:
	unsigned char flags;
	Condition *cond;
	History *hist;
	bool operator < (const Predecessor &p) {
		return cond < p.cond;
	}
};

class History {
private:
	int size;
	Event *event;
	parikh_t *parikh;
	vector <Predecessor> predecessors;
	unsigned char flags;
	Relation *co;
};

#endif
