//可回去重复的观看


//#include<iostream>
//#include<string>
//using namespace std;
//class A//下面两个继承A的子类是虚继承,所以此处的A也叫做虚基类
//{
//public:
//    int a;
//};
//
//class B:virtual public A
//{
//public:
//    int b;
//};
//
//class C:virtual public A
//{
//public:
//    int c;
//};
//
//class D:public B,public C
//        //在D里面,A放到一个公共位置,那么有时B需要找A,C需要找A,就要通过虚基表中偏移量进行计算
//{
//public:
//    int d;
//};
//
//int main(void)
//{
////    D D2;//这个是没有进行虚继承的
////    D2.B::a=10086;//在内存中存储是和继承顺序有关系的   因为是先继承的B,那么就现在内存中存放10086 2,然后是10087 3,最后存放4
////    D2.C::a=10087;
////    D2.b=2;
////    D2.c=3;
////    D2.d=4;
////    cout<<sizeof(D2)<<endl;
//
//
//    D D2;//这个是进行虚继承的
//    D2.B::a=10086;
//    D2.C::a=10087;
//    D2.b=2;
//    D2.c=3;
//    D2.d=4;
//    cout<<sizeof(D2)<<endl;
//    //虚拟继承的会将两者相同的a,放在一个公共的地方
//    //输出的内存发现会变大,因为存放了几个变量来记录b c d   和公共的a的偏移量
//}
//27节   2:44:00   详细的虚拟继承的在内存中的存储












//二丶 组合  组合是一种has-a的关系,假设B组合了A,每个B对象中都有一个A对象
//-----有限使用对象组合,而不是类继承
//
//class A
//{
//public:
//    int _a;
//};
//
//class B
//{
//public:
//    A A1;//这种就是组合,也是一种类的复用
//    int _b;
//};
//对象组合是类继承之外的另一种复用,新的更复杂的功能可以通过组装或组合对象来货的.对象组要求被组合的对象具有良好定义的接口.(这种复用的方式称为黑箱复用,因为对象内部的细节是不可见得)
///---对象只以黑箱的形式出现.组合类之间没有很强的依赖关系,耦合度低.优先使用组合有助于保持每个类被封装.

//实际尽量多用组合.组合的耦合度低,代码维护性好.

//

//组合没仔细看,28节0:00:00