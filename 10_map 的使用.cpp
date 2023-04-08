//map 同样分为 map multimap
//并且 map 是 key/value 的结构    也就是通过一个值查找另外一个值


//template < class Key,                                     // map::key_type
//        class T,                                       // map::mapped_type
//        class Compare = less<Key>,                     // map::key_compare
//        class Alloc = allocator<pair<const Key,T> >    // map::allocator_type
//> class map;

//pair:键值对      并且这个键值对也是一个类

//map 的使用比 set 的使用稍微复杂点    ,迭代器也是一种双向迭代器



#include<iostream>
using namespace std;
#include<string>
#include<map>





//single element (1)pair<iterator,bool> insert (const value_type& val);
//---这个版本下的 value_type是被重定义的  value_type原型是这样的 pair<const key_type,mapped_type>

//with hint (2)iterator insert (iterator position, const value_type& val);
//range (3)template <class InputIterator>
//void insert (InputIterator first, InputIterator last);          ---这个的意思就是能通过迭代器进行删除



//template <class T1, class T2> struct pair;   这个是键值对,pair,同时也是一个类

//首先展示一下插入
void  test_map()
{
    map<string,string>dict;
    dict.insert(pair<string,string>("sort","排序"));  //也可以换成下面的这种写法,这样写是等价的

    pair<string,string>kv1("apple","苹果");
    dict.insert(kv1);

    //再或者有第三种方式进行插入    ----上面的两种都是需要定义出 string
    dict.insert(make_pair("test","测试"));//和第一种的方式差不多,但是可以自动推导类型             ---这个函数的展开是交给编译器展开了

//    map<string,string>::iterator it=dict.begin();
    auto it=dict.begin();
    while(it!=dict.end())
    {
//        cout<<*it<<' ';//这里的流输出失败的原因是因为键值对时间上是一个类,也就是一个节点中存放的是一个类对象,所以<<不支持,自定义类型需要重载出来一个
        cout<<it->first<<':'<<it->second<<endl;//因为是对象,所以这样才是正确的输出的方式
        ++it;
    }


    //还可以使用范围for
    for(auto e:dict)
    {
        cout<<e.first<<':'<<e.second<<endl;//因为是对象,所以这样才是正确的输出的方式
    }
    //插入的同时还是会进行排序
}
//这边的 make_pair就是这样的
//template< class T1, class T2 >
//constexpr std::pair<V1,V2> make_pair( T1&& t, T2&& u );





//-------map 中的 key 不支持修改,但是 map 中的 value 是支持修改的
void test_map1()
{
    string arr[]={"苹果","香蕉","苹果","香蕉","苹果","香蕉","橙子","樱桃"};
    map<string,int>countmap;
//    for(auto& e:arr)
//    {
//        map<string,int>::iterator pos=countmap.find(e);//这样的写法是有一定的缺陷的,因为会涉及到两次查找   一次是 int,一次是 insert
//        if(pos!=countmap.end())
//        {
//            pos->second++;
//        }
//        else
//        {
//            countmap.insert(make_pair(e,1));
//        }
//
//    }



//    所以 map 的插入还能这样
//            pair<iterator,bool> insert (const value_type& val);   //并且 插入是有一个这样的形式的  这样的形式键值对
//    这个模式下的插入对应了两张情况
//    p1.插入成功:bool=true  iterator 就是新插入的元素的迭代器
//    p.2 插入失败:bool=false  iterator 就是已存在的元素的那个迭代器
    for(auto& e:arr)
    {
        pair<map<string,int>::iterator,bool>kv=countmap.insert(make_pair(e,1));//pair<map<string,int>::iterator,bool>这一堆等价于 auto,前提是自己得清楚
        //pair 的 first 是一个迭代器类型的指针,刚好指向这个迭代器是map 类型的,map 类型的迭代器也是有 first 和 second (键和值)
        if(kv.second==false)
        {
            kv.first->second++;
        }
    }

    for(auto& e:countmap)
    {
        cout<<e.first<<':'<<e.second<<endl;
    }
}






//map 中[]的使用场景
//mapped_type& operator[] (const key_type& k); //----这个是官方的标准库定义的方法
//return (*(        (this->           insert(make_pair(k,mapped_type()))            ).first)         ).second      这个可以说就是这个[]的内部的实现全部
//mapped_type()  这是匿名对象,在这个地方是 int 类型的    int()就是 0
//insert 其中的一个版本在上面的解释已经说了,返回的是一个 pair类型的值
//---总的就是使用了这个insert 的返回值,返回值的 pair 的 first 是一个 map 类型的迭代器,然后通过迭代器操作 second,这个[]就是用来操作 value 的

//--key_type 这个就是键值对的键,类型重定义            这个是参数
//--mapped_type  这个是 value 的引用,类型重定义        这个相当于返回的 value的引用

//---map 中的[]和之前是有一些不一样的,之前的都是一些数组的行为
void test_map2()
{
    string arr[]={"苹果","香蕉","苹果","香蕉","苹果","香蕉","橙子","樱桃"};
    map<string,int>countmap;
     for(auto& e:arr)
     {
         countmap[e]++;//就相当于 countmap.operator[](e)++         ,并且请注意,这个函数返回的是值的引用,也就是通过操作[键],就能操作这个值
     }

    for(auto& e:countmap)
    {
        cout<<e.first<<':'<<e.second<<endl;//因为 int 的匿名对象是 0,所以第一次插入的时候插入的是 0 次
    }
}
//除了上面的[]的展示的修改,还有一些其他的功能       --一定要记住返回值是 value 的引用
//--插入         //--
//--查找(对应的 value)          但是使用[]进行查找会出现问题的,如果没有这个键,会成为插入  比如 cout<<countmap["火龙果"]<<  没有的情况下会进行插入,有的情况下才会进行输出
//--修改(对应的 value)







//--------------------------------------------multimap的使用方法--------------------------------
//也就是说这个版本可以重复的插入相同的值,比如可以插入三个苹果
//这个容器查找最好还是用find






//int main(void)
//{
//    test_map2();
//}

//oj