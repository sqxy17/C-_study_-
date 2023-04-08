#pragma once
#include<iostream>
using namespace std;

//前言:什么是 key/value模型?                   ----甚至 value 也可以存放自定义类型
// 通过一个值查找另外一个值,也就是这两个值是强关联关系.  例如:中英互译(其实也就是中英字典)    再比如身份证刷身份证进站(一个身份证绑定特有的车票,座位,车的列次...)
//最简单的 key/value 模型就是字典模型

//比较麻烦的车票身份证的这个模型也可以,只是车票可能是是一个结构体,取名为 info,但是这个然后,value 是 vector<info>,车票这个结构体里面可以放很很多的消息



//一丶  具体实现 key/value模型

namespace  key_value
{



//-------二叉树单个结点的定义
    template<class K,class V>//在这个模型里面   这个k代表的意思是key     v 代表的意思是 value
    struct BSTreeNode
    {
    public:
        BSTreeNode(const K& key,const V& value)
                :_key(key)
                ,_value(value)
                ,_right(nullptr)
                ,_left(nullptr)
        {}

        BSTreeNode<K,V>* _left;
        BSTreeNode<K,V>* _right;
        K _key;
        V _value;
    };
    //下面的定义就是 key 存放的是身份证的信息,value 存放的是票的信息,但是一个人行程中可能有多张票,所以存票的 value 还可以是个 vector 容器(vector<info> _vinfo)







//-----------二叉树的定义
    template<class K,class V>
    struct BSTree
    {
        typedef BSTreeNode<K,V> Node;
    public:
        BSTree()
                :_root(nullptr)
        {}


        //-----------------------------搜索二叉树的插入(key/value 模型)--------------------------------
        bool insert(const K& key,const V& value)
        {
            if(_root==nullptr)
            {
                _root=new Node(key,value);
                return true;
            }

            Node* parent=nullptr;
            Node* cur=_root;

            while(cur)
            {
                if(cur->_key<key)//比较的时候仍然按照 key 进行比较
                {
                    parent=cur;
                    cur=cur->_right;
                }
                else if(cur->_key>key)
                {
                    parent=cur;
                    cur=cur->_left;
                }
                else
                {
                    return false;
                }
            }

            cur=new Node(key,value);
            if(parent->_key<key)
            {
                parent->_right=cur;
            }
            else
            {
                parent->_left=cur;
            }
            return true;
        }




        //--------------------------------中序遍历这个二叉树 (key/value 模型)-------------------------------
        void Inorder()
        {
            _Inorder(_root);
        }

        void _Inorder(Node* root)
        {
            if(root==nullptr)
            {
                return;
            }
            _Inorder(root->_left);
            cout<<root->_key<<":"<<root->_value<<' ';
            _Inorder(root->_right);
        }






        //------------------------------------搜索二叉树的查找(key/value 模型)-------------------------------------
        Node* Find(const K& key)//返回的这个节点里面是存在票的信息的,因为这个模型是一个节点即存放了 key,又存放了 value
        {
            Node* cur=_root;
            while(cur)
            {
                if(cur->_key>key)
                {
                    cur=cur->_left;
                }
                else if(cur->_key<key)
                {
                    cur=cur->_right;
                }
                else
                {
                    return cur;//找的到返回保存元素的节点地址
                }
            }
            return nullptr;//找不到返回空指针
        }





        //--------------------------------搜索二叉树节点的删除(key/value 模型)-----------------------------
        bool erase(const K& key)//删除没有什么需要改变的,只是替换法需要在替换一个 value 的值
        {
            Node* parent= nullptr;
            Node* cur=_root;
            while(cur)
            {
                if(cur->_key>key)
                {
                    parent=cur;
                    cur=cur->_left;
                }
                else if(cur->_key<key)
                {
                    parent=cur;
                    cur=cur->_right;
                }


                else
                {

                    if(cur->_right== nullptr)
                    {
                        if(parent== nullptr)
                        {
                            _root=cur->_left;
                        }
                        else
                        {
                            if(parent->_left==cur)
                            {
                                parent->_left=cur->_left;
                            }
                            else if(parent->_right==cur)
                            {
                                parent->_right=cur->_left;
                            }
                        }
                        delete cur;
                    }

                    else if(cur->_left==nullptr)
                    {
                        if(parent==nullptr)
                        {
                            _root=cur->_right;
                        }
                        else
                        {
                            if(parent->_left==cur)
                            {
                                parent->_left=cur->_right;
                            }
                            else if(parent->_right==cur)
                            {
                                parent->_right=cur->_right;
                            }
                        }
                        delete cur;
                    }

                    else
                    {
                        Node* rightmin=cur->_right;
                        Node* tmp=cur;
                        while(rightmin->_left)
                        {
                            tmp=rightmin;
                            rightmin=rightmin->_left;
                        }
                        cur->_key=rightmin->_key;
                        cur->_value=rightmin->_value;
                        if(tmp!=cur)
                        {
                            tmp->_left=rightmin->_right;
                        }
                        else
                        {
                            tmp->_right=rightmin->_right;
                        }
                        delete rightmin;
                    }

                    return true;
                }
            }
            return false;
        }

    private:
        Node* _root;
    };
}


//搜索二叉树最大的问就是他会退化,退化成单支,比如有序地插入.     也就和链表没什么区别,怎么解决这个问题呢?
//avl 和红黑树能解决,但是后面才学到
// 二叉树进阶oj 没做,二刷再说