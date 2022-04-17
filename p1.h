//
// Created by JAN on 2022/4/15.
//

#ifndef ALGORITHMWITHCPP_P1_H
#define ALGORITHMWITHCPP_P1_H
#include <iostream>
#include <iterator>
namespace qimg
{

/**
 * 对给定类型数组进行前n个元素出现val次数的计数
 * @tparam T
 * @param arr
 * @param val
 * @param n
 * @return long 出现的次数
 */
template <typename T,size_t N>
long count(const T (&arr)[N],const T val, const long n)
{
    if(n < 1) throw "argument n is less 1";
    long ret = 0;
    for(int i=0;i<n;++i)
    {
        if(arr[i] == val) ++ret;
    }
    return ret;
}

/**
 * 对迭代器指向的元素后n位出现val的次数的计数
 * @tparam Beg
 * @tparam Val
 * @param _beg
 * @param val
 * @param n
 * @return long 出现的次数
 */
template <typename Beg, typename Val>
inline long count(Beg _beg,const Val &val,long n)
{
    if(n < 1) throw "argument n is less 1";
    long ret = 0;
    for (int i = 0; i < n; ++i) {
        if(*_beg == val) ++ret;
        ++_beg;
    }
    return ret;
}

/**
 * 填充两个迭代器区间内的元素为val
 * @tparam Beg
 * @tparam End
 * @tparam Val
 * @param _beg
 * @param _end
 * @param val
 * @return void
 */
template <typename Iter, typename Val>
inline void fill(Iter  _beg, Iter  _end,const Val & val)
{
    while(_beg != _end)
    {
        *_beg = val;
        ++_beg;
    }
}

/**
 * i ~ i+n-1 累加 a[i]*b[i]
 * @tparam Iter
 * @param _fbeg 指向a容器的迭代器
 * @param _sbeg 指向b容器的迭代器
 * @param n
 * @return 迭代器指向对象相乘的类型
 */
template <typename Iter>
auto inner_product(Iter _fbeg, Iter _sbeg, long n) -> decltype(*_fbeg * *_sbeg)
{
    decltype(*_fbeg * *_sbeg) ret = 0;
    while(n--)
    {
        ret += (*_fbeg * *_sbeg);
        ++_fbeg;
        ++_sbeg;
    }
    return ret;
}

/**
 * 判断某个数组是否已经排序
 * @tparam Iter
 * @param _beg
 * @param n
 * @return 如果已经排序返回true, 否则返回false
 */
template <typename Iter>
bool is_sorted(Iter _beg, long n)
{
    bool _less = false;
    bool _greater = false;
    for(int i=0;i<n-1;++i)
    {
        if(*_beg < *(_beg +1)) _less = true;
        if(*_beg > *(_beg +1)) _greater = true;
        if(_less && _greater) return false;
        ++_beg;
    }
    return true;
}

/**
 * 计算arr1[i] != arr2[i]不成立的最小索引
 * @tparam T1
 * @tparam T2
 * @tparam N
 * @tparam M
 * @param arr1
 * @param arr2
 * @return 最小索引值，若不存在这样的情况，返回长度较小的那个数组的长度
 */
template <typename T1, typename T2,size_t N, size_t M>
size_t mismatch(T1 (&arr1)[N], T2(&arr2)[M])
{
    size_t _min = std::min(N,M);
    int i = 0;
    for(;i<_min;++i)
    {
        if(arr1[i] != arr2[i]) break;
    }
    return i;
}

/**
 *
 * @tparam Tp
 * @param arr
 * @param n
 */
template <typename Tp>
void iota(Tp arr, size_t n)
{
    for(int i=0;i<n;++i)
    {
        arr[i] += i;
    }
}

/**
 * 给定一个2darr, 为其动态分配第i行的空间为 _size[i]
 * @tparam T
 * @param _2darr
 * @param rows
 * @param _size
 * @return 开辟空间成功返回true 否则返回false
 */
template <typename T>
bool make2dArray(T ** & _2darr,int rows,int * const _size)
{
    try{
        _2darr = new T* [rows];
        for(int i=0;i<rows;++i)
        {
            _2darr[i] = new T[_size[i]];
        }
        return true;
    }catch (std::bad_alloc & bad_alloc)
    {
        return false;
    }
}

/**
 * 给定一个2darr, 为其动态开辟rows * cols的内存空间
 * @tparam T
 * @param _2darr
 * @param rows
 * @param cols
 * @return 开辟空间成功返回true 否则返回false
 */
template <typename T>
bool make2dArray(T ** & _2darr,const  int rows,const int cols)
{
    try{
        _2darr = new T* [rows];
        for(int i=0;i<rows;++i)
            _2darr[i] = new T[cols];
        return true;
    }catch (std::bad_alloc & bad_alloc)
    {
        return false;
    }
}

/**
 * 更改一个一维数组arr的长度并将原有的元素复制到新数组中,
 * 如果new length = 0, arr将指向nullptr
 * @tparam T
 * @param arr
 * @param old_length
 * @param new_length
 * @return 动态开辟成功返回true，否则返回false
 */
template <typename T>
bool change_length_1d(T* &arr,const int old_length,const int new_length)
{
    if(new_length < 0)
        throw "the new length must be >= 0";
    if(new_length == 0)
    {
        delete []arr;
        arr = nullptr;
        return true;
    }
    T* temp = arr;
    try{
        arr = new T[new_length];
    } catch (std::bad_alloc & bad_alloc) {
        return false;
    }
    int _min = std::min(old_length,new_length);
    std::copy(temp,temp+_min,arr);
    delete []temp;
    return true;
}

template <typename T> void delete_arr_2d(T** & arr, int rows);

/**
 * 重新分配一个二维动态数组的空间并将原有的元素复制到新数组中
 * 对于每个一维数组,遵循change_length_1d的规则
 * @tparam T
 * @param _2darr
 * @param old_rows
 * @param old_cols
 * @param new_rows
 * @param new_cols
 * @return 态开辟成功返回true，否则返回false
 */
template <typename T>
bool change_length_2d(T** & _2darr, const int old_rows, const int * const old_cols,
                      const int new_rows, const int * const new_cols)
{
    int _min = std::min(old_rows,new_rows);
    T** temp = _2darr;
    _2darr = new T* [new_rows];
    std::copy(temp,temp+_min,_2darr);
    int i=0;
    for(;i<_min;++i)
    {
        if(!change_length_1d(_2darr[i],old_cols[i],new_cols[i]))
            return false;
    }
    try{
        for(int j = i;j<new_rows; ++j)
        {
            _2darr[i] = new T[new_cols[j]];
        }
    }catch (...) {
        return false;
    }
    delete_arr_2d(temp,old_rows);
}

/**
 * 析构一个二维数组，将析构后的二级指针指向nullptr
 * @tparam T
 * @param arr
 * @param rows
 * @return nothing
 */
template <typename T>
inline void delete_arr_2d(T** & arr, int rows)
{
    for(int i=0;i<rows;++i)
        delete [] arr[i];
    delete[] arr;
    arr = nullptr;
}

/**
 * 递归法求 list (k,m]区间内的全排列
 * @tparam T
 * @param list
 * @param k int
 * @param m int
 * @return nothing
 */
template <typename T>
void permutations(T list[], int k, int m)
{
    if(k == m-1)
    {
        std::copy(list,list+m,
                  std::ostream_iterator<T> (std::cout," "));
        std::cout << std::endl;
    }
    else
    {
        for(int i=k;i<m;++i)
        {
            std::swap(list[i],list[k]);
            permutations(list,k+1,m);
            std::swap(list[i],list[k]);
        }
    }
}

/**
 * 此容器（或者是容器的子集）的首尾迭代器为start, _end
 * 递归法求此容器迭代器区间(_beg, _end]内元素的全排列
 * @tparam Iter
 * @param start
 * @param _beg
 * @param _end
 * @return nothing
 */
template <typename Iter>
void permutations(Iter start, Iter _beg, Iter _end)
{
    if(_beg == _end-1)
    {
        std::copy(start, _end,
                  std::ostream_iterator<decltype(*_beg)> (std::cout, " "));
        std::cout << std::endl;
    }
    else
    {
        for(auto it = _beg;it != _end;++it)
        {
            std::swap(*_beg,*it);
            permutations(start,_beg + 1,_end);
            std::swap(*_beg,*it);
        }
    }
}

/**
 * 递归法求阶乘
 * @tparam Tp
 * @param n
 * @return n!
 */
template <typename Tp>
Tp factorial_rec(Tp & n)
{
    return n *factorial_rec(n-1);
}

template <typename Tp>
inline Tp factorial(Tp n)
{
    Tp ret = 1;
    while(static_cast<bool>(n))
    {
        ret *= n--;
    }
    return ret;
}

/**
 * 递归法求解最大公约数
 * @tparam Tp
 * @param x
 * @param y
 * @return 最大公约数
 */
template <typename Tp>
Tp __gcd_rec_(Tp x, Tp y)
{
    if(y == 0)
        return x;
    else
        return __gcd_rec_(y, x % y);
}

/**
 * 递归方法判断一个元素是否在一个序列中，不建议使用
 * @tparam Tp
 * @param arr
 * @param n
 * @param val
 * @param i
 * @return 存在返回true, 否则返回false
 */
template <typename Tp>
bool is_have(const Tp arr[],const int n, const Tp & val, const size_t i = 0)
{
    if(i == n) return false;
    if(val == arr[i]) return true;
    return is_have(arr,n,val,i+1);
}

/**
 * 假设全集为arr[0] - arr[i]
 * 使用bool数组计算全集的所有子集
 * @param arr
 * @param n
 * @param i
 * @return nothing
 */
void subset(bool arr[],const int n,const int i = 0)
{
    if(i == n)
    {
        std::copy(arr,arr+i,
                  std::ostream_iterator<bool> (std::cout, " "));
        std::cout << std::endl;
        return;
    }
    for(int j=0;j<=1;++j)
    {
        arr[i] = j;
        subset(arr, n,i+1);
    }
}

}   //namespace qimg end

#endif //ALGORITHMWITHCPP_P1_H
