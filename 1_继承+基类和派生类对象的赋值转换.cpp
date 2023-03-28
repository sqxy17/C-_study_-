//前言:继承重点
//1.继承的概念和定义
//2.基类和派生类对象赋值转换
//3.继承中的作用域
//4.派生类的默认成员函数
//5.继承和友元
//6.继承和静态成员
//7.复杂的菱形继承及菱形虚拟继承
//8.继承的总结和反思





//一.继承的概念和定义
//1.继承的概念            ----继承的本质就是复用
//继承机制是面向对象程序设计使代码可以复用的重要手段,他允许程序员在保持原有类特性的基础上进行扩展,增加功能,这样产生新的类,称为派生类.
//继承呈现了面向对象程序设计的层次结构,体现了由简单到复杂的认知过程.    继承是类设计成次的复用


//2.举个例子
#include<iostream>
using namespace  std;
#include<string>
//class student
//{
//private:
//    //首先是两个类相同的成员(两个类拥有想同性质的成员变量)
//    string name;//名字
//    size_t idcard;//身份证号
//    size_t _age;//年龄
//    string _addrss;//住址
//
//    //学生类专有的属性
//    size_t _stuid;//学号
//};
//
//class teacher
//{
//    string name;//名字
//    size_t idcard;//身份证号
//    size_t _age;//年龄
//    string _addrss;//住址
//
//    //教室类专有的属性
//    size_t _jobid;//职工号
//};





//3.解决办法
//因为两个类有很多相似的成员变量,所以我们应该像下面的这样设置
//将两者共有的信息都放在一个父类当中(有的地方也叫做基类),然后我们再学生类和教师类都叫做子类
//子类只需要完成继承父类

//class person//这个就叫做父类(也叫做基类)
//{
//public:
//    void print()
//    {
//        cout<<_name<<endl;
//        cout<<_age<<endl;
//    }
//private:
//    string _name="zhangsan";//名字
//    size_t _idcard;//身份证号
//    size_t _age=18;//年龄
//    string _addrss;//住址
//};

//继承父类创建学生类
//子类也叫做派生类
//继承不仅仅是继承成员变量,还会继承父类的成员函数
//class student:public person         //看清继承的格式   : + 限定符  + 父类名
//        //这个地方的语法就叫做继承
//{
//private:
//    size_t _stuid;
//};
//
//
//class teacher:public/*这个public可以改成其他的*/ person
//{
//private:
//    size_t _jobid;
//};
//
//
//int main(void)
//{
//    student s1;
//    teacher t1;
//
//    s1.print();//也就是说继承不但能继承父类的成员变量,还能继承父类的成员函数
//    t1.print();
//    return 0;
//}














//三丶  三种继承方式的区别
//class person        //-----如果父类中的成员有三种访问限定符,也就是说有三种成员
//{
//public:     //将父类中各种访问限定符下的成员,以不同的方式继承到子类当中去的时候,这些成员会在子类中什么访问限定符下出现?
//    void print()
//    {
//        cout<<_name<<endl;
//        cout<<_age<<endl;
//    }
//private:
//    string _name="zhangsan";//名字
//    size_t _age=18;//年龄
//
//protected:
//    size_t _idcard;//身份证号
//};
//
//
//class student:public person    //----student是派生类(子类),person是基类(父类),  public是继承方式
//        //继承方式有三种:public继承  protected继承    private继承        这些继承对父类中的各种访问限定符下的成员会有影响
//{
//private:
//    size_t _stuid;//学号
//};
//
//int main(void)
//{
//    student s1;
//    s1.print();//也就是说继承不但能继承父类的成员变量,还能继承父类的成员函数
//    return 0;
//}

//1.首先第一种继承方式   -----public继承
//父类中的public成员:   会变成子类中的public成员
//父类中的protected成员:  会变成子类的protected成员
//父类中的private成员:     在子类当中不可见




//2.第二种继承    -----protected继承
//父类中的public成员:   会变成子类的protected成员
//父类中的protected成员:  会变成子类中的protected成员
//父类中的private成员:   在子类当中不可见




//3.第三种继承     ----private
//父类中的public成员:   成为子类的private成员
//父类中的protected成员:  成为子类的private成员
//父类中的private成员:   在子类当中不可见













