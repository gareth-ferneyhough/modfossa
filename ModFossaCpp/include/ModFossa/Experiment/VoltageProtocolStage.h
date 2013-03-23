/* 
 * File:   VoltageProtocolStage.h
 * Author: gareth
 *
 * Created on March 23, 2013, 12:47 PM
 */

#ifndef VOLTAGEPROTOCOLSTAGE_H
#define	VOLTAGEPROTOCOLSTAGE_H

#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {
class VoltageProtocolStage {
public:
    typedef ModFossa::shared_ptr<VoltageProtocolStage>::type SharedPointer;
    
    VoltageProtocolStage();
    ~VoltageProtocolStage();
private:

};
}

#endif	/* VOLTAGEPROTOCOLSTAGE_H */

