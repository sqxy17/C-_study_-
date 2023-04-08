#include<iostream>
using namespace  std;


//回顾:
//构成多态:运行时决议,运行时决定调用谁
//----要在虚表中寻找虚函数,最后call 的是eax寄存器里面的地址,没有确切的地址   call eax

//不构成多态:编译时决议,编译时决定调用谁
//----也就是说在转成汇编代码的时候就已经确定要使用哪个函数了,call 了确定的地址  001028h4之类的确定地址

//虚表在表的最后一个元素后面会添加一个nullptr



//一丶  多态章节的后续补充
//取出虚表
//首先从本质角度说:这个是虚指针是 :函数指针数组   (虚函数指针数组)



class base{
public:
    virtual void func1(){cout<<"func1"<<endl;}
    virtual void func2(){cout<<"func2"<<endl;}
private:
    int _a=10086;
};

class derive:public base{          //----derive: 获得取得
public:
    virtual void func1(){cout<<"derive::func1"<<endl;}
    virtual void func3(){cout<<"derive::func3"<<endl;}
    void func4(){cout<<"derive::func4"<<endl;}
private:
    int _b=10087;
};

typedef void(*vf_ptr)(); //    首先要记得函数指针void(*)(int,int);   这种就是函数指针,指针的变量在*后面定义     接着就是函数指针数组void(*[100])(int,int)
//这个就是将函数指针进行了重定义

void printfVF(vf_ptr* table)//这样就是数组类型的指针           ---打印虚函数表中的内容
{
    for(int i=0;table[i];++i)
    {
        printf("vft[%d]:%p\n",i,table[i]);
        table[i]();//成功的调用函数了
    }
}




//int main(void)
//{
//    base b;
//    //虚表指针是在构造函数的参数列表时初始化的
//    derive d;
////    derive类型创建的变量其虚表存放的是 重写的func1地址,继承的func2地址    ,但是func3 在监视窗口不可见,其实也是在虚表当中的
//
//    printfVF((vf_ptr*)(*(long*)&b));
//    //所以哪怕是子类是私有的虚函数了,通过地址还是能找到虚函数的地址并且调用
//    return 0;
//}

//他娘的,二刷用win系统,这边没法实操看的一知半解
//课件上的题必须他娘的做了,
//后面的指针偏移的那部分跳过去了

//后续的补充:inline函数:
//如果不构成多态,这个函数保持 inline 属性,如果构成多多态,这个函数就没有 inline 属性了,因为调用的是到对象的虚函数表中找到虚函数地址,实现嗲用无法使用 inline 属性
//----这个实在题目中的,二刷给我好好的认真看一遍

