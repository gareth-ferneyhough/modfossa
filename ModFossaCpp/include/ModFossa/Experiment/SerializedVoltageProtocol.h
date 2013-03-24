/* 
 * File:   ProtocolIteration.h
 * Author: gareth
 *
 * Created on March 23, 2013, 2:46 PM
 */

#ifndef SERIALIZEDVOLTAGEPROTOCOL_H
#define	SERIALIZEDVOLTAGEPROTOCOL_H

#include <vector>
#include <utility>

namespace ModFossa {
typedef std::vector<std::pair<double, double> > ProtocolIteration;
typedef std::vector<ProtocolIteration> SerializedVoltageProtocol;
}
#endif	/* PROTOCOLITERATION_H */

