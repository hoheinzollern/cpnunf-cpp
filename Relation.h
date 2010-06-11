#ifndef RELATION_H
#define RELATION_H

#include "netconv.h"
#include "Event.h"
#include <algorithm>
#include <vector>
using namespace std;
class Condition;
class History;

class Pair {
public:
	Condition *cond;
	vector<History *> hists;

	bool operator<(const Pair &p) const;
};

class Relation: public vector<Pair> {
	bool ordered;
public:
	/**
	  * Default constructor: builds an empty relation
	  */
	Relation();

	/**
	  * @arg n the number of pairs that are inserted at the begin
	  */
	Relation(size_t n);

	/**
	  * Copy constructor
	  */
	Relation(const Relation &);

	void intersectWith(Relation &);
	Relation *unionWith(Relation &);
	void dropPreset(Event &);
	void sort(iterator __first, iterator __last);
};

#endif
