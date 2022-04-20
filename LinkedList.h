//
// Created by JAN on 2022/4/17.
//

#ifndef ALGORITHMWITHCPP_LINKEDLIST_H
#define ALGORITHMWITHCPP_LINKEDLIST_H
#include <cstring>
#include <ostream>
#include "arraylist.h"
namespace qimg{
    template <typename T> class _Node;

    template <typename T> class LinkedList;

    template <typename T> class ChainIterator;

    /**
     * LinkedList的配套节点
     * @tparam T
     */
    template <typename T>
    class _Node
    {
        friend  class LinkedList<T>;
        friend class ChainIterator<T>;
    private:
        using Node = _Node<T>;

        T _element;
        Node * _next;
    public:
        _Node() = default;
        explicit _Node(Node * next) : _next(next)
        { }
        _Node(const T & ele, Node * next) : _element(ele), _next(next)
        { }
    };

    /**
     * 适配LinkedList的单向迭代器，
     * 目前不能适配STL算法，但是可以用于正常的迭代器迭代
     * 提供了++, ++(int), *, ->, ==, ！=的操作
     * @tparam T
     */
    template <typename T>
    class ChainIterator
    {
        friend class LinkedList<T>;
    private:
        using Node = _Node<T>;
        using Iter = ChainIterator<T>;
        Node * _node;
    public:
        explicit ChainIterator(Node * node) : _node(node)
        { }

        bool operator==(const Iter & iter) const
        {
            return _node == iter._node;
        }

        bool operator!=(const Iter & iter) const
        {
            return _node != iter._node;
        }

        Iter & operator++()
        {
            _node = _node->_next;
            return *this;
        }

        const Iter operator++(int)
        {
            Iter ret(*this);
            _node = _node->_next;
            return ret;
        }

        T & operator*() const
        {
            return _node->_element;
        }
    private:
        Node * const operator->() const
        {
            return _node;
        }
    };

    /**
     * 将链表写到流os中
     * @tparam T
     * @param os
     * @param list
     * @return os(&)
     */
    template<typename T>
    std::ostream &operator<<(std::ostream &os, const LinkedList<T> &ls);

    template <typename T>
    class LinkedList
    {
    private:
        using Node = _Node<T>;
        int _size;
        Node * _head;
    public:
        using iterator = ChainIterator<T>;
        friend std::ostream &operator<< <T>(std::ostream &os, const LinkedList &list);
        LinkedList();
        LinkedList(const std::initializer_list<T> & init_ls);
        void push_front(const T & val);
        void pop_front();
        int size() const;
        void output(std::ostream & os) const;
        void reserve();
        bool empty() const { return _size == 0; }
        iterator begin() const { return iterator (_head->_next); }
        iterator end() const { return iterator (nullptr); }
        ~LinkedList();
    };

    template <typename T>
    LinkedList<T>::LinkedList() : _size(0), _head(new Node(T{}, nullptr))
    { }

    template <typename T>
    void LinkedList<T>::push_front(const T &val)
    {
        _head->_next = new Node(val,_head->_next);
        ++_size;
    }

    /**
     * 删除链表头元素
     * @tparam T
     */
    template <typename T>
    void LinkedList<T>::pop_front()
    {
        Node * need = _head->_next;
        _head->_next = need->_next;
        need->_next = nullptr;
        --_size;
        delete need;
    }

    /**
     * 使用初值列表初始化LinkedList
     * @tparam T
     * @param init_ls
     */
    template<typename T>
    LinkedList<T>::LinkedList(const std::initializer_list<T> &init_ls)
        : LinkedList()
    {
        for(auto it = rbegin(init_ls);it != rend(init_ls);++it)
        {
            push_front(*it);
        }
    }
    /**
     * 析构函数
     * @tparam T
     */
    template <typename T>
    LinkedList<T>::~LinkedList<T>() {
        while(_head != nullptr)
        {
            Node * next = _head->_next;
            delete _head;
            _head = next;
        }
    }

    /**
     * 返回链表大小
     * @tparam T
     * @return
     */
    template<typename T>
    inline int LinkedList<T>::size() const {
        return _size;
    }

    /**
     * 将链表写到流os中
     * @tparam T
     * @param os
     * @return nothing
     */
    template <typename T>
    void LinkedList<T>::output(std::ostream &os) const {
        _Node<T> * node = _head->_next;
        while(node != nullptr)
        {
            os << node->_element << " ";
            node = node->_next;
        }
    }

    /**
     * 将链表写到流os中
     * @tparam T
     * @param os
     * @param ls
     * @return os(&)
     */
    template<typename T>
    std::ostream & operator<<(std::ostream & os, const LinkedList<T> & ls)
    {
        ls.output(os);
        return os;
    }

    /**
     * 将LinkedList反转
     * @tparam T
     * @return nothing
     */
    template <typename T>
    void LinkedList<T>::reserve() {
        Node *bef, *need, *keep;
        bef = _head->_next;
        need = bef->_next;
        bef->_next = nullptr;
        keep = need;
        while(true)
        {
            if(keep == nullptr)
                break;
            else
                keep = keep->_next;
            need->_next = bef;
            bef = need;
            need = keep;
        }
        _head ->_next =  bef;
    }
}   //namespace qimg end

#endif //ALGORITHMWITHCPP_LINKEDLIST_H
