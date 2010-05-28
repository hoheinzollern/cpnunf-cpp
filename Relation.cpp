#include "Relation.h"

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
			vector<hist_t *>::iterator end = set_intersection(
					first1->hists.begin(), first1->hists.end(),
					first2->hists.begin(), first2->hists.end(),
					first1->hists.begin()
				);
			first1->hists.resize(end - first1->hists.begin());
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
			vector<hist_t *>::iterator end = set_union(
					first1->hists.begin(), first1->hists.end(),
					first2->hists.begin(), first2->hists.end(),
					last->hists.begin()
				);
			last->hists.resize(end - last->hists.begin());
			++last; ++first1; ++first2;
		}

	}
	if (first1==last1) last = copy(first2, last2, last);
	if (first2==last2) last = copy(first1, last1, last);
	result->resize(last - result->begin());
	return result;
}

void Relation::sort(iterator __first, iterator __last) {
	sort(__first, __last);
	ordered = true;
}
