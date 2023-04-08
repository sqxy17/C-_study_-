#pragma once
#include<iostream>
#include<string>
using namespace std;

//--------------------------------此处的旋转是有问题的,以后再次观看的时候好好检查时哪里出错了---------------------------

//此处实现的还是不许冗余的版本
//此处的avl 树每个节点的平衡因子都是右-左
//触发旋转是因为更新到根节点还是 2 或者-2
//最重要的是怎么实现平衡

template<class K,class V>
struct AVLTreeNode
{
    AVLTreeNode(const pair<K,V>& kv)
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_KV(kv)
    ,_bf(0)
    {}


public:
    AVLTreeNode<K,V>* _left;
    AVLTreeNode<K,V>* _right;
    AVLTreeNode<K,V>* _parent;
    pair<K,V> _KV;

    int _bf;//也就是平衡因子 balance factor
};



template<class K,class V>
class AVLTree
{
public:
    typedef AVLTreeNode<K,V>Node;

    AVLTree()
    :_root(nullptr)
    {}



    //----------------插入-----------------------------
    //ps.1:新插入的结点只会影响祖先的平衡因子(父结点,父结点的父结点等都是祖先结点),其他结点并不会影响
    //ps.2:新插入的结点的平衡因子肯定是 0
    //ps.3:每插入一个结点,都需要更新其祖先结点的平衡因子,
    //ps.4:如果出现了异常的平衡因子(绝对值大于 1 的),就需要旋转平衡处理
    //ps.5:插入结点涉及到平衡因子的更新
    bool insert(const pair<K,V>& kv)//插入的键值对是存在于一个结点当中的
    {
        if(_root==nullptr)
        {
            _root=new Node(kv);
            return true;
        }

        Node* parent=nullptr;
        Node* cur=_root;
        while(cur)//能进到这个循环起码根节点是存在的
        {
            if(cur->_KV.first>kv.first)
            {
                parent=cur;//parent 就是三叉连的连接过程
                cur=cur->_left;
            }
            else if(cur->_KV.first<kv.first)
            {
                parent=cur;
                cur=cur->_right;
            }
            else
            {
                return false;//也就是插入的键已经存在了
            }
        }

        //到达此处的 cur 是一个空指针,但不知道是上一个结点的左子树还是右子树
        cur=new Node(kv);   //----在此处 cur 是新创建的一个结点,保存了新的值并且进行了新的连接
        if(parent->_KV.first>kv.first)
        {
            parent->_left=cur;
            cur->_parent=parent;//也就是说 avl 树的实现可以说两两结点是双向的
        }
        else// parent->_KV.first<kv.first    ---键不可能存在相等的情况,因为在上面如果相等的话就会返回 false
        {
            parent->_right=cur;
            cur->_parent=parent;
        }


//------------------此处是处理插入的平衡因子的-----------------
        //平衡因子的处理情况    -----一共有五种情况
        //ps1:cur==parent->left   parent->bf--
        //ps2:cur==parent->right   parent->bf++
        //ps3:更新以后,parent->bf==0,更新结束           ----因为左右子树平衡了,新插入的结点被插入到低的一端了
        //ps4:更新以后,parent->bf==1或者-1,那就继续往上更新          ----说明更新前 parent->bf是 0,现在变成 1 或者是-1,parent 所在的子树高度变高了
        //ps5:更新以后,parent->bf==2或者-2  ,parent 所在的子树已经不平衡了,需要旋转处理


        //注:在父结点的右边插入,要对父节点的平衡因子进行++,在父结点的左边插入,要对父节点的平衡因子进行--   ,然后一直向上更新,直到某一个祖宗结点平衡因子成为0,或者更新到根节点
        //更新平衡因子,可能会更新到根节点的场景
        while(parent)//---当然这里是空指针的情况下就不能更新了,或者说根节点的的父节点是 nullptr
        {
            if(parent->_left==cur)//if(cur==parent->_left),我认为视频中写反了,这个是原版的
            {
                parent->_bf--;
            }
            else//这个 cur 不是插入在父结点的左边就是插入在父结点的右边
            {
                parent->_bf++;
            }
            //---------到这上面的两个判断就是对父节点的平衡因子进行++或者--的地方


            if(parent->_bf==0)//如果出现了某一个祖宗结点为 0 的情况,那么就可以直接停止更新了
            {
                break;
            }
            else if(parent->_bf==1 || parent->_bf==-1)//---这种情况就是向上跟新的过程,这是比较好的情况
            {
                //没有碰见祖先节点平衡因子为 0 的情况,那么就一直向上更新,直到碰见根节点才停止
                cur=parent;
                parent=parent->_parent;
            }


                //---------------这种情况就是需要旋转处理的, 旋转有四种旋转的方法--------------
                //----旋转的规则就是:保持搜索树的规则  控制平衡
                //---旋转的意义:这棵树平衡了  这棵树整体的高度降低了1

                //ps1:左单旋     ----这种方法是将父结点变成其右结点的左子树   ,通常针对的是单链情况下的右子树,   也就是左子树比右子树的高度高 2
                //---单旋一般是将父节点旋转成为子节点的子节点,但是原子节点如果本身就有子树,会先将原子树的子树给父结点的一侧,然后再将父结点作为子节点的子节点
                //---如果在旋转的过程中,其子树没有子树,那么可以直接将父节点旋转成为子树的子树
                //--记得旋转的时候改变父结点的指向

                //ps2:右单旋      ----这种方法是将父节点变成其左节点的右节点   ,通常是针对单链情况下的左子树,    反过来就是
                //---这个单旋是和上面的那个相反的
                //ps3:
            else if(parent->_bf==2 || parent->_bf==-2)//----旋转才是 avl 的重点!!!!
            {//旋转就是左边子树高进行右单旋,右边子树高进行左单旋
                if(parent->_bf==-2 && cur->_bf==-1)//这样的情况下就是进行的右单旋,因为父结点的平衡因子是负数,是因为父结点的左子树高度较高,要向右旋转   旋转的时候注意根节点的指向
                {
                    rotate_right(parent);
                }
                else if(parent->_bf==2 && cur->_bf==1)//---这种情况就是进行的左单旋,左单旋的方式和右单旋的方式是类似的,只是方向反了.
                {
                    rotate_left(parent);
                }
                else if(parent->_bf==-2 && cur->_bf==1)//
                {
                    rotate_lr(parent);
                }
                else if(parent->_bf==2 && cur->_bf==-1)
                {
                    rotate_rl(parent);
                }
                else
                {
                    assert(0);
                }

                break;     //----旋转完之后,就可以结束了
            }
            else
            {
                //不是上面的五种情况,肯定插入更新平衡因子之前,树中的平衡因子就已经有问题了
                assert(false);
            }

        }
        return  true;
    }


