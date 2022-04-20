//
// Created by JAN on 2022/4/19.
//
/**
 * 此文件用于个人学习，其中很多矩阵类并不完善，仅仅写出其行主映射组织的get，set方法
 */
#ifndef ALGORITHMWITHCPP_MATRIX_H
#define ALGORITHMWITHCPP_MATRIX_H
#include <iostream>
#include <exception>
#include <algorithm>
namespace qimg{

    /**
    * 求解n维数组的实际内存大小的递归方程
    * @param length_arr 矩阵的对应维数的长度例如arr[2][3][4], length_arr = {2, 3, 4}
    * @param n 矩阵维数
    * @param base_num 类型所占字节数, 默认为sizeof int
    * @param i 用户无需提供，也禁止提供，递归中确定基线的值
    * @return 返回其所占字节数
    */
    size_t get_arr_size(int * length_arr,const int n, const int base_num = sizeof (int),int i=0)
    {
        if(i == n-1)
            return length_arr[i] * base_num;
        else
            return base_num * length_arr[i] + length_arr[i] * get_arr_size(length_arr,n,base_num,i+1);
    }

    template <typename T> class matrix;
    template <typename T>
    std::ostream & operator<<(std::ostream & os, const matrix<T> & m);

    template <typename T>
    class matrix
    {
        friend std::ostream & operator<< <T> (std::ostream& os, const matrix<T> & m);
    public:
        explicit matrix(int rows = 0, int cols = 0);
        matrix(const matrix<T> & m);
        ~matrix() { delete element; }
        int rows() const { return _rows; }
        int cols() const { return _cols; }
        T & operator()(int i, int j) const;
        matrix<T> & operator=(const matrix<T> & m);
        matrix<T>   operator+(const matrix<T> & m) const;
        matrix<T>   operator-(const matrix<T> & m) const;
        matrix<T>   operator*(const matrix<T> & m) const;
        matrix<T> & operator+=(const matrix<T> & m);

    private:
        int _rows;
        int _cols;
        T * element;
    };

    /**
     * 构造函数，构造一个rows * cols大小的矩阵
     * 如果参数不合法会抛出std::invalid_argument异常
     * @tparam T
     * @param rows
     * @param cols
     */
    template<typename T>
    matrix<T>::matrix(int rows, int cols)
    {
        if(rows <= 0 || cols <= 0 )
            throw std::invalid_argument("rows or cols must be > 0");
        _rows = rows;
        _cols = cols;
        element = new T[_rows * _cols];
    }

    /**
     * 构造一个m矩阵
     * @tparam T
     * @param m
     */
    template<typename T>
    matrix<T>::matrix(const matrix<T> &m)
    {
        T * _keep = element;
        element = new T[m._rows * m._cols];
        delete []_keep;
        _rows = m._rows;
        _cols = m._cols;
        std::copy(m.element,m.element + _rows * _cols,this->element);
    }

    /**
     * 将矩阵m赋值给*this
     * @tparam T
     * @param m
     * @return
     */
    template <typename T>
    matrix<T> &matrix<T>::operator=(const matrix<T> &m)
    {
        if(this == &m)
            return *this;
        element = new T[m._cols * m._rows];
        _rows = m._rows;
        _cols = m._cols;
        std::copy(m.element, m.element + _rows * m._cols, this->element);
        return *this;
    }

    /**
     * 获得矩阵[row][col]处的元素，从1开始计数
     * @tparam T
     * @param i
     * @param j
     * @return
     */
    template <typename T>
    T & matrix<T>::operator()(const int i,const  int j) const
    {
        if(i<=0 || j<=0 || i > _rows || j > _cols)
            throw std::invalid_argument
            ("rows num or cols num must be > 0 and <= _rows / cols");
        return element[(i-1) * _cols + j-1];
    }

    /**
     * 矩阵加法
     * @tparam T
     * @param m
     * @return 相加后的矩阵
     */
    template <typename T>
    matrix<T> matrix<T>::operator+(const matrix<T> &m) const
    {
        if(_rows != m._rows || _cols != m._cols)
            throw std::invalid_argument("two matrix can not add");
        matrix<T> ret(_rows,_cols);
        for(int i=0;i<_rows * _cols;++i)
            ret.element[i] = element[i] + m.element[i];
        return ret;
    }

