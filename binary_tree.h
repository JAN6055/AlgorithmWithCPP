//
// Created by JAN on 2022/4/22.
//

#ifndef ALGORITHMWITHCPP_BINARY_TREE_H
#define ALGORITHMWITHCPP_BINARY_TREE_H

#include <iostream>
#include <deque>
namespace qimg{

    /**
     * �������еĽڵ�
     * @tparam T
     */
    template<typename T>
    class binaryTreeNode
    {
    public:
        T element;
        binaryTreeNode<T> * _left, * _right;

        binaryTreeNode(const T & element, binaryTreeNode<T> *left, binaryTreeNode<T> *right)
        : element(element), _left(left), _right(right)
        { }

        binaryTreeNode() : binaryTreeNode(T{}, nullptr, nullptr)
        { }

        explicit binaryTreeNode(const T & element) : binaryTreeNode(element, nullptr, nullptr)
        { }

        virtual ~binaryTreeNode() = default;
    };


    /**
     * �������ڵ��һ����ӡ��
     * @tparam T
     * @param x
     */
    template<typename T>
    void visit(binaryTreeNode<T> * x)
    {
        std::cout << x->element <<" ";
    }

    /**
     * �������ĳ������
     * @tparam T
     */
    template<typename T>
    class binary_tree{
    public:
        virtual ~binary_tree() = default;
        virtual bool empty() const = 0;
        virtual int  size() const = 0;
        virtual void preOrder(void (*)(T *)) = 0;   //ǰ��
        virtual void inOrder(void (*)(T *)) = 0;    //����
        virtual void postOrder(void (*)(T *)) = 0;  //����
        virtual void levelOrder(void (*)(T *)) = 0; //���
    };

    /**
     * ������֯�Ķ����������м̳д������binary_tree<T>
     * @tparam T
     */
    template <typename E>
    class linked_binary_tree : public binary_tree<binaryTreeNode<E>>
    {
    private:
        using Node = binaryTreeNode<E>;
    public:
        linked_binary_tree() : root(nullptr), _size(0)
        { }
        bool empty() const override { return  _size == 0; }
        int  size()  const override { return _size; }

        void preOrder(void (*visit)(Node * )) override {    //ǰ��
            linked_binary_tree<E>::visit = visit;
            preOrder(root);
        }

        void inOrder(void (*visit)(Node *)) override        //����
        {
            linked_binary_tree<E>::visit = visit;
            inOrder(root);
        }

        void postOrder(void (*visit)(Node *)) override      //����
        {
            linked_binary_tree<E>::visit = visit;
            postOrder(root);
        }

        ~linked_binary_tree() override{
            erase();
        }

        void add(const E & val);
        int  height() const;
        void levelOrder(void (*visit)(Node *)) override;    //���

        void erase()         //�����
        {
            postOrder(dispose);
            root = nullptr;
            _size = 0;
        }
        static void (*visit)(Node *);     //��ӡ��ָ��
    private:
        Node * root;                      //���ڵ�
        int _size;                        //���ڵ��еĸ���
        static void preOrder(Node * t);   //ǰ��
        static void inOrder(Node * t);    //����
        static void postOrder(Node * t);  //����
        static void levelOrder(Node * t); //���
        static void add(const E & val, Node * node);
        static void dispose(Node * t) { delete t; } //ɾ����
        static int  height(Node * t);
    };

    /**
     * ��̬��Ա��ǰ�����
     * @tparam T
     * @param t
     */
    template<typename T>
    void linked_binary_tree<T>::preOrder(Node *t) {
        if(t == nullptr)
            return;
        linked_binary_tree<T>::visit(t);
        preOrder(t->_left);
        preOrder(t->_right);
    }

    /**
     * ��̬��Ա���������
     * @tparam T
     * @param t
     */
    template<typename T>
    void linked_binary_tree<T>::inOrder(Node * t) {
        if(t == nullptr)
            return;
        inOrder(t->_left);
        linked_binary_tree<T>::visit(t);
        inOrder(t->_right);
    }


    /**
     * ��̬��Ա���������
     * @tparam T
     * @param t
     */
    template<typename T>
    void linked_binary_tree<T>::postOrder(Node *t)
    {
        if(t == nullptr)
            return;
        postOrder(t->_left);
        postOrder(t->_right);
        linked_binary_tree<T>::visit(t);
    }

    /**
     * ��̬��Ա����α���
     * @tparam T
     * @param t
     */
    template<typename T>
    void linked_binary_tree<T>::levelOrder(Node *t) {
        std::deque<Node *> node_deque;
        while(t != nullptr)
        {
            visit(t);
            if(t->_left != nullptr)
                node_deque.push_back(t->_left);
            if(t->_right != nullptr)
                node_deque.push_back(t->_right);
            if(node_deque.empty()) return;
            t = node_deque.front();
            node_deque.pop_front();
        }
    }

    /**
     * ��Ա��������α��������þ�̬�汾ʵ��
     * @tparam T
     * @param visit
     */
    template<typename T>
    void linked_binary_tree<T>::levelOrder(void (*visit)(Node *)) {
        linked_binary_tree<T>::visit = visit;
        linked_binary_tree<T>::levelOrder(root);
    }

    /**
     * ��һ������������ӽڵ�---δ��ɵİ汾
     * @tparam T
     * @param val
     */
    template<typename T>
    void linked_binary_tree<T>::add(const T &val) {
        if(root == nullptr){
            root = new Node(val);
            return;
        }
        add(val,root);
    }

    /**
     * ��̬��Ա����������ĸ߶�
     * @tparam T
     * @param t
     * @return �������ĸ߶�(int)
     */
    template<typename T>
    int linked_binary_tree<T>::height(binaryTreeNode<T> * t)
    {
        if(t == nullptr)
            return 0;
        int hl = height(t->_left);
        int hr = height(t->_right);
        if(hl > hr)
            return ++hl;
        else
            return ++hr;
    }

    /**
     * ��Ա������ȷ���������߶ȣ�����static �汾��height���
     * @tparam T
     * @return
     */
    template<typename T>
    int linked_binary_tree<T>::height() const {
        return height(root);
    }

    /**
     * ��̬��Ա��������������һ���ڵ�---δ��ɵİ汾
     * @tparam T
     * @param val
     * @param node �ݹ���ʼΪroot
     */
    template<typename T>
    void linked_binary_tree<T>::add(const T &val, Node *node) {
        if(node->_left == nullptr)
            node->_left = new Node(val);
        else if(node->_right == nullptr)
            node->_right = new Node (val);
        else
            add(val, node->_left);
    }

    /**
     * ��ʼ����̬���ݳ�Ա visit
     * @tparam T
     */
    template<typename T>
    void(* linked_binary_tree<T>::visit)(binaryTreeNode<T> *) = nullptr;

}

#endif //ALGORITHMWITHCPP_BINARY_TREE_H