    //----------右单旋的实现----------        rotate:旋转   这个是被上面调用的
    //ps1:旋转之后还要注意控制平衡因子
    void rotate_right(Node*& parent)//右旋的时候有可能是根节点,也有可能是下面的子树的结点       -
    {
        Node* parent_left=parent->_left;//父结点就是要成为这个结点的子节点
        Node* parent_left_right=parent_left->_right;//子结点的右子树
        parent->_left=parent_left_right;//父结点的左指针指向原子结点的右节点
        if(parent_left_right)//也就是说原子结点的右节点如果是存在的情况下,那么他的父结点的指向就要改成 parent 了
        {
            parent_left_right->_parent=parent;
        }

        Node* parentparent=parent->_parent;//因为这个这个旋转的结点可能是根节点,也有可能是下面的子结点,,所以要记录一下最开始的父节点的父节点是谁
        parent_left->_right=parent;//原 子结点的右指针指向父结点
        parent->_parent=parent_left;//父结点的指向同样也会改变

        if(parent==_root)
        {
            _root=parent_left;
            _root->_parent= nullptr;
        }
        else
        {
            if(parentparent->_left==parent)
            {
                parent->_left=parent_left;
            }
            else
            {
                parentparent->_right=parent_left;
            }
            parent_left->_parent=parentparent;//   ----时时刻刻要记住维护这个三叉链
        }
        //---旋转之后就是为了让异常的平衡因子降到零,并且异常的平衡因子一般都是上面的
        parent_left->_bf=parent->_bf=0;
        //也就是说这个旋转之后,其平衡因子也就变为正常了,   在调用了这个函数之后,就可以停止上面的循环了
    }



