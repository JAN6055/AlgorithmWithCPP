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
 * �Ը��������������ǰn��Ԫ�س���val�����ļ���
 * @tparam T
 * @param arr
 * @param val
 * @param n
 * @return long ���ֵĴ���
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
 * �Ե�����ָ���Ԫ�غ�nλ����val�Ĵ����ļ���
 * @tparam Beg
 * @tparam Val
 * @param _beg
 * @param val
 * @param n
 * @return long ���ֵĴ���
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
 * ������������������ڵ�Ԫ��Ϊval
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
 * i ~ i+n-1 �ۼ� a[i]*b[i]
 * @tparam Iter
 * @param _fbeg ָ��a�����ĵ�����
 * @param _sbeg ָ��b�����ĵ�����
 * @param n
 * @return ������ָ�������˵�����
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
 * �ж�ĳ�������Ƿ��Ѿ�����
 * @tparam Iter
 * @param _beg
 * @param n
 * @return ����Ѿ����򷵻�true, ���򷵻�false
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
 * ����arr1[i] != arr2[i]����������С����
 * @tparam T1
 * @tparam T2
 * @tparam N
 * @tparam M
 * @param arr1
 * @param arr2
 * @return ��С����ֵ������������������������س��Ƚ�С���Ǹ�����ĳ���
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
 * ����һ��2darr, Ϊ�䶯̬�����i�еĿռ�Ϊ _size[i]
 * @tparam T
 * @param _2darr
 * @param rows
 * @param _size
 * @return ���ٿռ�ɹ�����true ���򷵻�false
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
 * ����һ��2darr, Ϊ�䶯̬����rows * cols���ڴ�ռ�
 * @tparam T
 * @param _2darr
 * @param rows
 * @param cols
 * @return ���ٿռ�ɹ�����true ���򷵻�false
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
 * ����һ��һά����arr�ĳ��Ȳ���ԭ�е�Ԫ�ظ��Ƶ���������,
 * ���new length = 0, arr��ָ��nullptr
 * @tparam T
 * @param arr
 * @param old_length
 * @param new_length
 * @return ��̬���ٳɹ�����true�����򷵻�false
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
 * ���·���һ����ά��̬����Ŀռ䲢��ԭ�е�Ԫ�ظ��Ƶ���������
 * ����ÿ��һά����,��ѭchange_length_1d�Ĺ���
 * @tparam T
 * @param _2darr
 * @param old_rows
 * @param old_cols
 * @param new_rows
 * @param new_cols
 * @return ̬���ٳɹ�����true�����򷵻�false
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
 * ����һ����ά���飬��������Ķ���ָ��ָ��nullptr
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
 * �ݹ鷨�� list (k,m]�����ڵ�ȫ����
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
 * ���������������������Ӽ�������β������Ϊstart, _end
 * �ݹ鷨�����������������(_beg, _end]��Ԫ�ص�ȫ����
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
 * �ݹ鷨��׳�
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
 * �ݹ鷨������Լ��
 * @tparam Tp
 * @param x
 * @param y
 * @return ���Լ��
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
 * �ݹ鷽���ж�һ��Ԫ���Ƿ���һ�������У�������ʹ��
 * @tparam Tp
 * @param arr
 * @param n
 * @param val
 * @param i
 * @return ���ڷ���true, ���򷵻�false
 */
template <typename Tp>
bool is_have(const Tp arr[],const int n, const Tp & val, const size_t i = 0)
{
    if(i == n) return false;
    if(val == arr[i]) return true;
    return is_have(arr,n,val,i+1);
}

/**
 * ����ȫ��Ϊarr[0] - arr[i]
 * ʹ��bool�������ȫ���������Ӽ�
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
