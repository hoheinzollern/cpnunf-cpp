#ifndef EVENT_H
#define EVENT_H

#include "History.h"
#include "netconv.h"
#include <vector>
#include <set>

using namespace std;

class Condition;
class History;

class Event {
	static int count;

public:
	vector <Condition *> preset;
	vector <Condition *> postset;
	vector <Condition *> readarcs;
	trans_t *origin;
	int num;
	int mark;
	short  foata_level;
	set <History *> histories;
	Event(const vector <Condition *> &_preset,
		  const vector <Condition *> &_readarcs,
		  trans_t *_origin);
};

#endif
