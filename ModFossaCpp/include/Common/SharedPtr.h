#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <memory>
namespace ModFossa
{
template <typename T>
struct shared_ptr {
    typedef std::shared_ptr<T> type;
};
}

#endif