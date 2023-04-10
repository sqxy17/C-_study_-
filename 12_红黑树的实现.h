//----红黑树是一定需要掌握的,因为后续是需要用这个封装 map 和 set 的

#pragma once
#include<iostream>
using namespace std;


//------------既然是红黑树,那么就需要颜色,颜色是用枚举类型来定义的
enum colour
{
    red,
    black
};




//红黑树单个的结点
template<class K,class V>
class RBTreeNode//红黑树的更新同样是需要三叉链的
{
public:
    RBTreeNode<K,V>* _left;
    RBTreeNode<K,V>* _right;
    RBTreeNode<K,V>* _parent;

    pair<K,V> _kv;

    colour _col;


    RBTreeNode(const pair<K,V>& kv)
    :_left(nullptr)
    ,_right(nullptr)
    ,_parent(nullptr)
    ,_kv(kv)
    ,_col(red)
    {}

};







//红黑树的具体实现
template<class K,class V>
class RBTree
{
public:
    typedef RBTreeNode<K,V> Node;

    RBTree()
    :_root(nullptr)
    {}




    //--------------------------------红黑树也是插入最重要--------------------------
    //新插入的结点都是红的
    //下面的 ps 都是插入时可能出现的场景
    //就是因为插入的结点是红色的,造成了两个红色的挨着,才会向上调整颜色



