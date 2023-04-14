//#pragma once
//#include"13_14_用于封装 map 和 set 的改装红黑树.h"
//
//
////如果想用红黑树的实现,来是实现这两种数据结构,一个是 key-value 的结构,一个是 key 的结构.  如果实现两棵树就会造成代码的冗余
////那么应该
//
//
////set 是一种 key 的数据结构
//namespace llk_set
//{
//    template<class K,class V>
//    class set
//    {
//    public:
//        bool insert(const K& key)
//        {
//            return _t.insert(key);
//        }
//    private:
//        RBTree<K,K> _t;
//    };
//}
//