    /**
     * 矩阵乘法
     * @tparam T
     * @param m
     * @return 相乘后的矩阵
     */
    template <typename T>
    matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
        if(_cols != m._rows)
            throw std::invalid_argument("this->_cols != rhs._rows");
        matrix<T> ret(_rows,m._cols);

        int ct = 0, cm  =0, cw = 0;

        //逐一计算ret[i][j]
        for(int i=1;i<=_rows;++i)
        {
            for(int j =1;j<=m._cols;++j)
            {
                //为了避免初始化的麻烦，先将sum初始化为两个元素的相乘的结果
                //所以对应的k循环中应是k = 2 to _cols
                T sum = element[ct] * m.element[cm];
                for(int k = 2;k<=_cols;++k)
                {
                    ++ct; //i行的下一项
                    cm += m._cols; //j列的下一项
                    // c[i][j] = this[rows][n] * [n][cols]
                    sum += element[ct] * m.element[cm];
                }
                ret.element[cw++] = sum; //赋值ret[i][j]
                ct -= _cols  -1; //更新ct归位
                cm = j;     //更新cm到下一列
            }
            ct += _cols;    //更新ct到下一行
            cm = 0;         //更新cm归位
        }
        return ret;
    }

    /**
     * 将矩阵写入到输出流os中
     * @tparam T
     * @param os
     * @param m
     * @return os
     */
    template <typename T>
    std::ostream & operator<<(std::ostream & os, const matrix<T> & m)
    {
        using namespace std;
        for(int i=1;i <= m._rows * m._cols;++i)
        {
            os << m.element[i-1] << "\t";
            if(!(i % m._cols))
                os << endl;
        }
        return os;
    }

    /**
     * 矩阵的operator+=运算符
     * @tparam T
     * @param m
     * @return *this(&)
     */
    template <typename T>
    matrix<T> &matrix<T>::operator+=(const matrix<T> &m) {
        if(_rows != m._rows || _cols != m._cols)
            throw std::invalid_argument("two matrix can not add");
        for(int i=0;i<_rows*_cols;++i)
            element[i] += m.element[i];
        return *this;
    }

    /**
     * 矩阵减法
     * @tparam T
     * @param m
     * @return 相减后的矩阵
     */
    template <typename T>
    matrix<T> matrix<T>::operator-(const matrix<T> &m) const {
        if(_rows != m._rows || _cols != m._cols)
            throw std::invalid_argument("Two matrices cannot be subtracted");
        matrix<T> ret(_rows,_cols);
        for(int i=0;i<_rows*_cols;++i)
            ret.element[i] = element[i] = m.element[i];
        return ret;
    }

    template <typename T> class diagonal_matrix;
    template <typename T>
    std::ostream & operator<<(std::ostream & os, const diagonal_matrix<T> & m);

    /**
     * 对角矩阵，仅仅写了一些映射操作
     * @tparam T
     */
    template <typename T>
    class diagonal_matrix
    {
        friend std::ostream & operator<< <T>(std::ostream & os, const diagonal_matrix<T> & m);
    private:
        int _n;
        T * element;
    public:
        explicit diagonal_matrix(int n);
        T & get(int i, int j) const;
        void set(int i, int j, const T & val);
        ~diagonal_matrix();
    };

    /**
     * 对角矩阵构造函数，设置矩阵维数位n
     * @tparam T
     * @param n
     */
    template <typename T>
    diagonal_matrix<T>::diagonal_matrix(int n)
    {
        if(n <= 0)
            throw std::invalid_argument("the matrix dimension must be >= 0");
        _n = n;
        element = new T[n];
    }

    /**
     * 获得i，j位元素的引用
     * @tparam T
     * @param i
     * @param j
     * @return 第i，j位元素的引用
     */
    template <typename T>
    T &diagonal_matrix<T>::get(int i, int j) const
    {
        if(i <=0 || j<=0 || i > _n || j > _n)
            throw std::out_of_range("need i <=0 || j<=0 || i > _n || j > _n");
        if(i == j)
            return element[i];
        else
            return 0;
    }

    /**
     * 将第i，j位的元素赋值
     * @tparam T
     * @param i
     * @param j
     * @param val
     * @return nothing
     */
    template <typename T>
    void diagonal_matrix<T>::set(int i, int j, const T &val)
    {
        if(i <=0 || j<=0 || i > _n || j > _n)
            throw std::out_of_range("need i <=0 || j<=0 || i > _n || j > _n");
        if(i == j)
            element[i-1] = val;
        else
            if(val != 0)
                throw std::invalid_argument
                ("if new val is not on the diagonal it must is zero");
    }

    /**
     * 将矩阵写入到输出流os中
     * @tparam T
     * @param os
     * @param m
     * @return os(&)
     */
    template <typename T>
    std::ostream & operator<<(std::ostream & os, const diagonal_matrix<T> & m)
    {
        for(int i=1;i<=m._n;++i){
            for(int j=1;j<=m._n;++j)
            {
                if(j == i)
                    os << m.element[i-1] << "\t";
                else
                    os << 0 << "\t";
                if(!(j % m._n))
                    os << std::endl;
            }
        }
        return os;
    }

    /**
     * 对角矩阵的析构函数
     * @tparam T
     */
    template <typename T>
    diagonal_matrix<T>::~diagonal_matrix<T>(){
        delete []element;
    }

    template <typename T> class three_diagonal_matrix;
    template <typename T>
    std::ostream & operator<<(std::ostream & os, const three_diagonal_matrix<T> & m);

    /**
     * 三对角矩阵
     * @tparam T
     */
    template <typename T>
    class three_diagonal_matrix
    {
        friend std::ostream & operator<< <T>(std::ostream & os,
                                             const three_diagonal_matrix<T> & m);
    private:
        T * element;
        int _n;
    public:
        explicit three_diagonal_matrix(int n);
        T & get(int i, int j) const;
        void set(int i, int j, const T & val);
        ~three_diagonal_matrix();
    };

    /**
     * 构造一个n维的三对角矩阵
     * @tparam T
     * @param n
     */
    template<typename T>
    three_diagonal_matrix<T>::three_diagonal_matrix(int n) : element(new T[3 * n - 2]), _n(n)
    { }

    /**
     * 得到i，j位元素
     * @tparam T
     * @param i
     * @param j
     * @return i，j位元素的引用
     */
    template<typename T>
    T & three_diagonal_matrix<T>::get(int i, int j) const{
        static int zero =0;
        if(i <=0 || j <= 0 || i > _n || j > _n)
            throw std::out_of_range("need i <=0 || j <= 0 || i > _n || j > _n");
        switch (i-j) {
            case 1:
                return element[i-2];
            case 0:
                return element[_n + i - 2]; // n-1+i-1
            case -1:
                return element[2 * _n + i -2]; //2n-1+i-1
            default:
                return zero;
        }
    }

    /**
     * 将i，j位赋值为val
     * @tparam T
     * @param i
     * @param j
     * @param val
     * @return nothing
     */
    template<typename T>
    void three_diagonal_matrix<T>::set(int i, int j, const T &val) {
        if(abs(i - j)>1)
                throw std::invalid_argument("don't set zero to be any other num");
        get(i,j) = val;
    }

    /**
     * 析构函数
     * @tparam T
     */
    template<typename T>
    three_diagonal_matrix<T>::~three_diagonal_matrix() {
        delete []element;
    }

    /**
     * 将三对角矩阵写入到输出流os中
     * @tparam T
     * @param os
     * @param m
     * @return os(&)
     */
    template<typename T>
    std::ostream & operator<<(std::ostream & os, const three_diagonal_matrix<T> & m)
    {
        for(int i=1;i<=m._n;++i)
        {
            for(int j=1;j<=m._n;++j)
            {
                if(abs(i - j) <= 1)
                    os << m.get(i,j) << "\t";
                else
                    os << 0 << "\t";
            }
            os << std::endl;
        }
        return os;
    }


}   //namespace qimg end
#endif //ALGORITHMWITHCPP_MATRIX_H

