/*
 * Util.h
 *
 *  Created on: Jul 9, 2012
 *      Author: gareth
 */

/* Function: drange
 *
 * Generates and returns an stl vector of doubles in the range given by
 * first, increment, and last (inclusive).
 *
 */
std::vector<double> drange(double first, double increment, double last) {
	std::vector<double> range;

	double t = first;
	while (t <= last) {
		range.push_back(t);
		t += increment;
	}

	return range;
}
