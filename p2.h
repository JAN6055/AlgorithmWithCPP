//
// Created by JAN on 2022/4/16.
//

#ifndef ALGORITHMWITHCPP_P2_H
#define ALGORITHMWITHCPP_P2_H
namespace qimg
{
  namespace s_sort
  {
      /**
       * 名次计算，将arr中的元素的名次映射到r中
       * 注：名次为在a[i]前等于a[i]和共小于a[i]的元素之和
       * @tparam T
       * @param arr
       * @param n
       * @param r
       * @return nothing
       */
      template <typename T>
      void rank(T arr[], const int n, int r[])
      {
          for(int i=0;i<n;++i)
              r[i] = 0;
          //i 从0开始不会比较，所以没什么意义
          for(int i=1;i<n;++i)
              for(int j=0;j<i;++j)
              {
                  //判断a[i],前面元部分元素的计数,因为j<i
                  if(arr[j] <= arr[i]) r[i]++;
                  //对于a[j],后部分的计数,因为j<i
                  else r[j]++;
              }
      }

      /**
       * 附加数组的计数排序
       * @tparam T
       * @param arr 待排序数组
       * @param n 数组长度
       * @param r 已经排好的名词
       * @return nothing
       */
      template <typename T>
      void rearrange(T arr[], const int n, const int r[])
      {
          T * temp = new T[n];
          for(int i=0;i<n;++i)
              temp[r[i]] = arr[i];
          for(int i=0;i<n;++i)
              arr[i] = temp[i];
          delete []temp;
      }

      /**
       * 寻找数组中最大元素
       * @tparam T
       * @param arr
       * @param n
       * @return 数组中最大元素索引
       */
      template <typename T>
      int index_of_max(T arr[], const int n)
      {
          int ret = 0;
          T & _max = arr[0];
          for(int i = 1;i<n;++i)
          {
              if(arr[i] >= _max)
              {
                  _max = arr[i];
                  ret = i;
              }
          }
          return ret;
      }

      /**
       * 选择排序，每次选择一个最大的元素与最大元素的前一个元素交换
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      void selection_sort(T arr[], const int n)
      {
          // >1 即可
          for(int i=n;i>1;--i)
          {
              int j = index_of_max(arr,i);
              std::swap(arr[i-1],arr[j]);
          }
      }

      /**
       * 一次冒泡过程
       * @tparam T
       * @param arr 进行一次冒泡的数组
       * @param n 数组长度
       * @return nothing
       */
      template <typename T>
      void bubble(T arr[], const int n)
      {
          for(int i=0;i<n-1;++i)
              if(arr[i] > arr[i+1])
                  std::swap(arr[i],arr[i+1]);
      }

      /**
       * 冒泡排序
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template<typename T>
      void bubble_sort(T arr[], const int n)
      {
          for(int i=n;i>1;--i)
              bubble(arr,i);
      }
      /**
       * 对一个有序数组插入一个元素,不对其长度自增
       * @tparam T
       * @param arr
       * @param n
       * @param val
       */
      template <typename T>
      void insert(T arr[],const int n, const T val)
      {
          int i;
          for(i=n-1;i>=0 && val < arr[i];--i)
              arr[i+1] = arr[i];
          arr[i+1] = val;
      }

      /**
       * 对一个有序数组插入一个元素, 并对其长度自增
       * @tparam T
       * @param arr
       * @param n 此数组的长度
       * @param val
       * @return nothing
       */
      template <typename T>
      void insert_ref(T arr[], int & n, const T & val)
      {
          qimg::s_sort::insert(arr,n,val);
          ++n;
      }

      /**
       * 原地重排的计数排序，不用开辟额外的空间
       * @tparam T
       * @param arr
       * @param n
       * @param r 已经排好的名词
       * @return nothing
       */
      template <typename T>
      void rearrange_inplace(T arr[], const int n, int r[])
      {
          for(int i=0;i<n;++i)
          {
              while(i != r[i])
              {
                  int t = r[i];
                  std::swap(arr[i],arr[t]);
                  std::swap(r[i],r[t]);
              }
          }
      }

      /**
       * 即时终止的选择排序，如果此数组已经有序，那么就不再进行排序
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      void selection_sort_pro(T arr[], const int n)
      {
          bool sorted = false;
          for(int size = n; !sorted && size > 1; --size)
          {
              sorted = true;
              int flag = 0;
              for(int j=1;j<size; ++j) //找到最大元素索引
              {
                  if(arr[flag] <= arr[j])
                      flag = j;
                  else      //如果没有进入else,那么此数组已经排好序
                      sorted = false;
              }
              std::swap(arr[flag],arr[size-1]);
          }
      }

      /**
       * bubble的改良版，用于即时终止的冒泡排序
       * @tparam T
       * @param arr
       * @param n
       * @return 如果没有进行元素的交换，则返回false，否则返回true
       */
      template <typename T>
      bool bubble_pro(T arr[], const int n)
      {
          bool bubbled = false;
          for(int i=0;i<n-1;++i)
          {
              if(arr[i] > arr[i+1])
              {
                  std::swap(arr[i],arr[i+1]);
                  bubbled = true;
              }
          }
          return bubbled;
      }

