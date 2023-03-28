//前言:从3_中就可以看出.c++对于重写的要求还是比较严格的,但是有些情况下由于疏忽,可能会导致函数名字母次序写反反而无法构成重载.
// 而这种错误在编译器期间是不会报错的,只有在程序运行时没有得到预期的结果才能发现.  ----因此c++11提供了两个关键字,可以帮助检测是否成功重写了

//----override:否决,撤销      final:最终的,完成的


#include<iostream>
using namespace std;
//一丶  如何做到一个类不能被继承
//1.将这个类的构造函数设置为私有成员          ------此处的举例是在c++98的标准下的
//class person
//{
//public:
//     int _a;
//
//     static person creat(int a=0)
//     {
//         return person(a);
//     }
//private:
//    person(int a=0)
//    :_a(a)
//    {}
//};
//因为子类继承之后,其子类构造对象的时候,其继承的父类的构造函数会不可见,也就是说子类将无法构造对象        ---间接的限制这个父类不能被继承

//然后自己的这个类还需要能够实例化对象,因此还要在搞出来一个函数
//int main(void)
//{
//    person A=person::creat(10086);
//}



//--------------------使用final的场景----------------------

//2.上面的c++98这样定义不可继承的类是非常麻烦的,所以c++11给了一个关键字  final:最终的    -----使用了这个关键字以后,这个类将不能在被继承(最终类)

//-----final放在类名的后面,这个类就是最终类,将不能被继承
//class person final
//{
//public:
//    int _a;
//    person(int a=0)
//    :_a(a)
//    {}
//};






//----final还能使函数不能被重写
//class person
//{
//public:
//    int _a;
//
//    virtual void test()final
//    {
//        cout<<"person"<<endl;
//    }
//
//    person(int a=0)
//            :_a(a)
//    {}
//};
//
//
//class student:public person
//{
//public:
//    int _b;
//
//    void test()//只要父类的虚函数带上了virtual关键字,下面的子类的同名函数就不能出现,否则就会报错
//    {
//        cout<<"student"<<endl;
//    }
//};
//
//int main(void)
//{
//    student s1;
//    person p1;
//
//    p1.test();
//    s1.test();
//}

//总结一下:final修饰虚函数,限制他不能被子类的虚函数重写






//-------------------使用override的场景--------------
//这个关键字主要是放在子类重写的虚函数的后面,检查是否完成重写
//没有重写的话会报错
//class person
//{
//public:
//    int _a;
//
//    virtual void test()
//    {
//        cout<<"person"<<endl;
//    }
//
//    person(int a=0)
//            :_a(a)
//    {}
//};
//
//
//class student:public person
//{
//public:
//    int _b;
//
//    void test()override          //---这个关键字主要是放在重写的虚函数的后面的,用来检测是否重写成功,不成功会报错
//    //为什么要检查?如果参数不同,会构成隐藏,并不会报错
//    {
//        cout<<"student"<<endl;
//    }
//};
//
//int main(void)
//{
//    student s1;
//    person p1;
//
//    p1.test();
//    s1.test();
//}













//二丶重载    重写(覆盖)     隐藏(重定义)的对比

//重载:两个函数在同一个作用域        函数名/参数不同          重载也是静态的多态

//重写(覆盖):两个函数分别在派生类和基类的作用域       函数名/参数/返回值,都必须相同(协变除外)     两个函数都必须是虚函数
//---重写是在原理层的

//重定义(隐藏):两个函数分别在基类和派生类的作用域     函数名相同      两个基类和派生类的同名函数不构成重写就是重定义