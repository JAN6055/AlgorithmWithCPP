//
// Created by JAN on 2022/4/17.
//

#ifndef ALGORITHMWITHCPP_LINKEDLIST_H
#define ALGORITHMWITHCPP_LINKEDLIST_H
#include <cstring>
#include "p3.h"
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
     * 单向链表
     * @tparam T
     */
    template <typename T>
    class LinkedList
    {
        friend class ChainIterator<T>;
    private:
        using Node = _Node<T>;
        Node * _head;
        Node * _bef_end;
        Node * _end;
        int _size;
    public:
        using iterator = ChainIterator<T>;
        explicit LinkedList(const int n = 0)
        : _head(new Node()), _bef_end(_head), _end(new Node()), _size(n)
        {
            _head->_next = _bef_end->_next = _end;
            for(int i=0;i<n;++i)
            {
                push_back(T());
            }
        }

        ~LinkedList()
        {
            while(_head != _end)
            {
                Node * next = _head->_next;
                delete _head;
                _head = next;
            }
            delete _end;
        }

        /**
         * 尾插入一个值尾val的节点
         * @param val
         */
        void push_back(const T & val)
        {
            Node * node = new Node (val,_end);
            _bef_end->_next = node;
            _bef_end = node;
        }

        /**
         * 在迭代器iter后插入一个值为val的节点
         * @param iter
         * @param val
         * @return
         */
        bool insert(iterator iter, const T & val)
        {
            if(iter == end())
                return false;
            Node * node = new Node(val,iter->_next);
            iter->_next = node;
            return true;
        }
        /**
         * 在第一个值为_find的节点后面插入一个值为val的节点
         * @param _find
         * @param val
         * @return 成功插入返回true, 否则返回false
         */
        bool insert(const T & _find, const T & val)
        {
            return insert(find(_find),val);
        }
        /**
         * 获得一个头迭代器
         * @return 一个头迭代器
         */
        iterator begin() const
        {
            return iterator (_head->_next);
        }

        /**
         * 获得一个超尾迭代器
         * @return 一个超尾迭代器
         */
        iterator end() const
        {
            return iterator (_end);
        }

        /**
         * 搜索第一个值为val的节点
         * @param val
         * @return 如果找到，返回指向对应节点的迭代器，否则返回一个超尾迭代器
         */
        iterator find(const T & val)
        {
            auto _first = begin();
            auto _last = end();
            while(_first != _last)
            {
                if(*_first == val)
                    return _first;
                ++_first;
            }
            return _last;
        }
        void reserve();
    };

    /**
     * 对LinkedList的反转
     * @tparam T
     * @return nothing
     */
    template <typename T>
    void LinkedList<T>::reserve()
    {
        Node * p; //前驱节点
        Node * q; //回指节点
        Node * _keep; //记录节点
        //从真正存储数据的节点开始
        p = _head->_next;
        q = p->_next;
        while(q != _end)
        {

            _keep = q->_next; //指针记录
            q->_next = p; //节点回指

            p = q;  //p移动到下一个节点
            q = _keep; //移动到下一个节点
        }
        Node * head_next = _head->_next;
        _head->_next = p;
        head_next->_next = _end;
        _bef_end = head_next;
    }

}   //namespace qimg end

#endif //ALGORITHMWITHCPP_LINKEDLIST_H
