/* 
 * File:   ContainerTypes.h
 * Author: gareth
 *
 * Created on March 29, 2013, 8:58 PM
 */

#ifndef CONTAINERTYPES_H
#define	CONTAINERTYPES_H

#include <vector>

namespace ModFossa {

typedef std::vector<double> Vector;
typedef std::vector<std::vector<double > > Vector2d;
typedef std::vector<Vector2d> Vector3d;
typedef std::vector<Vector3d> Vector4d;
};

#endif	/* CONTAINERTYPES_H */

