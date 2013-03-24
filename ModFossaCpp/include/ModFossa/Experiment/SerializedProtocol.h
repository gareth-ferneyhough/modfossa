/* 
 * File:   SerializedProtocol.h
 * Author: gareth
 *
 * Created on March 23, 2013, 2:46 PM
 */

#ifndef SERIALIZEDPROTOCOL_H
#define	SERIALIZEDPROTOCOL_H

#include <vector>
#include <utility>

namespace ModFossa {
typedef std::vector<std::pair<double, double> > ProtocolIteration;
typedef std::vector<ProtocolIteration> SerializedProtocol;
}
#endif	/* PROTOCOLITERATION_H */

