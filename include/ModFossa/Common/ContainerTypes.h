/* 
 * File:   ContainerTypes.h
 * Author: gareth
 *
 * Created on March 29, 2013, 8:58 PM
 */

#ifndef CONTAINERTYPES_H
#define	CONTAINERTYPES_H

#include <string>
#include <vector>
#include <ModFossa/Common/SharedPtr.h>

namespace ModFossa {

typedef std::vector<std::string> StringVec;
typedef shared_ptr<StringVec>::type StringVecSharedPtr;
    
typedef std::vector<double> Vector;
typedef std::vector<std::vector<double > > Vector2d;
typedef std::vector<Vector2d> Vector3d;
typedef std::vector<Vector3d> Vector4d;

typedef shared_ptr<Vector>::type VectorSharedPtr;
typedef shared_ptr<Vector2d>::type Vector2dSharedPtr;
typedef shared_ptr<Vector3d>::type Vector3dSharedPtr;
typedef shared_ptr<Vector4d>::type Vector4dSharedPtr;

};

#endif	/* CONTAINERTYPES_H */

