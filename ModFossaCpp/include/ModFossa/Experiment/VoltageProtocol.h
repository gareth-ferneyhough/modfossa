/* 
 * File:   VoltageProtocol.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:47 PM
 */

#ifndef VOLTAGEPROTOCOL_H
#define	VOLTAGEPROTOCOL_H

#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {
class VoltageProtocol {
public:
    typedef ModFossa::shared_ptr<VoltageProtocol>::type SharedPointer;
    
    VoltageProtocol();
    ~VoltageProtocol();
private:

};
}

#endif	/* VOLTAGEPROTOCOL_H */

