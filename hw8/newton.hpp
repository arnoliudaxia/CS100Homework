#ifndef NEWTON_HPP_
#define NEWTON_HPP_

#include <stdlib.h>

template<typename T>
double findNearestRoot( T f, double startingPoint, double eps = 0.000001 ) {
	double delta = 10;
	while (delta=(f(startingPoint).first / f(startingPoint).second),abs(delta)>eps)
	{
		startingPoint = startingPoint - delta;
	}
	return startingPoint;
}

#endif