//四丶 对三种继承方式的总结
//(1)父类中的private成员对于三种继承方式,在子类中都是不可见的.
// ---这里的不可见是说,父类的私有成员依然被继承到了子类中,但是子类无论是在子类的外面,还是子类的内部都无法访问其继承的父类的私有成员
//(2)保护成员限定符(protected)是因为继承才出现的
//---如果想要子类继承后能够访问父类成员,但是其他地方却不能访问父类成员.那么可以将父类的成员设置成protected
//(3)除了父类的private成员三种继承方式在子类当中都是不可见的,其余继承方式就代表父类中成员继承到子类时所能设置的最大权限的访问限定符

//(4)如果不指明继承方式,那么默认的继承方式是private,用struct定义类继承,不写明继承方式,默认继承方式是public继承
//----class student:person    默认是private继承             struct student:person    默认是public继承

//(5)在实际运用的过程中一般情况下都是public的继承方式,几乎很少使用另外两种继承方式,也不提倡用另外两种的继承方式,实际中的扩展维护性并不强














//五丶   基类和派生类对象复制转换            ----下面的这三点也叫赋值兼容规则
//(1)派生类对象 可以赋值给基类的对象/基类的指针/基类的引用.  -----这里有个形象的说法叫做切片或者切割          (也是父类的兼容关系)
//---寓意就是把派生类那部分切来赋值过去

//(2)基类对象不能赋值给派生类对象
//(3)基类的指针可以通过强制类型转换赋值给派生类的指针,但是必须是基类的指针是只想派生类对象时才是安全的.
//-----这里的基类如果是多态类型,可以使用RTTI的 dynamic cast来进行识别后进行安全转换(在这个地方是只需要简单的了解一下就行)




//1.首先我们要清楚,自定义类型在赋值的时候需要是相同的类型,如果自己没用定义赋值函数,则会使用默认的赋值函数
//----现在有一个问题,怎么实现父类和子类的赋值关系       因为这两个自定义类型是差不多的,如果类型里面的成员相差太大,那么就不建议这样去赋值

//2.子类父类相互赋值的具体实现
//class person
//{
//public:
//    void print()
//    {
//        cout<<_idcard<<endl;
//    }
//
//    void change(size_t x)
//    {
//        _idcard=x;
//    }
//private:
//    size_t _idcard=10087;
//protected:
//    string _name="zhangsan";
//    size_t _age=18;
//
//};
//
//
//class student:public person   //但是切割(切片)的操作仅限公有继承        !!!!!只有公有继承支持下面的三种的赋值方式
//        //因为其他的类型继承可能会出现成员权限的变更,  也就是父类中公有成员通过protected继承之后,在子类中就变成了protected类型的成员
//{
//private:
//    size_t _stuid;
//};

//int main(void)
//{
//    student s1;
//    person p1;
//
//
////    下面的这三个子类给父类赋值的过程叫做--切割(切片)
////    父类对象=子类对象  能通过是因为---赋值兼容
//    p1=s1;//如果将子类的对象赋值给父类是可以直接通过的
//    person* ps=&s1;//甚至父类指针能接受子类的地址
//    person& ps1=s1;//甚至能将s1(子类)给父类的引用                    ps:这三种不存在类型转换,是语法天然的支持的行为  不像int a; double  d=1.1; a=d   这种就出现了隐式类型转换
//    //类型转换会存在临时变量的,能够直接引用就说明不会出现临时变量,也就不存在类型转换的行为
//
//
//    //切割也就是说将子类中有父类的相同的成员,也有子类专属的成员,切割就是让子类中和父类中相同的成员进行赋值
//    //请记住,不但能赋值给父类的指针类型,还能赋值给父类的引用类型
//
//    //但是无论是赋值给父类的指针类型,还是赋值给父类的引用类型,其指针和引用只能操作两者共有的成员,通过父类指针无法操作子类的专属成员
//    //尽量不要在父类中在继承的时候定义私有的成员
//
//
//
//
//
//
//
//    //虽然子类能给父类赋值,但是父类并不能给子类赋值,哪怕是强制类型转换都会出错
////    s1=(student)p1;             //虽然对象不能直接进行赋值,但是指针和引用却可以,赋值的时候强制类型转换就可以了
//    student* ss1=(student*)&p1;//但是需要强制类型转换    不过这样是有风险的,操作指针的时候会存在越界的风险
//    //怎么安全的用子类指针指向父类的对象,后面会讲
//    student& ss2=(student&)p1;
//
//}


//int main(void)//虽然不能访问父类的私有成员,但是还是能通过父类提供的共有成员函数访问私有成员
//{
//    student s1;
//    s1.change(11111);
//    person p1;
//    p1=s1;
//    p1.print();
//    p1.change(234);
//    p1.print();
//
//}



