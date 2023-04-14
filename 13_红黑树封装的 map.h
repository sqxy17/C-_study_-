//#pragma once
//#include"13_14_用于封装 map 和 set 的改装红黑树.h"
////map 的这种数据结构是 k_v结构
//namespace llk_map
//{
//    template<class K,class V>
//    class map
//    {
//    public:
//        bool insert(const pair<K,V>& kv)
//        {
//            return _t.insert(kv);
//        }
//    private:
//        RBTree<K,pair<K,V>> _t;//第二个模板参数决定了结点里存放的是什么
//    };
//}