//
// Created by JAN on 2022/4/15.
//

#ifndef ALGORITHMWITHCPP_ARRAYLIST_H
#define ALGORITHMWITHCPP_ARRAYLIST_H

#include <algorithm>
#include <sstream>
#include <exception>
#include <iterator>
#include "qimg_algorithm.h"
namespace qimg
{
/**
 * 对一个线性表的基本定义，所有的线性表都要继承这个纯虚基类
 * @tparam T
 */
template <typename T>
class linearList
{
public:
    virtual ~linearList() = default;
    virtual int index_of(const T & val) const = 0;
    virtual bool empty() const = 0;
    virtual unsigned size() const = 0;
    virtual T & get(unsigned index) const = 0;
    virtual void erase(unsigned index) = 0;
    virtual void insert(unsigned index,const  T& val) = 0;
    virtual void output(std::ostream & os) const = 0;
};

template <typename T> class linear_iterator;

/**
 * 以数组组织的线性表，public 继承于  linearList<T>
 * @tparam T
 */
template <typename T>
class ArrayList : public linearList<T>
{
protected:
    T * arr;         //指向一维数组的指针
    unsigned _size;   //元素数量
    unsigned _capacity;  //容器组最大装载大小
    void check_index(unsigned index) const;
public:
    using iterator = linear_iterator<T>;

    void add(const T & val);

    explicit ArrayList(unsigned init = 10);

    ArrayList(const std::initializer_list<T> & ls)
    : ArrayList(ls.size() + 10)
    {
        _size = ls.size();
        std::copy(ls.begin(),ls.end(),begin());
    }

    ArrayList(const ArrayList<T>&);

    iterator begin() const
    {
        return iterator(arr);
    }

    iterator end() const
    {
        return iterator (arr + _size);
    }

    /**
     * 返回索引为index的元素的引用，如果下标不合法将抛出一个out_of_range异常
     * @param index
     * @return 索引为index元素的引用
     */
    T &get(const unsigned index) const override {
        check_index(index);
        return arr[index];
    }

    T & operator[](const unsigned index) const
    {
        return get(index);
    }
    bool empty() const override
    {
        return _size == 0;
    }

    unsigned int size() const override
    {
        return _size;
    }

    ~ArrayList() override
    {
        delete []arr;
    }

    unsigned capacity() const
    {
        return _capacity;
    }


    int index_of(const T &val) const override;

    void erase(unsigned int index) override;

    void output(std::ostream &os) const override;

    void insert(unsigned int index, const T & val) override;


};

/**
 * 构造函数，开辟init_cap大小的空间
 * @tparam T
 * @param init_cap
 */
template<typename T>
ArrayList<T>::ArrayList(const unsigned init_cap) : _size(0)
{
    if(init_cap <= 0)
    {
        arr = nullptr;
        _capacity = 0;
        return;
    }
    _capacity = init_cap;
    arr = new T[init_cap];
}

/**
 * 拷贝构造
 * @tparam T
 * @param rhs
 */
template<typename T>
ArrayList<T>::ArrayList(const ArrayList<T> & rhs)
    : _size(rhs._size), _capacity(rhs._capacity)
{
    arr = new T[_capacity];
    std::copy(rhs.arr,rhs.arr+_size,arr);
}

/**
 * 检查index是否合法，如果不合法的话会抛出一个out_of_range
 * @tparam T
 * @param index
 */
template<typename T>
void ArrayList<T>::check_index(const unsigned int index) const
{
    if(index < 0 || index >= _size)
    {
        std::ostringstream s;
        s << "index = " << index << " size=" << _size;
        throw std::out_of_range(s.str());
    }
}



/**
 * 寻找val的索引
 * @tparam T
 * @param val
 * @return 找到元素返回其索引下标，没有找到返回-1
 */
template<typename T>
inline int ArrayList<T>::index_of(const T &val) const {
    using std::find;
    int ret = (int)(find(arr,arr+_size,val) - arr);
    if(ret == _size) return -1;
    else return ret;
}


/**
 * 删除在index位置的元素
 * @tparam T
 * @param index
 */
template<typename T>
inline void ArrayList<T>::erase(const unsigned int index) {
    check_index(index);
    --_size;
    for(unsigned i=index;i<_size;++i)
    {
        arr[i] = arr[i+1];
    }
}

/**
 * 将arr, arr+ _size通过os输出
 * @tparam T
 * @param os
 * @param ls
 * @return
 */
    template<typename T>
    std::ostream &operator<<(std::ostream &os, const ArrayList<T> &ls) {
        ls.output(os);
        return os;
    }


/**
 * 将arr, arr+_size复制到输出流os中
 * @tparam T
 * @param os
 */
template<typename T>
inline void ArrayList<T>::output(std::ostream &os) const {
    std::ostream_iterator<T> out(os," ");
    std::copy(arr,arr+_size,out);
}



/**
 * 将对val象插入到index的位置
 * @tparam T
 * @param index
 * @param val
 */
template<typename T>
void ArrayList<T>::insert(const unsigned int index, const T & val) {
    if(index < 0 || index > _size)
    {
        std::ostringstream s;
        s << "index = " << index << " size=" << _size;
        throw std::out_of_range(s.str());
    }
    if(_size == _capacity)
    {
        unsigned new_capacity = _capacity ? 2 * _capacity : 1;
        change_length_1d(arr,_capacity,
                         new_capacity);
        _capacity = new_capacity;
    }
    std::move_backward(arr+index,arr+_size,arr+index+1);
    ++_size;
    arr[index] = val;
}



/**
 * 在容器末尾添加一个对象val
 * @tparam T
 * @param val
 */
template <typename T>
inline void ArrayList<T>::add(const T &val)
{
    insert(_size,val);
}

/**
 * 基于数组组织的迭代器的通用表示
 * @tparam T
 */
template <typename T>
class linear_iterator
{
public:
    explicit linear_iterator(T *point = nullptr) : point(point){ }
    using iter = linear_iterator<T>;

    iter& operator++()
    {
        ++point;
        return *this;
    }

    const iter operator++(int)
    {
        iter ret = *this;
        ++point;
        return ret;
    }

    T& operator*() const
    {
        return *point;
    }

    iter & operator--()
    {
        --point;
        return *this;
    }

    const iter operator--(int)
    {
        iter ret = *this;
        --point;
        return ret;
    }

    bool operator==(const iter & rhs) const
    {
        return point == rhs.point;
    }

    bool operator!=(const iter & rhs) const
    {
        return point != rhs.point;
    }

protected:
    T * point;
};


}   //namespace qimg end


#endif //ALGORITHMWITHCPP_ARRAYLIST_H