    bool insert(const pair<K,V>& kv)
    {
        //-------------插入的第一步就是搜索二叉树的插入,并没有什么区别--------------同样还是分为根节点存在和根节点不存在的场景,但是根结点不存在的场景还分为几种场景请注意
        if(_root==nullptr)
        {
            _root=new Node(kv);
            _root->_col=black;
            return true;
        }

        Node* parent=nullptr;//这个parent 变量就是用来记录 cur 的_parent 指针指向结点
        Node* cur=_root;//新增的结点给成红色
        while(cur)//如果根节点不存在就会在上面创建一个结点来进行保存
        {
            if(cur->_kv.first>kv.first)
            {
                parent=cur;//parent 就是三叉连的连接过程
                cur=cur->_left;
            }
            else if(cur->_kv.first<kv.first)
            {
                parent=cur;
                cur=cur->_right;
            }
            else//--这个是插入的键值对的键是相等的,相等的则不进行重复的插入
            {
                return false;
            }
        }

        //到达此处的 cur 是一个空指针,但不知道是上一个结点的左子树还是右子树
        cur=new Node(kv);   //----在此处 cur 是新创建的一个结点,保存了新的值并且进行了新的连接
        cur->_col=red;

        if(parent->_kv.first>kv.first)
        {
            parent->_left=cur;
            cur->_parent=parent;//也就是说 avl 树的实现可以说两两结点是双向的
        }
        else// parent->_KV.first<kv.first    ---键不可能存在相等的情况,因为在上面如果相等的话就会返回 false
        {
            parent->_right=cur;
            cur->_parent=parent;
        }



        //-----------------------从这个地方开始是控制平衡的-----------------------------------------------------------------------------------------------
        //场景一:插入的新结点的父节点如果是红色,那么他的组父节点肯定是黑色,并且它的叔叔结点一定是红的(如果叔叔结点存在的话)            也就是说这种情况是假设叔叔结点存在的情况下
        //---此时的解决办法就是将新插入结点的父节点,叔叔结点,都变成黑的,并且把组父结点改成红的,然后继续向上调整(再将组父结点当做新插入的结点向上进行调整,如果组父结点是根节点的或者组父结点是)
        //---祖父结点变成红色是因为每个路径的黑色结点都是相同的
        //---调整的规则就是每个路径上的黑色结点的数量是相同的,并且红色节点不能连续出现          如果调整到根节点,那么就可以停止了


        //场景二:插入的新结点是红色的,父结点也是红色的,组父结点是黑色的,但是插入的新结点的叔叔结点并不存在的情况/或者叔叔结点是存在的但是叔叔结点颜色是黑色
        //这样的处理方式就是旋转+变色
        //ps1:叔叔结点不存在,将新插入结点的父结点作为旋转点,左旋或者右旋,然后再进行变色
        //ps2:叔叔结点存在,但是叔叔结点是黑色的,依然是旋转后再进行变色            ----ps1,ps2 都可以看作是叔叔节点是黑色,但是父结点是红色的情况下才进行的旋转
        // ---旋转的规则和 avl 树的旋转的规则是相同的,只是说这个红黑树的旋转是发生在两个红色的结点挨着并且叔叔节点不存在或者叔叔存在但是叔叔是黑色的结点.



        //场景三:插入的新的结点是红的,父亲是红的,祖父结点是黑的,叔叔结点不存在,或者叔叔结点存在但是为黑的
        //----和场景二的区别就是,插入的新的结点和父结点是曲线形状的(一般就是父结点是组父结点的左结点,然后新插入结点是父结点的右结点    有或者是父结点是组父结点的右结点,但是新插入的结点是父结点的左结点)

        //旋转的时候是将祖父结点换成父结点的子结点


        //-----------------用得到右旋的场景
        while(parent && parent->_col==red)//-----因为插入的新结点是红色的,所以需要改变的情况也就是新插入的结点的父结点同样是红色的     不为空是因为向上更新到根节点以后就不应再去更新了
        {
            Node* grandfather=parent->_parent;//父结点的父节点,这个是用来变更叔叔结点的时候用到的
            if(grandfather->_left==parent)//这个条件就是说明父亲在祖父的左边
            {
                Node* uncle=grandfather->_right;

                //-----------------场景一:  叔叔结点存在,并且叔叔结点是红色的-----------
                //插入的新结点是红色的,而且不用去注意插入的新结点是父结点的左结点还是右结点.向上染色就可以,前提是叔叔结点是红色的
                if(uncle && uncle->_col==red)
                {
                    parent->_col=uncle->_col=black;
                    grandfather->_col=red;

                    //现在就得继续向上处理的
                    cur=grandfather;
                    parent=cur->_parent;
                }
                //------------------场景二: 叔叔节点不存在,或者叔叔节点存在但是叔叔结点是黑色的,父结点是红色的----------------
                //叔叔结点不存在其实 nil 结点(也就是这里的叶子结点还是黑的,说不存在还是存在的)
                else//一般情况下都是由情况一变更过来的    但是情况一变更过来的情况一共有两种
                {
                    if(cur==parent->_left)//变更过来的第一种就是叔叔结点是黑色或者不存在,并且新插入的结点是父结点的左结点的左结点

                    {
                        rotateR(grandfather);
                        parent->_col=black;
                        grandfather->_col=red;
                    }
                    else//这里的情况是插入的结点是组父结点的左结点的右节点     ----这样就是场景三,需要用到的是双旋
                    {
                        rotateL(parent);
                        rotateR(grandfather);
                        cur->_col=black;
                        grandfather->_col=red;
                    }
                }
            }

            //----------用得到左旋的场景
            //从这里开始是说明父亲是在祖父结点的右边
            else
            {
                Node* uncle=grandfather->_left;
                if(uncle && uncle->_col==red)
                {
                    parent->_col=uncle->_col=black;
                    grandfather->_col=red;

                    //现在就得继续向上处理的
                    cur=grandfather;
                    parent=cur->_parent;
                }
                    //------------------场景二: 叔叔节点不存在,或者叔叔节点存在但是叔叔结点是黑色的,父结点是红色的----------------
                else//一般情况下都是由情况一变更过来的
                {
                    if(cur==parent->_right)//这里是左旋,新插入的结点是父结点的右结点的右结点
                    {
                        rotateL(grandfather);
                        parent->_col=black;
                        grandfather->_col=red;
                    }
                    else//此处的情况就是插入的结点是组父结点的右结点的左结点            ----这种就是场景三,用到的也就是双旋
                    {
                        rotateR(parent);
                        rotateL(grandfather);
                        cur->_col=black;
                        grandfather->_col=red;
                    }
                }
            }
        }
        _root->_col=black;
        return true;
    }



//-------------------------------------下面是左右单旋的实现-------------------------------------------------------------
        //两个单旋本质上和 avl 树的旋转没有什么区别,只是不用再去管理平衡因子

    //----------右单旋的实现----------        rotate:旋转   这个是被上面调用的
    //右旋是成为左结点的右结点
    void rotateR(Node*& parent)//右旋的时候有可能是根节点,也有可能是下面的子树的结点       -
    {
        Node* parent_left=parent->_left;//父结点就是要成为这个结点的子节点
        Node* parent_left_right=parent_left->_right;//子结点的右子树
        parent->_left=parent_left_right;//父结点的左指针指向原子结点的右节点
        if(parent_left_right)//也就是说原子结点的右节点如果是存在的情况下,那么他的父结点的指向就要改成 parent 了
        {
            parent_left_right->_parent=parent;//时刻要记得处理父亲指针
        }

        Node* parentparent=parent->_parent;//因为这个这个旋转的结点可能是根节点,也有可能是下面的子结点,,所以要记录一下最开始的父节点的父节点是谁
        parent_left->_right=parent;//原 子结点的右指针指向父结点
        parent->_parent=parent_left;//父结点的指向同样也会改变

        if(_root==parent)//parent为根结点的情况下
        {
            _root=parent_left;
            _root->_parent= nullptr;
        }
        else
        {
            if(parentparent->_left==parent)
            {
                parentparent->_left=parent_left;
            }
            else
            {
                parentparent->_right=parent_left;
            }
            parent_left->_parent=parentparent;//   ----时时刻刻要记住维护这个三叉链
        }
    }



