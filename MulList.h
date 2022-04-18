//
// Created by JAN on 2022/4/17.
//

#ifndef ALGORITHMWITHCPP_MULLIST_H
#define ALGORITHMWITHCPP_MULLIST_H
#include "p3.h"
#include <memory>
namespace qimg
{

    template <typename T>
    class MulList : public linearList<T>
    {
    private:
        int _size;
        int _cap;
        std::shared_ptr<T> arr;
        std::shared_ptr<int> first;
        std::shared_ptr<int> last;
        int _part;
    public:
        MulList(const int length, const int part)
        : _size(0), _cap(length), arr(new T[length]),
        first(new int[part + 1]), last(new int[part + 1]), _part(part)
        {
            first.get()[0] = last.get()[0] = -1;
        }

        MulList(const MulList<T> & rhs) : MulList(rhs._size, rhs._part)
        { }


        ~MulList() = default;


    };


}

#endif //ALGORITHMWITHCPP_MULLIST_H
