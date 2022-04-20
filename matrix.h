//
// Created by JAN on 2022/4/19.
//
/**
 * ���ļ����ڸ���ѧϰ�����кܶ�����ಢ�����ƣ�����д��������ӳ����֯��get��set����
 */
#ifndef ALGORITHMWITHCPP_MATRIX_H
#define ALGORITHMWITHCPP_MATRIX_H
#include <iostream>
#include <exception>
#include <algorithm>
namespace qimg{

    /**
    * ���nά�����ʵ���ڴ��С�ĵݹ鷽��
    * @param length_arr ����Ķ�Ӧά���ĳ�������arr[2][3][4], length_arr = {2, 3, 4}
    * @param n ����ά��
    * @param base_num ������ռ�ֽ���, Ĭ��Ϊsizeof int
    * @param i �û������ṩ��Ҳ��ֹ�ṩ���ݹ���ȷ�����ߵ�ֵ
    * @return ��������ռ�ֽ���
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
     * ���캯��������һ��rows * cols��С�ľ���
     * ����������Ϸ����׳�std::invalid_argument�쳣
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
     * ����һ��m����
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
     * ������m��ֵ��*this
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
     * ��þ���[row][col]����Ԫ�أ���1��ʼ����
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
     * ����ӷ�
     * @tparam T
     * @param m
     * @return ��Ӻ�ľ���
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
     * ����˷�
     * @tparam T
     * @param m
     * @return ��˺�ľ���
     */
    template <typename T>
    matrix<T> matrix<T>::operator*(const matrix<T> &m) const {
        if(_cols != m._rows)
            throw std::invalid_argument("this->_cols != rhs._rows");
        matrix<T> ret(_rows,m._cols);

        int ct = 0, cm  =0, cw = 0;

        //��һ����ret[i][j]
        for(int i=1;i<=_rows;++i)
        {
            for(int j =1;j<=m._cols;++j)
            {
                //Ϊ�˱����ʼ�����鷳���Ƚ�sum��ʼ��Ϊ����Ԫ�ص���˵Ľ��
                //���Զ�Ӧ��kѭ����Ӧ��k = 2 to _cols
                T sum = element[ct] * m.element[cm];
                for(int k = 2;k<=_cols;++k)
                {
                    ++ct; //i�е���һ��
                    cm += m._cols; //j�е���һ��
                    // c[i][j] = this[rows][n] * [n][cols]
                    sum += element[ct] * m.element[cm];
                }
                ret.element[cw++] = sum; //��ֵret[i][j]
                ct -= _cols  -1; //����ct��λ
                cm = j;     //����cm����һ��
            }
            ct += _cols;    //����ct����һ��
            cm = 0;         //����cm��λ
        }
        return ret;
    }

    /**
     * ������д�뵽�����os��
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
     * �����operator+=�����
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
     * �������
     * @tparam T
     * @param m
     * @return �����ľ���
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
     * �ԽǾ��󣬽���д��һЩӳ�����
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
     * �ԽǾ����캯�������þ���ά��λn
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
     * ���i��jλԪ�ص�����
     * @tparam T
     * @param i
     * @param j
     * @return ��i��jλԪ�ص�����
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
     * ����i��jλ��Ԫ�ظ�ֵ
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
     * ������д�뵽�����os��
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
     * �ԽǾ������������
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
     * ���ԽǾ���
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
     * ����һ��nά�����ԽǾ���
     * @tparam T
     * @param n
     */
    template<typename T>
    three_diagonal_matrix<T>::three_diagonal_matrix(int n) : element(new T[3 * n - 2]), _n(n)
    { }

    /**
     * �õ�i��jλԪ��
     * @tparam T
     * @param i
     * @param j
     * @return i��jλԪ�ص�����
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
     * ��i��jλ��ֵΪval
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
     * ��������
     * @tparam T
     */
    template<typename T>
    three_diagonal_matrix<T>::~three_diagonal_matrix() {
        delete []element;
    }

    /**
     * �����ԽǾ���д�뵽�����os��
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

