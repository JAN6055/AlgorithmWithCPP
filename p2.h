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
       * ���μ��㣬��arr�е�Ԫ�ص�����ӳ�䵽r��
       * ע������Ϊ��a[i]ǰ����a[i]�͹�С��a[i]��Ԫ��֮��
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
          //i ��0��ʼ����Ƚϣ�����ûʲô����
          for(int i=1;i<n;++i)
              for(int j=0;j<i;++j)
              {
                  //�ж�a[i],ǰ��Ԫ����Ԫ�صļ���,��Ϊj<i
                  if(arr[j] <= arr[i]) r[i]++;
                  //����a[j],�󲿷ֵļ���,��Ϊj<i
                  else r[j]++;
              }
      }

      /**
       * ��������ļ�������
       * @tparam T
       * @param arr ����������
       * @param n ���鳤��
       * @param r �Ѿ��źõ�����
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
       * Ѱ�����������Ԫ��
       * @tparam T
       * @param arr
       * @param n
       * @return ���������Ԫ������
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
       * ѡ������ÿ��ѡ��һ������Ԫ�������Ԫ�ص�ǰһ��Ԫ�ؽ���
       * @tparam T
       * @param arr
       * @param n
       * @return nothing
       */
      template <typename T>
      void selection_sort(T arr[], const int n)
      {
          // >1 ����
          for(int i=n;i>1;--i)
          {
              int j = index_of_max(arr,i);
              std::swap(arr[i-1],arr[j]);
          }
      }

      /**
       * һ��ð�ݹ���
       * @tparam T
       * @param arr ����һ��ð�ݵ�����
       * @param n ���鳤��
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
       * ð������
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
       * ��һ�������������һ��Ԫ��,�����䳤������
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
       * ��һ�������������һ��Ԫ��, �����䳤������
       * @tparam T
       * @param arr
       * @param n ������ĳ���
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
       * ԭ�����ŵļ������򣬲��ÿ��ٶ���Ŀռ�
       * @tparam T
       * @param arr
       * @param n
       * @param r �Ѿ��źõ�����
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
       * ��ʱ��ֹ��ѡ����������������Ѿ�������ô�Ͳ��ٽ�������
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
              for(int j=1;j<size; ++j) //�ҵ����Ԫ������
              {
                  if(arr[flag] <= arr[j])
                      flag = j;
                  else      //���û�н���else,��ô�������Ѿ��ź���
                      sorted = false;
              }
              std::swap(arr[flag],arr[size-1]);
          }
      }

      /**
       * bubble�ĸ����棬���ڼ�ʱ��ֹ��ð������
       * @tparam T
       * @param arr
       * @param n
       * @return ���û�н���Ԫ�صĽ������򷵻�false�����򷵻�true
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
       * ��ʱ��ֹ��ð���������������Ĺ����������Ѿ������򷵻�
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
       * ��������汾һ
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
       * ��������汾��
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
   * �����ת��,������ת�ã���ԭ���㷨
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
     * �������a1[rows][n] aw[n][cols], ans[rows][cols]
     * �˰汾����ָ��Ϊ����
     * a1 * a2���������ans��
     * @tparam T
     * @param arr1
     * @param arr2
     * @param ans
     * @param rows �û��ṩ
     * @param n �û��ṩ
     * @param cols  �û��ṩ
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
     * ������ˣ�a1[rows][n] aw[n][cols], ans[rows][cols]
     * �˰汾����������Ϊ����
     * a1 * a2���������ans��
     * @tparam T
     * @tparam ROWS �������ƶ�
     * @tparam N �������ƶ�
     * @tparam COLS �������ƶ�
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
     * ����ӷ�
     * @tparam T
     * @tparam ROWS
     * @tparam COLS
     * @param arr1
     * @param arr2
     * @return ָ������һ������ָ��
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
     * ����ӷ���������õľ���������ans[][]��
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
