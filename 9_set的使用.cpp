//前言:在初阶阶段,我们已经接触过 STL 中的部分容器,如 vector,list,deque,forward_list,等这些容器统称为序列是容器,因为其底层尾线性序列的数据结构,里面存储的是元素本身.
//那什么是关联式容器?它与序列容器有什么关系?

//学完这节容器就分为:序列式容器(可以说这个就是为了存放数据)         关联式容器 (map/set,底层可以说是搜索树),


//一丶    首先这两个也是容器    -----关联式容器
//1. 关联式容器                 -----关联式数据一般就是存储数据的同时查找数据
//关联式容器也是用来存储数据的,与序列式容器不同的是,其里面存储的是<key,value>结构的键值对,在数据检索时,比序列式容器效率更高

//2.键值对
//用来表示具有一一对应关系的一种结构,该结构中一般只包含两个成员变量 key 和 value,   key 代表键值,value 表示与 key 对应的信息.
//---比如现在要建立一个英汉互译的字典,那该字典中必然有对应得英文单词和对应的中文意思.  并且这个英文单词和中文含义是一一对应的,通过该单词,就能找到对应的中文含义








//二丶 set 的大致使用
//1.set 的底大致就是一个搜索树(并且是一个 key 的模型
// template < class T,                        // set::key_type/value_type                  -----compare 是一个仿函数
//           class Compare = less<T>,        // set::key_compare/value_compare              -----空间配置器,也就是内存池
//           class Alloc = allocator<T>      // set::allocator_type
//           > class set;)

//容器都有迭代器,这个 set 还是一个容器.底层是平衡二叉树(红黑树)


#include<iostream>
#include<set>
using namespace std;


void my_print(set<int>& s1)
{
    set<int>::iterator it=s1.begin();       //一定要记住 set 的底层是一个二叉树,也就是一个个节点组成的,不是数组那样的连续的空间
    while(it!=s1.end())
    {
        cout<<*it<<' ';
        ++it;
    }
}
//
//void test_set1()//简单的遍历
//{
//    set<int>s;
//    s.insert(3);
//    s.insert(1);
//    s.insert(1);
//    s.insert(5);
//    s.insert(2);
//    s.insert(8);
//    s.insert(8);
//    //虽然有两个 8 和 1,但是在插入的的时候,只会讲值插入一次,在自己实现的时候重复插入会返回 false,还有这个搜索二叉树的插入本质就是排序+去重
//
////搜索树走中遍历输出是有序的         平衡二叉树也是搜索二叉树的一种
//    my_print(s);     //一定要记住 set 的底层是一个二叉树,也就是一个个节点组成的,不是数组那样的连续的空间
//}
//
//
//
////--------------------set 容器元素的删除-------------------            常用的是前两个
////(1)void erase (iterator position);          //给一个迭代器位置
////(2)size_type erase (const value_type& val);      //这个版本是传值删除 ,返回值就是 size_t类型的整数,就是返回被删除数据的个数
////(3)void erase (iterator first, iterator last);
//void test_set2()
//{
//    set<int>s;
//    s.insert(3);
//    s.insert(1);
//    s.insert(5);
//    s.insert(2);
//    s.insert(8);
//
//    my_print(s);
//    //使用第一个删除需要搭配 find,返回迭代器的位置
//    set<int>::iterator pos=s.find(3);      //这一堆就相当于 s.erase(3),可以理解为是传值删除的一个封装
//    if(pos!=s.end())
//    {
//        s.erase(pos);//这个元素的删除使用的是第一个版本的          ---这个版本是删除一个位置,要保证迭代器有效(不能失效)
//        //find 查找失败返回的是最后一个元素的后一个位置
//    }
//    cout<<endl;
//    my_print(s);
//}
//
//int main(void)
//{
//    test_set2();
//}











//二丶 multiset        multi:多种//这个还是在头文件
//这个也是一个容器,但是和 set 这个容器是有区别的
//这个容器是允许插入重复的值的,set 容器是不准插入重复的值的

//--也就是 set 是排序+去重      multiset 排序
void my_print(multiset<int>& s1)
{
    multiset<int>::iterator it=s1.begin();       //一定要记住 set 的底层是一个二叉树,也就是一个个节点组成的,不是数组那样的连续的空间
    while(it!=s1.end())
    {
        cout<<*it<<' ';
        ++it;
    }
}

void test_multiset()
{
    multiset<int>s;
    s.insert(3);
    s.insert(3);
    s.insert(1);
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(8);

//    my_print(s);

    //由于这个容器能插入重复的值,所以在 find 的时候,查找的值是哪一个值?例如 find(3),返回的是哪一个 3 的地址
    multiset<int>::iterator pos=s.find(3);//找到的是中序的第一个 3           ----中序遍历就是按升序的方式进行输出
    while(pos!=s.end())
    {
        cout<<*pos<<' ';
        ++pos;
    }
}



//-------------------------multiset 容器的删除--------------
//(1)void erase (iterator position);
//(2)size_type erase (const value_type& val);            //返回 size_t的意义在这里,删除同样的会返回删除的数量
//(3)void erase (iterator first, iterator last);


void test_multiset2()
{
    multiset<int>s;
    s.insert(3);
    s.insert(3);
    s.insert(1);
    s.insert(5);
    s.insert(2);
    s.insert(8);
    s.insert(8);

    //能删除重复的 3
//    s.erase(3);
//    my_print(s);


    multiset<int>::iterator pos=s.find(8);
    while(pos!=s.end() && *pos==8)
    {
        auto next=pos;
        ++next;
        s.erase(pos);
        pos=next;
    }
    my_print(s);
}




//--------------------multiset 容器不能通过迭代器进行修改,可以认为是常量,因为修改了之后可能就不是搜索树了


//int main(void)
//{
//    test_multiset2();
//}