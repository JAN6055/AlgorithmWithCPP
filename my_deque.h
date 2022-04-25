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
     * 用于构建双向链表的节点
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
     * 简单的适配双向链表的迭代器
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
     * 双向链表，支持迭代器迭代
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
     * 链表是否为空
     * @tparam T
     * @return 如果为空返回true，否则返回false
     */
    template <typename T>
    bool list<T>::empty() const{
        return _size == 0;
    }

    /**
     * 获得链表的节点个数
     * @tparam T
     * @return
     */
    template <typename T>
    int list<T>::size() const{
        return _size;
    }

    /**
     * 向链表头添加值为val的节点
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
     * 删除链表的第一个节点，如果链表为空，则什么也不做
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
     * 向链表尾中添加一个值为val的节点
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
     * 删除链表尾的元素，如果链表为空，则什么也不做
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
     * 获得链表头的元素
     * @tparam T
     * @return
     */
    template <typename T>
    T &list<T>::front() const {
        return _head->next->element;
    }

    /**
     * 获得链表尾的元素
     * @tparam T
     * @return 链表尾元素的引用
     */
    template <typename T>
    T &list<T>::back() const {
        return _end->pre->element;
    }
}

#endif // MY_DEQUE_H
