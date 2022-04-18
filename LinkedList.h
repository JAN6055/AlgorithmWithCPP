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
     * LinkedList�����׽ڵ�
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
     * ����LinkedList�ĵ����������
     * Ŀǰ��������STL�㷨�����ǿ������������ĵ���������
     * �ṩ��++, ++(int), *, ->, ==, ��=�Ĳ���
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
     * ��������
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
         * β����һ��ֵβval�Ľڵ�
         * @param val
         */
        void push_back(const T & val)
        {
            Node * node = new Node (val,_end);
            _bef_end->_next = node;
            _bef_end = node;
        }

        /**
         * �ڵ�����iter�����һ��ֵΪval�Ľڵ�
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
         * �ڵ�һ��ֵΪ_find�Ľڵ�������һ��ֵΪval�Ľڵ�
         * @param _find
         * @param val
         * @return �ɹ����뷵��true, ���򷵻�false
         */
        bool insert(const T & _find, const T & val)
        {
            return insert(find(_find),val);
        }
        /**
         * ���һ��ͷ������
         * @return һ��ͷ������
         */
        iterator begin() const
        {
            return iterator (_head->_next);
        }

        /**
         * ���һ����β������
         * @return һ����β������
         */
        iterator end() const
        {
            return iterator (_end);
        }

        /**
         * ������һ��ֵΪval�Ľڵ�
         * @param val
         * @return ����ҵ�������ָ���Ӧ�ڵ�ĵ����������򷵻�һ����β������
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
     * ��LinkedList�ķ�ת
     * @tparam T
     * @return nothing
     */
    template <typename T>
    void LinkedList<T>::reserve()
    {
        Node * p; //ǰ���ڵ�
        Node * q; //��ָ�ڵ�
        Node * _keep; //��¼�ڵ�
        //�������洢���ݵĽڵ㿪ʼ
        p = _head->_next;
        q = p->_next;
        while(q != _end)
        {

            _keep = q->_next; //ָ���¼
            q->_next = p; //�ڵ��ָ

            p = q;  //p�ƶ�����һ���ڵ�
            q = _keep; //�ƶ�����һ���ڵ�
        }
        Node * head_next = _head->_next;
        _head->_next = p;
        head_next->_next = _end;
        _bef_end = head_next;
    }

}   //namespace qimg end

#endif //ALGORITHMWITHCPP_LINKEDLIST_H
