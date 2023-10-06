#include "Iterator.h"
#include "LO.h"
#include <exception>
using std::exception;

Iterator::Iterator(const LO& lo) : lo(lo) {
	curent = lo.inc;
}

void Iterator::prim() {
	curent = lo.inc;
}

void Iterator::urmator() {
	if (valid())
		curent = lo.urm[curent];
	else
		throw exception();
}

bool Iterator::valid() const {
	return (curent != -1);
}

TElement Iterator::element() const {
	if (valid())
		return lo.el[curent];
	else
		throw exception();
}

void Iterator::revinoKPasi(int k)
{
	if (k <= 0)
		throw exception();
	for (int i = 0; i < k; i++)
	{
		curent = lo.prec[curent];
		if (!valid())
			throw exception();
	}
}
