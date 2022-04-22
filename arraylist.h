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
 * ��һ�����Ա�Ļ������壬���е����Ա�Ҫ�̳�����������
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
 * ��������֯�����Ա�public �̳���  linearList<T>
 * @tparam T
 */
template <typename T>
class ArrayList : public linearList<T>
{
protected:
    T * arr;         //ָ��һά�����ָ��
    unsigned _size;   //Ԫ������
    unsigned _capacity;  //���������װ�ش�С
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
     * ��������Ϊindex��Ԫ�ص����ã�����±겻�Ϸ����׳�һ��out_of_range�쳣
     * @param index
     * @return ����ΪindexԪ�ص�����
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
 * ���캯��������init_cap��С�Ŀռ�
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
 * ��������
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
 * ���index�Ƿ�Ϸ���������Ϸ��Ļ����׳�һ��out_of_range
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
 * Ѱ��val������
 * @tparam T
 * @param val
 * @return �ҵ�Ԫ�ط����������±꣬û���ҵ�����-1
 */
template<typename T>
inline int ArrayList<T>::index_of(const T &val) const {
    using std::find;
    int ret = (int)(find(arr,arr+_size,val) - arr);
    if(ret == _size) return -1;
    else return ret;
}


/**
 * ɾ����indexλ�õ�Ԫ��
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
 * ��arr, arr+ _sizeͨ��os���
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
 * ��arr, arr+_size���Ƶ������os��
 * @tparam T
 * @param os
 */
template<typename T>
inline void ArrayList<T>::output(std::ostream &os) const {
    std::ostream_iterator<T> out(os," ");
    std::copy(arr,arr+_size,out);
}



/**
 * ����val����뵽index��λ��
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
 * ������ĩβ���һ������val
 * @tparam T
 * @param val
 */
template <typename T>
inline void ArrayList<T>::add(const T &val)
{
    insert(_size,val);
}

/**
 * ����������֯�ĵ�������ͨ�ñ�ʾ
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