    //--------------------左单旋的实现---------------
    void rotate_left(Node*& parent)
    {
        Node* parent_right=parent->_right;
        Node* parent_right_left=parent_right->_left;

        parent->_right=parent_right_left;
        if(parent_right_left)//---这里是因为父结点的右节点的左节点可能是空的
            parent_right_left->_parent=parent;

        //---一定要注意,旋转的可能不是根节点,所以还要记录旋转的节点的 parent
        Node* parentparent=parent->_parent;
        parent_right->_left=parent;
        parent->_parent=parent_right;

        if(_root==parent)
        {
            _root=parent_right;
            parent_right->_parent=nullptr;
        }
        else
        {
            if(parentparent->_left==parent)
            {
                parentparent->_left=parent_right;
            }
            else
            {
                parent_right=parentparent;
            }
            parent_right->_parent=parentparent;
        }
        parent_right->_bf=parent->_bf=0;
    }


    //-------------接下来是双旋------------
    //ps1:双旋并不是简单的一边高,而是相对的,相对于某个结点来说,而且是个曲线,具体得看课件的图示
    //ps2:双旋分为左右单旋  ,右左单旋
    //ps3:简单的描述就是从子树到根的顺序,先将异常的子树结点进行旋转,再带上根节点进行旋转.   至于是右左还是左右无看具体情况的高低
    //ps4:双旋的平衡因子调整有些特殊的情况
    //ps5:双旋同样要向上调整平衡因子
    void rotate_lr(Node*& parent)//左右双旋和右左双旋都是有三种情况的
    {
        rotate_left(parent->_left);
        rotate_right(parent);
    }

    void rotate_rl(Node*& parent)//双旋不能依赖单旋的平衡因子的更新(也就是耦合性弱点)
    {
        Node* subR=parent->_right;
        Node* subRL=subR->_left;
        int bf=subRL->_bf;

        rotate_right(parent->_right);
        rotate_left(parent);

        if(bf==1)
        {
            parent->_bf=-1;
            subR->_bf=0;
            subRL->_bf=0;
        }
        else if(bf==-1)
        {
            parent->_bf=0;
            subR->_bf=1;
            subRL->_bf=0;
        }
        else if(bf==0)
        {
            parent->_bf=0;
            subR->_bf=0;
            subRL->_bf=0;
        }
        else
        {
            assert(0);
        }
    }






    //----------------------对于这个 avl 树的中序遍历-------------
    void inorder()
    {
        _inorder(_root);
    }

    void _inorder(Node* root)
    {
        if(root==nullptr)
        {
            return;
        }
        _inorder(root->_left);
        cout<<root->_KV.first<<':'<<root->_KV.second<<endl;
        _inorder(root->_right);
    }









    //-----------------检查 avl 树的高度---------------       //小小的提示一下,只要是成员函数想要用递归,都是要套用函数的
    int height(Node* root)
    {
        if(root==NULL)
        {
            return 0;
        }
        int lheight=height(root->_left);
        int rheight=height(root->_right);

        return lheight>rheight?lheight+1:rheight+1;
    }

    bool isbalance()
    {
        _isbalance(_root);
    }

    bool _isbalance(Node* root)
    {
        if(root==nullptr)
        {
            return true;
        }

        int lheight=height(root->_left);
        int rheight=height(root->_right);

        if(rheight-lheight!=root->_bf)
        {
            cout<<root->_KV.first<<"现在是"<<root->_bf<<endl;
            cout<<root->_KV.first<<"因该是"<<rheight-lheight<<endl;
            return false;
        }
        return abs(rheight-lheight)<2 && _isbalance(root->_left) && _isbalance(root->_right);//abs是一个求绝对值的函数,也就是用来检测 avl 树高度的函数
    }







    //----------------------avl 树的删除仅仅需要理解就行---------------但是建议下面自己去实现一下

private:
    Node* _root;//这个还是根节点
};
//后续总结:
//ps1:旋转的时候请注已经被旋转的父指针的指向
//ps2:双旋的场景就是还是某一个祖宗结点的平衡因子出现了异常,但是算上这个祖宗结点出现异常是因为不是顺序插入,插入新的结点以后出现了  < 或者>  这样的插入情况
//--然后就得对这个祖宗结点进行旋转,这个子节点也要跟着旋转,并且两个的旋转是相反的

//ps3:我们通常是通过avl树的高度来检测是否正常
