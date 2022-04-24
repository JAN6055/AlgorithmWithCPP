//
// Created by JAN on 2022/4/22.
//

#ifndef ALGORITHMWITHCPP_BINARY_TREE_H
#define ALGORITHMWITHCPP_BINARY_TREE_H

#include <iostream>
#include <deque>
namespace qimg{

    /**
     * 二叉树中的节点
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
     * 二叉树节点的一个打印器
     * @tparam T
     * @param x
     */
    template<typename T>
    void normal_visit(binaryTreeNode<T> * x)
    {
        std::cout << x->element <<" ";
    }

    /**
     * 二叉树的抽象基类
     * @tparam T
     */
    template<typename T>
    class binary_tree{
    public:
        virtual ~binary_tree() = default;
        virtual bool empty() const = 0;
        virtual int  size() const = 0;
        virtual void preOrder(void (*)(T *)) = 0;   //前序
        virtual void inOrder(void (*)(T *)) = 0;    //中序
        virtual void postOrder(void (*)(T *)) = 0;  //后序
        virtual void levelOrder(void (*)(T *)) = 0; //层次
    };

    /**
     * 链表组织的二叉树，公有继承纯虚基类binary_tree<T>
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
        linked_binary_tree(const std::initializer_list<E> & ls);
        bool empty() const override { return  _size == 0; }
        int  size()  const override { return _size; }

        void preOrder(void (*visit)(Node * )) override {    //前序
            linked_binary_tree<E>::visit = visit;
            preOrder(root);
        }

        void inOrder(void (*visit)(Node *)) override        //中序
        {
            linked_binary_tree<E>::visit = visit;
            inOrder(root);
        }

        void postOrder(void (*visit)(Node *)) override      //后序
        {
            linked_binary_tree<E>::visit = visit;
            postOrder(root);
        }

        ~linked_binary_tree() override{
            erase();
        }

        void add(const E & val);
        int  height() const;
        void levelOrder(void (*visit)(Node *)) override;    //层次

        void erase()         //清除树
        {
            postOrder(dispose);
            root = nullptr;
            _size = 0;
        }

        void swap(linked_binary_tree<E> & tree) noexcept;
        void reserve() const;
    private:
        Node * root;                      //根节点
        int _size;                        //数节点中的个数
        static void (*visit)(Node *);     //打印器指针
        static void preOrder(Node * t);   //前序
        static void inOrder(Node * t);    //中序
        static void postOrder(Node * t);  //后序
        static void levelOrder(Node * t); //层次
        static void dispose(Node * t) { delete t; } //删除器
        static int  height(Node * t);
        static void reserve(Node * t);
    };

    /**
     * 静态成员，前序遍历
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
     * 静态成员，中序遍历
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
     * 静态成员，后序遍历
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
     * 静态成员，层次遍历
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
     * 成员函数，层次遍历，调用静态版本实现
     * @tparam T
     * @param visit
     */
    template<typename T>
    void linked_binary_tree<T>::levelOrder(void (*visit)(Node *)) {
        linked_binary_tree<T>::visit = visit;
        linked_binary_tree<T>::levelOrder(root);
    }

    /**
     * 向一个二叉树中添加节点
     * 用此方法构造的二叉树为完全二叉树，用于测试，不建议使用
     * @tparam T
     * @param val
     */
    template<typename T>
    void linked_binary_tree<T>::add(const T &val) {
        if(root == nullptr){
            root = new Node(val);
            ++_size;
            return;
        }
        std::deque<Node*> node_deque{ root };
        while (true)
        {
            Node * node = node_deque.front();
            if(node->_left == nullptr)
            {
                node->_left = new Node (val);
                ++_size;
                return;
            }
            if(node->_right == nullptr)
            {
                node->_right = new Node (val);
                ++_size;
                return;
            }
            if(node->_left != nullptr)
                node_deque.push_back(node->_left);
            if(node->_right != nullptr)
                node_deque.push_back(node->_right);
            node_deque.pop_front();
        }
    }

    /**
     * 静态成员，求二叉树的高度
     * @tparam T
     * @param t
     * @return 二叉树的高度(int)
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
     * 成员函数，确定二叉树高度，调用static 版本的height完成
     * @tparam T
     * @return
     */
    template<typename T>
    int linked_binary_tree<T>::height() const {
        return height(root);
    }

    /**
     * 初始化静态数据成员 visit
     * @tparam T
     */
    template<typename T>
    void(* linked_binary_tree<T>::visit)(binaryTreeNode<T> *) = qimg::normal_visit;

    /**
     * 交换两个二叉树
     * @tparam T
     * @param tree
     */
    template<typename T>
    void linked_binary_tree<T>::swap(linked_binary_tree<T> & tree) noexcept
    {
        std::swap(root, tree.root);
    }

    /**
     * 列表初始一个层次遍历为迭代列表结果的完全二叉树
     * @tparam T
     * @param ls
     */
    template<typename T>
    linked_binary_tree<T>::
            linked_binary_tree(const std::initializer_list<T> &ls)
    : linked_binary_tree()
    {
        for (const auto &item: ls) {
            add(item);
        }
    }

    /**
     * 静态方法，交换t树每个节点的左右子树 --- bug所有的叶子节点不会的到交换
     * @tparam T
     * @param t
     */
    template<typename T>
    void linked_binary_tree<T>::reserve(Node *t) {
        if(t == nullptr) return;
        if(t->_left != nullptr)
            reserve(t->_left);
        if(t->_right != nullptr)
            reserve(t->_left);
        using namespace std;
        if(t->_left != nullptr || t->_right != nullptr)
            std::swap(t->_right,t->_left);

    }

    /**
     * 成员函数，交换每个节点的左右子树
     * @tparam T
     */
    template<typename T>
    void linked_binary_tree<T>::reserve() const {
        if(root == nullptr) return;
        linked_binary_tree<T>::reserve(root);
    }
}   //namespace qimg end

#endif //ALGORITHMWITHCPP_BINARY_TREE_H
