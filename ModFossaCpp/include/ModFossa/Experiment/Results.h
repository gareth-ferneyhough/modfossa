/* 
 * File:   Results.h
 * Author: gareth
 *
 * Created on March 23, 2013, 2:46 PM
 */

#ifndef RESULTS_H
#define	RESULTS_H

#include <vector>
#include <utility>

namespace ModFossa {
typedef std::vector<std::vector<std::vector<double > > >ProtocolIterationResults;
typedef std::vector<ProtocolIterationResults> ExperimentSweepResults;
}
#endif	/* RESULTS_H */

