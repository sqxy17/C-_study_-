//一丶  二叉搜索树                  ----就特么是用来搜索数据的
//1.二叉搜索树的概念
//---二叉搜索树又称二叉排序树,它是一棵空树,或者是有以下性质的二叉树:
//若它的左子树不为空,则左子树上所有节点的值都小于根节点的值
//若它的右子树不为空,则右子树上所有节点的值都大于根节点的值
//它的左右子树也分别是二叉搜索树

//小小的总结一下,也就是根节点的右子树上的所有的节点值都大于根节点,左子树上的所有节点的值都小于根节点    并且子树也符合这个规律(如果存在的话)



//2.查找的最大次数也就是树的高度次        时间复杂度就按照满二叉树计算
//但是这种搜索二叉树是不成熟的            ------后面有平衡搜索二叉树来解决 平衡二叉树还会衍生出  avl树,红黑树




//------------------------------------------以下实现的是 key 模型,这个模型就是专门用来搜索的----------------------------------------

//二丶  实际实现             ----m默认搜索二叉树不能有重复的值,只是说特殊的地方可以用
//#include<iostream>
//using namespace std;
//
//
////-------二叉树单个结点的定义
//template<class K>//这个k代表的意思是key
//struct BSTreeNode//BinaarySearchTreeNode   二叉搜索树
//{
//public:
//    BSTreeNode(int key=0)
//    :_key(key)
//    ,_right(nullptr)
//    ,_left(nullptr)
//    {}
//
//    BSTreeNode<K>* _left;
//    BSTreeNode<K>* _right;
//    K _key;
//};
//
//
//
//
////-----------二叉树的定义
//template<class K>
//struct BSTree
//{
//    typedef BSTreeNode<K> Node;
//public:
//    BSTree()
//    :_root(nullptr)
//    {}
//
//
//    //-----------------------------搜索二叉树的插入--------------------------------
//    bool insert(const K& key)//我们要保证插入之后还要是搜索二叉树
//    {
//        if(_root==nullptr)//也就是这个是空指针的情况下,也就是没有第一个节点,那就要创建一个节点
//        {
//            _root=new Node(key);
//            return true;
//        }
//        //到达了这里也就证明了已经存在了头结点
//        Node* parent=nullptr;//如果已经是存在很多数据了,要经过一系列比较才能进行插入    这个就是用来待链接的节点的
//        Node* cur=_root;
//
//        while(cur)
//        {
//            if(cur->_key<key)
//            {
//                parent=cur;
//                cur=cur->_right;
//            }
//            else if(cur->_key>key)
//            {
//                parent=cur;
//                cur=cur->_left;
//            }
//            else
//            {
//                return false;//相等就是错误的
//            }
//        }
//
//        cur=new Node(key);
//        if(parent->_key<key)
//        {
//            parent->_right=cur;
//        }
//        else
//        {
//            parent->_left=cur;
//        }
//        return true;
//    }
//
//
//
//
//    //--------------------------------中序遍历这个二叉树 -------------------------------          ----并且中序就是排序+去重
//    void Inorder()
//    {
//        _Inorder(_root);
//    }
//
//    void _Inorder(Node* root)     //但是这种方式在调用的时候需要穿进去根节点,可以设置一个得到根节点地址的公共函数,也可以套个壳
//    {
//        if(root==nullptr)
//        {
//            return;
//        }
//        _Inorder(root->_left);
//        cout<<root->_key<<' ';
//        _Inorder(root->_right);
//    }
//
//
//
//
//
//
//    //------------------------------------搜索二叉树的查找-------------------------------------
//    Node* Find(const K& key)
//    {
//        Node* cur=_root;
//        while(cur)
//        {
//            if(cur->_key>key)
//            {
//                cur=cur->_left;
//            }
//            else if(cur->_key<key)
//            {
//                cur=cur->_right;
//            }
//            else
//            {
//                return cur;//找的到返回保存元素的节点地址
//            }
//        }
//        return nullptr;//找不到返回空指针
//    }
//
//
//
//
//
//    //----------------------------------搜索儿二叉树某个结点的删除-------------------------------------
//    // !!!!重难点  要记得叶结点删除的时候,其父节点的左(右)要置为空,否则会成为野指针
//    //删除节点有三种情况,没有孩子的节点(可以当做只有一个孩子的处理)  只有一个孩子的结点   只有两个孩子的结点
//    //假设待删除的节点N1还有两个子节点            ----用的到的一种方法就是替换法
//    //替换的精髓就是从N1节点的所有子节点找到一个,如果还放在当前位置的情况下,大小关系依然成立就删除之找到的那个节点替换到这里来,并将N1删除
//    //其最好的两个节点就是N1的右子树的最左节点      N1的左子树的最右节点
//    bool erase(const K& key)
//    {
//        Node* parent= nullptr;//parent要记录找到的值的结点的父结点,如果值在根节点里面,parent 就是 nullptr
//        Node* cur=_root;
//        while(cur)
//        {
//            if(cur->_key>key)
//            {
//                parent=cur;
//                cur=cur->_left;
//            }
//            else if(cur->_key<key)
//            {
//                parent=cur;
//                cur=cur->_right;
//            }
//
//
//            else//从这下面为在 cur 中找到的场景,请注意 cur 可能是根节点,要合理的处理这种情况
//            {
//                //找到了这个节点之后,需要分情况了,要删除的这个节点是不是没有子节点(或者只有一个子节点?)  或者有两个子节点
//                //要清楚 cur 是当前存放着 key 的结点,删除的就是这个
//                if(cur->_right== nullptr)//没有左子树的和之只有根节点的符合
//                {
//                    if(parent== nullptr)//如果删除的是头结点
//                    {
//                        _root=cur->_left;
//                    }
//                    else
//                    {
//                        if(parent->_left==cur)
//                        {
//                            parent->_left=cur->_left;
//                        }
//                        else if(parent->_right==cur)
//                        {
//                            parent->_right=cur->_left;
//                        }
//                    }
//                    delete cur;
//                }
//
//                else if(cur->_left==nullptr)//只有没有右子树的符合
//                {
//                    if(parent==nullptr)
//                    {
//                        _root=cur->_right;
//                    }
//                    else
//                    {
//                        if(parent->_left==cur)
//                        {
//                            parent->_left=cur->_right;
//                        }
//                        else if(parent->_right==cur)
//                        {
//                            parent->_right=cur->_right;
//                        }
//                    }
//                    delete cur;//在这里释放是因为有两个字节点的,释放的并不是 cur,而是替换的那个节点
//                }
//
//                else//这种情况就是删除的子节点肯定是有两个子节点的,就只能开始替换法了
//                {
//                    //cur这个地址不能动,因为是记录这找到的那个节点的
//                    //并且下面的方法找的的右子树的最左结点       ----左子树的最右结点也是相同的
//
//                    Node* rightmin=cur->_right;       //不管此处cur是不是根节点都无所谓
//                    Node* tmp=cur;
//                    while(rightmin->_left)
//                    {
//                        tmp=rightmin;
//                        rightmin=rightmin->_left;
//                    }
//                    cur->_key=rightmin->_key;
//                    if(tmp!=cur)
//                    {
//                        tmp->_left=rightmin->_right;
//                    }
//                    else
//                    {
//                        tmp->_right=rightmin->_right;
//                    }
//                    delete rightmin;
//                }
//
//                return true;//找的到返回保存元素的节点地址
//            }
//        }
//        return false;//找不到返回空指针
//    }
//
//
//
//    //----------------------------递归的方法进行查找-----------------------
//    bool FindR(const K& key)
//    {
//        _FindR(_root,key);//传过去的时候自带 this
//    }
//
//    Node* _FindR(Node* root,const K& key)
//    {
//        if(root==nullptr)
//        {
//            return nullptr;
//        }
//        else
//        {
//            if(root->_key>key)
//            {
//                return _FindR(root->_left,key);
//            }
//            else if(root->_key<key)
//            {
//                return _FindR(root->_right,key);
//            }
//            else
//            {
//                return root;
//            }
//        }
//    }
//
//
//    //-----------------------------递归的方式进行插入----------------------------
////虽然但是,尽量不要用递归的的方式进行插入,如果深度深会崩
//    bool insertR(const K& key)
//    {
//        _insertR(_root,key);
//    }
//
//    bool _insertR(Node*& root,const K& key)//这里的指针的引用非常关键,没有这个引用将不会正常的插入
//    //这里用引用的原因是因为,这个root,相当于上一个结点 left 或者 right 的别名,让他们的别名指向新创建的结点,就相当于父结点成功连接上了子节点
//    //这里的引用就相当上个结点的子节点的别名!!!!!
//    {
//        if(root==nullptr)
//        {
//            root=new Node(key);
//            return true;
//        }
//
//        if(root->_key>key)
//        {
//            return _insertR(root->_left,key);
//        }
//        else if(root->_key<key)
//        {
//            return _insertR(root->_right,key);
//        }
//        else
//        {
//            return false;
//        }
//    }
//
//
//
//    //----------------------------递归的方式进行删除----------------------------
//    bool eraseR(const K& key)
//    {
//        return _eraseR(_root,key);
//    }
//
//    bool _eraseR(Node*& root,const K& key)//请注意,传入的是指针的别名,将指针指向的空间释放掉并不会指针,指针还会存在
//    {
//        if(root==nullptr)//作用 1:递归到空子树也找不到,会报错           作用 2:防止传空根节点
//        {
//            return false;//找到最后一个了还没找到就返回 false
//        }
//
//        if(root->_key>key)
//        {
//            return _eraseR(root->_left,key);
//        }
//        else if(root->_key<key)
//        {
//            return _eraseR(root->_right,key);
//        }
//
//        else//下面的都是找到 key 值时出现的各种情况
//        {
//            Node* del=root;//这个变量主要是用于没有子节点或者只有一个结点的情况下用于删除
//            if(root->_left==nullptr)
//            {
//                root=root->_right;
//            }
//            else if(root->_right==nullptr)
//            {
//                root=root->_left;//这个是指针的别名
//            }
//            else//虽然是递归,还是要考虑没有父结点有两个子节点的情况
//            {
//                Node* min=root->_right;
//                while(min->_left)
//                {
//                    min=min->_left;
//                }
//                swap(min->_key,root->_key);
//
//                //递归到右子树去删除
//                return _eraseR(root->_right,key);//或者_eraser(root->_right,min->key);
//            }
//            delete del;
//            return true;
//        }
//    }
//
////二叉树进阶的oj 没有看,二刷的时候全部做完
//private:
//    Node* _root;
//};











