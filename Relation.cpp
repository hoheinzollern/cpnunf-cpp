#include "Relation.h"
#include "Condition.h"
#include "History.h"

bool Pair::operator <(const Pair &p) const
{
	return cond < p.cond;
}

Relation::Relation(): vector<Pair>(), ordered(true)
{
}

Relation::Relation(size_t n): vector<Pair>(n), ordered(true)
{
}

Relation::Relation(const Relation &r): vector<Pair>(r), ordered(r.ordered)
{
}

void Relation::intersectWith(Relation &r)
{
	if (!ordered)
		sort(begin(), end());
	if (!r.ordered)
		sort(r.begin(), r.end());
	iterator first1 = begin(), last1 = end(),
		first2 = r.begin(), last2 = r.end();
	while (first1 != last1 && first2 != last2)
	{
		if (*first1 < *first2) ++first1;
		else if (*first2 < *first1) ++first2;
		else {
			vector<History *>::iterator it, end = set_intersection(
					first1->hists.begin(), first1->hists.end(),
					first2->hists.begin(), first2->hists.end(),
					it
				);
			first1->hists.resize(distance(first1->hists.begin(), end));
			++first1; ++first2;
		}
	}
	resize(first1 - begin());
}

Relation *Relation::unionWith(Relation &r)
{
	if (!ordered)
		sort(begin(), end());
	if (!r.ordered)
		sort(r.begin(), r.end());
	iterator first1 = begin(), last1 = end(),
		first2 = r.begin(), last2 = r.end();
	Relation *result = new Relation(size() + r.size());
	iterator last = result->begin();
	while (first1 != last1 && first2 != last2)
	{
		if (*first1<*first2) *last++ = *first1++;
		else if (*first2<*first1) *last++ = *first2++;
		else {
			*last = Pair();
			last->cond = first1->cond;
			last->hists.resize(first1->hists.size() + first2->hists.size());
			vector<History *>::iterator it, end = set_union(
					first1->hists.begin(), first1->hists.end(),
					first2->hists.begin(), first2->hists.end(),
					it
				);
			last->hists.resize(distance(last->hists.begin(), end));
			++last; ++first1; ++first2;
		}

	}
	if (first1==last1) last = copy(first2, last2, last);
	if (first2==last2) last = copy(first1, last1, last);
	result->resize(last - result->begin());
	return result;
}

void Relation::dropPreset(Event &e)
{
	vector<Condition*>::iterator presetIterator = e.preset.begin();
	iterator first = end(), relationIterator = begin();
	while (presetIterator != e.preset.end() && relationIterator != end()) {
		if (*presetIterator < (*relationIterator).cond) {
			if (first != end()) {
				erase(first, relationIterator);
				first = end();
			}
			++presetIterator;
		} else if (*presetIterator > (*relationIterator).cond) {
			if (first != end()) {
				erase(first, relationIterator);
				first = end();
			}
			++relationIterator;
		} else {
			if (first != end())
				first = relationIterator;
			++presetIterator;
			++relationIterator;
		}
	}
	if (first != end())
		erase(first, relationIterator);
}

void Relation::sort(iterator __first, iterator __last) {
	sort(__first, __last);
	ordered = true;
}
