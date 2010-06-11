#include "History.h"

void History::findOrCreateEvent()
{
	vector<Event *>
		&post = predecessors[0].cond->postset,
		&read = predecessors[0].cond->readarcs;

	trans_t *t =(trans_t *)event;

	vector<Event *>::iterator i = post.begin(), j = read.begin();
	bool foundPost = false, foundRead = false;
	while (i != post.end() && (*i).origin != t)
		++i;
	if (i != post.end()) foundPost = true;
	while (!foundPost && j != read.end() && (*j).origin != t)
		++j;
	if (j != read.end()) foundRead = true;

	if (!foundPost && !foundRead) {
		// Event not found, create it.
		vector <Condition *> preset, readarcs;
		vector <Predecessor>::iterator pred;
		for (pred = predecessors.begin(); pred != predecessors.end(); ++pred) {
			if ((*pred).hasFlag(PRESET)) {
				preset.push_back((*pred).cond);
			} else {
				readarcs.push_back((*pred).cond);
			}
		}
		event = new Event(preset, readarcs, t);
		nc_add_event(e);
	} else if (foundPost) {
		event = *i;
	} else {
		event = *j;
	}
}

void History::computeConcurrency()
{
	vector <Predecessor>::iterator it = predecessors.begin();
	Relation *tmp;
	while (it != predecessors.end()) {
		Relation *priv = (*it).cond->coPrivate[hist];
		if (tmp) {
			if (priv) {
				Relation co = priv->unionWith(*((*it).hist.co));
				tmp->intersectWith(co);
				delete co;
			} else {
				tmp->intersectWith(*((*it).hist.co));
			}
		} else {
			if (priv)
				tmp = priv->unionWith((*it).hist.co);
			else
				tmp = new Relation((*it).hist.co);
		}
		++it;
	}

	// TODO: reverse side of the relation
}
