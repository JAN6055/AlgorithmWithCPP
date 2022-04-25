//
// Created by JAN on 2022/4/25.
#ifndef  MY_DEQUE_H
#define  MY_DEQUE_H
#include <iostream>
namespace qimg{
    template <typename T> class ls_node;
    template <typename T> class list;
    template <typename T> class list_iterator;
    template <typename T>
    /**
     * ���ڹ���˫������Ľڵ�
     * @tparam T
     */
    class ls_node
    {
    public:
        using Node = ls_node<T>;
        T element;
        Node * next;
        Node * pre;
        explicit ls_node(const T & val = T{}, Node * _next = nullptr, Node * _pre = nullptr)
                : element(val), next(_next), pre(_pre)
        { }
    };

    /**
     * �򵥵�����˫������ĵ�����
     * @tparam T
     */
    template <typename T>
    class list_iterator
    {
        friend class list<T>;
    private:
        using Node = ls_node<T>;
        using iter = list_iterator<T>;
        Node * node;
    public:
        explicit list_iterator(Node * _node) : node(_node)
        { }
        iter & operator++(){
            node = node->next;
            return *this;
        }
        const iter operator++(int)
        {
            iter ret (*this);
            node = node->next;
            return ret;
        }
        T & operator*() const{
            return node->element;
        }
        bool operator==(const iter & rhs)
        {
            return node == rhs.node;
        }
        bool operator!=(const iter & rhs)
        {
            return node != rhs.node;
        }
        iter & operator--()
        {
            node = node->pre;
            return *this;
        }
        const iter operator--(int)
        {
            iter ret (*this);
            node = node->pre;
            return ret;
        }
    };

    /**
     * ˫������֧�ֵ���������
     * @tparam T
     */
    template<typename T>
    class list
    {
    private:
        using Node = ls_node<T>;
        Node * _head;
        Node * _end;
        int _size;
    public:
        using iterator = list_iterator<T>;
        iterator begin() const{
            return iterator (_head->next);
        }

        iterator end() const{
            return iterator (_end);
        }
        bool empty() const;
        int  size() const;
        void push_front(const T & val);
        void push_back(const T & val);
        void pop_front();
        void pop_back();
        T & front() const;
        T & back() const;
        list() : _head(new Node()), _end(new Node()), _size(0)
        {
            _head->next = _end;
            _end->pre = _head;
        }
        list(const std::initializer_list<T> & ls) : list()
        {
            for (const auto &item: ls) {
                push_back(item);
            }
        }
    };

    /**
     * �����Ƿ�Ϊ��
     * @tparam T
     * @return ���Ϊ�շ���true�����򷵻�false
     */
    template <typename T>
    bool list<T>::empty() const{
        return _size == 0;
    }

    /**
     * �������Ľڵ����
     * @tparam T
     * @return
     */
    template <typename T>
    int list<T>::size() const{
        return _size;
    }

    /**
     * ������ͷ���ֵΪval�Ľڵ�
     * @tparam T
     * @param val
     */
    template <typename T>
    void list<T>::push_front(const T & val){
        Node * node = new Node(val,_head->next, _head);
        _head->next = node;
        node->next->pre = node;
        --_size;
    }

    /**
     * ɾ������ĵ�һ���ڵ㣬�������Ϊ�գ���ʲôҲ����
     * @tparam T
     */
    template <typename T>
    void list<T>::pop_front(){
        if(_size == 0)
            return;
        Node * del = _head->next;
        _head->next = del->next;
        del->next->pre = _head;
        del->next = nullptr;
        del->pre = nullptr;
        --_size;
    }

    /**
     * ������β�����һ��ֵΪval�Ľڵ�
     * @tparam T
     * @param val
     */
    template <typename T>
    void list<T>::push_back(const T &val) {
        Node * node = new Node(val,_end,_end->pre);
        node->pre->next = node;
        _end->pre = node;
        ++_size;
    }


    /**
     * ɾ������β��Ԫ�أ��������Ϊ�գ���ʲôҲ����
     * @tparam T
     */
    template <typename T>
    void list<T>::pop_back(){
        if(_size == 0)
            return;
        Node * del = _end->pre;
        _end->pre = del->pre;
        del->pre->next = _end;
        del->next = nullptr;
        del->pre = nullptr;
        --_size;
    }

    /**
     * �������ͷ��Ԫ��
     * @tparam T
     * @return
     */
    template <typename T>
    T &list<T>::front() const {
        return _head->next->element;
    }

    /**
     * �������β��Ԫ��
     * @tparam T
     * @return ����βԪ�ص�����
     */
    template <typename T>
    T &list<T>::back() const {
        return _end->pre->element;
    }
}

#endif // MY_DEQUE_H
