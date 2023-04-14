//这两个容器在功能上是和 map,set是完全一样的,只是在底层的实现是不一样的
//这两个容器在底层的实现是哈希表
//set 对应 unordered_set     map对应 unordered_map                    unordered:无序的
//map set的搜索查找,这两个新的容器同样能够使用
//记住 set 不支持更改元素的值.但是 map 支持更改元素的值
//记住 map 和 unmap 的[]是用来使用键的




//一丶  这两种容器和 map set的区别
//1.unordered_xxx的容器遍历不按照 key 排序,从容器的命名中就能看出来
//2.unorder_xxx 他们的迭代器是一种单向迭代器
//3.最最最重要的是 unordered_xxx的综合效率最高

//#include<iostream>
//using namespace std;
//#include<unordered_map>
//#include<unordered_set>
//
//
//
//
////------------------------这个测试是用来测试 unordered_map这个容器的-------------------------------
//void test_unordered_map()
//{
//
//}
//
//
//
//
//
////-----------------------这个测试是用来测试 unordered_set这个容器的----------------------------------
////set是排序+去重
////unordered_set是单纯的去重   并没有排序
//void test_unordered_set()
//{
//    unordered_set<int>us;
//    us.insert(1);
//    us.insert(1);
//    us.insert(6);
//    us.insert(9);
//    us.insert(3);
//    us.insert(3);
//    us.insert(7);
//    us.insert(5);
//
//    unordered_set<int>::iterator it=us.begin();
//    while(it!=us.end())
//    {
//        cout<<*it<<' ';
//        ++it;
//    }
//    cout<<endl;
//    for(auto e:us)
//    {
//        cout<<e<<' ';
//    }
//    //us.find()返回的是迭代器
//    //us.erase()同样是两个版本,一种是删除指定的元素,另一种是删除迭代器所指向的位置的元素
//}
//
//
////这个函数是不去重的版本
//void test_unordered_multiset()
//{
//    unordered_multiset<int>ums;
//    ums.insert(1);
//    ums.insert(1);
//    ums.insert(2);
//    ums.insert(3);
//
//    for(auto e:ums)
//    {
//        cout<<e<<' ';
//    }
//}
//
//
//
//
//
//
//
//
////-----------------------------------这两个无序的容器的和之前的存储的容器的效率对比-----------------------------
//#include<time.h>
//#include<random>
//#include<vector>
//#include<set>
//
////明显的能够看出来,在乱序的元素,或者重复的元素非常多unordered_set的插入的时间更短
////但是插入的元素有序或者接近有序set 插入的时间较短
////除了测试的插入的时间对比,find(查找),erase(删除)的时间也是这样
//
////unordered_set的查找是非常快的,如果遇见查找的场景比较多的情况,就可以使用 unordered_set
//void comp()
//{
//    int n=1000000;
//    vector<int>v;
//    v.reserve(n);
//    srand(time(NULL));//初始化的时间种子
//
//    for(int i=0;i<n;++i)
//    {
//        v.push_back(rand());
//    }
//
//
//    //此处是 unordered_set 的时间
//    unordered_set<int>us;
//    size_t begin2=clock();
//    for(auto e:v)
//    {
//        us.insert(rand());
//    }
//    size_t end2=clock();
//    cout<<"unordered_set插入 10000 个元素需要的时间:"<<end2-begin2<<endl;
//
//    //此处是 set 的时间
//    set<int>s;
//    size_t begin3=clock();
//    for(auto e:v)
//    {
//        s.insert(rand());
//    }
//    size_t end3=clock();
//    cout<<"set容器插入 10000个元素所需要的时间:"<<end3-begin3<<endl;
//
//}


//int main(void)
//{
////    test_unordered_set();
////    cout<<endl;
////    test_unordered_multiset();
//
//    comp();
//}