      /**
       * 及时终止的冒泡排序，如果在排序的过程中序列已经有序，则返回
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      void bubble_sort_pro(T arr[], const int n)
      {
          for(int size=n;size>1;--size)
          {
              if(!bubble_pro(arr,size))
                  return;
          }
      }

      /**
       * 插入排序版本一
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      inline void insert_sort1(T arr[], const int n)
      {
          for(int i=1;i<n;++i)
          {
              insert(arr,i,arr[i]);
          }
      }

      /**
       * 插入排序版本二
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      inline void insert_sort2(T arr[], const int n)
      {
          for(int i=1;i<n;++i)
          {
              int j = i;
              const T  key = arr[i];
              while(j > 0 && key < arr[j-1])
              {
                  arr[j] = arr[j-1];
                  --j;
              }
              arr[j] = key;
          }
      }

  } //namespace __sort end


  /**
   * 矩阵的转置,将矩阵转置，非原地算法
   * @tparam T
   * @param arr
   * @param rows
   * @param cols
   * @return nothing
   */
    template<typename T>
    void matrix_transpose(T** & arr, const int rows, const int cols)
    {
        T** temp = arr;
        qimg::make2dArray(arr, cols, rows);
        for(int i=0;i<rows;++i)
        {
            for(int j=0;j<cols;++j)
            {
                //std::cout << temp[i][j] << " ";
                arr[j][i] = temp[i][j];
            }
        }
        delete_arr_2d(temp,rows);
    }

    /**
     * 矩阵相乘a1[rows][n] aw[n][cols], ans[rows][cols]
     * 此版本接受指针为参数
     * a1 * a2将结果放在ans中
     * @tparam T
     * @param arr1
     * @param arr2
     * @param ans
     * @param rows 用户提供
     * @param n 用户提供
     * @param cols  用户提供
     */
    template <typename T>
    void matrix_mul(T** arr1, T** arr2, T** ans,
                    const int rows, const int n, const int cols)
    {
        for(int i=0;i<rows;++i)
        {
            for(int j=0; j < cols; ++j)
            {
                T temp = 0;
                for(int k=0;k<n;++k)
                {
                    temp += arr1[i][k] * arr2[k][j];
                }
                ans[i][j] = temp;
            }
        }
    }

    /**
     * 矩阵相乘，a1[rows][n] aw[n][cols], ans[rows][cols]
     * 此版本接受数组作为参数
     * a1 * a2将结果放在ans中
     * @tparam T
     * @tparam ROWS 编译器推断
     * @tparam N 编译器推断
     * @tparam COLS 编译器推断
     * @param arr1
     * @param arr2
     * @param ans
     */
    template <typename T, size_t ROWS, size_t N, size_t COLS>
    void matrix_mul(T (&arr1)[ROWS][N],T (&arr2)[N][COLS], T (&ans)[ROWS][COLS])
    {
        for(int i=0;i<ROWS;++i)
        {
            for(int j=0; j < COLS; ++j)
            {
                T temp = 0;
                for(int k=0;k<N;++k)
                {
                    temp += arr1[i][k] * arr2[k][j];
                }
                ans[i][j] = temp;
            }
        }
    }

    /**
     * 矩阵加法
     * @tparam T
     * @tparam ROWS
     * @tparam COLS
     * @param arr1
     * @param arr2
     * @return 指向矩阵的一个二级指针
     */
    template <typename T,size_t ROWS, size_t COLS>
    T** matrix_add(T (&arr1)[ROWS][COLS], T (&arr2)[ROWS][COLS])
    {
        T ** ret;
        if(!qimg::make2dArray(ret,ROWS,COLS))
        {
            return nullptr;
        }
        for(int i=0;i<ROWS;++i)
            for(int j=0;j<COLS;++j)
                ret[i][j] = arr1[i][j] + arr2[i][j];
        return ret;
    }

    /**
     * 矩阵加法，将计算好的矩阵结果放在ans[][]中
     * @tparam T
     * @tparam ROWS
     * @tparam COLS
     * @param arr1
     * @param arr2
     * @param ans
     * @return nothing
     */
    template <typename T, size_t ROWS, size_t COLS>
    void matrix_add(T (&arr1)[ROWS][COLS], T (&arr2)[ROWS][COLS],
                    T(&ans)[ROWS][COLS])
    {
        for(int i=0;i<ROWS;++i)
            for(int j=0;j<COLS;++j)
                ans[i][j] = arr1[i][j] + arr2[i][j];
    }

}   //namespace qimg end

#endif //ALGORITHMWITHCPP_P2_H
