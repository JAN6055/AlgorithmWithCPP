//
// Created by JAN on 2022/4/21.
//

#ifndef ALGORITHMWITHCPP_STACK_H
#define ALGORITHMWITHCPP_STACK_H
#include "arraylist.h"

namespace qimg{

    /**
     * 利用私有继承ArrayList组织的栈
     * @tparam T
     */
    template<typename T>
    class stack_arr : private qimg::ArrayList<T>
    {
    private:
        using arr = ArrayList<T>;
    public:
        explicit stack_arr(int n = 0);
        bool empty() const { return arr::empty(); }
        unsigned int size() const { return arr::size(); }
        T & top() const;
        void pop();
        void push(const T & val);
    };

    template <typename T>
    stack_arr<T>::stack_arr(int n) : arr(n)
    { }

    template <typename T>
    T &stack_arr<T>::top() const {
        if(!empty())
            return arr::get(size() -1);
    }

    template <typename T>
    void stack_arr<T>::pop() {
        if(!empty())
            arr::erase(size()-1);
    }

    template<typename T>
    void stack_arr<T>::push(const T & val) {
        arr::add(val);
    }


}   //namespace qimg end

#endif //ALGORITHMWITHCPP_STACK_H
