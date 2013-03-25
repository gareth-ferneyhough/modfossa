#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
namespace ModFossa
{

using boost::make_shared;
    
template <typename T>
struct shared_ptr {
    typedef boost::shared_ptr<T> type;
};
}

#endif