    //--------------------左单旋的实现-------------------------
    void rotateL(Node*& parent)
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
                parentparent->_right=parent_right;
            }
            parent_right->_parent=parentparent;
        }
    }





    //----------------------对于这个 红黑树的中序遍历-------------
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
        cout<<root->_kv.first<<':'<<root->_kv.second<<endl;
        _inorder(root->_right);
    }





    //------------------------------红黑树的平衡检测---------------------------------
    //--检测的依据就是根据红黑树的那五条性质,但是最重要的额还是就两点
    //ps1:不能出现连续的红色结点
    //ps2:各条路径上面的黑色结点的数量必须是相同的

    //检测各路径上面的黑色结点是否一样的时候,其中的一种方法就是将上面的路径的黑色节点记录到栈中去
    //保存黑色节点数量可以用存放基准值的方法
    //avl 树中的检测是比较详细的,二刷的时候一定要好好弄清楚

    bool isbalance()
    {
        if(_root && _root->_col==red)
        {
            cout<<"根节点不是黑色"<<endl;
            return false;
        }

        int banchmark=0;//这个就是基准值       banchmark:基准             基准值就是随便选一个路径上面的所有黑色结点作为参考值,然后这个结点将会与其他路径的座位比较,出现不同这个树就是错误的
        Node* left=_root;
        while(left)//用最左路径作为基准值
        {
            if(left->_col==black)
            {
                ++banchmark;
            }
            left=left->_left;
        }

        int blacknum=0;//
        return _isbalance(_root,banchmark,blacknum);
    }

    //循环的结点进行嵌套的调用
    bool _isbalance(Node* root,int banchmark,int blacknum)
    {
        if(root==nullptr)
        {
            if(banchmark!=blacknum)
            {
                cout<<"存在黑色结点不相等的路径"<<endl;
            }
            return true;
        }

        if(root->_col==red && root->_parent->_col==red)//红色结点肯定是用父亲结点的
        {
            cout<<"出现了两个红色的挨着的结点"<<endl;
            return false;
        }

        if(root->_col==black)
        {
            ++blacknum;
        }
        return _isbalance(root->_left,banchmark,blacknum) && _isbalance(root->_right,banchmark,blacknum);
    }








    //---------------------------红黑树的删除-----------------------
    //会用就行,了解即可

private:
    Node* _root;
};

//注意:
//ps1:插入红结点比插入黑结点的影响要小
//ps2:三个场景下的更新可以说都是新增的结点是红色,然后和父亲结点新增的颜色是相同的,然后才进行更新(因为不能有两个连续的红色结点挨着)
//ps3:左旋或者右旋的时候,和之前的 avl 树是一样的,将新插入的节点和组父结点相连接,并且将父结点作为新插入结点的子树,并且会将新插入节点的子树给父结点(视左旋或者右旋的情况而定)
//---这里的新插入的节点可能是(因为染色以后的父结点),并不是真正的新插入的结点
//---双旋的第一次旋转只是将两个红色的结点从曲线变成单纯的直线(也就是祖父的左的左,或者祖父的右的右两个都是红色),然后再进行第二次旋转,第二次旋转就是一边高的那种旋转
//---第二次旋转以后,新插入结点就会变成原祖父结点的位置,祖父结点会变成新插入结点的子树,并且组父结点会变成红色

//ps4:单旋的时候,是旋转下来的结点变色变成红色,围绕着旋转的点变成黑色






//补充:红黑树和 avl 树的比较
//红黑树和 avl 树都是高效的平衡二叉树,增删改查的时间复杂度都是 long2 N,红黑树不追求绝对平衡,其只需保证最长路径不超过最短路径的二倍
//相对而言,降低了插入和旋转的次数,所以在经常进行插入和删除的结构中性能比 avl 树更优,而且红黑树的实现比 avl 简单,所以在实际运用中红黑树更多
//---红黑树应用的一些例子:stl 库中的 map/set  java 库  linux 内核



//手撕红黑树大概就是写个插入

