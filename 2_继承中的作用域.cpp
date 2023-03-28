//一丶 继承中的作用域
//1.在继承体系中,基类和派生类都有独立的作用域
//2.子类和父类有同名成员,子类成员将屏蔽父类对同名成员的直接访问,这种情况叫隐藏,也叫重定义
//-----在子类成员函数中,可以使用基类::基类成员   这样显式的进行访问
//3.需要注意的是,如果是成员函数的隐藏,只需要函数名相同就能构成隐藏
//4.在实际的继承体系中,最好不要定义同名的成员




//二丶 隐藏(重定义)
//也就是父类和子类拥有同名的成员:子类继承父类之后会将父类的同名成员隐藏起来   只有通过::才能访问

//不但同名变量会构成隐藏,同名函数也会构成隐藏,哪怕子类父类只是名字相同,其形参类型个数完全不同         ----只要函数名相同就构成隐藏,和形没有关系
//为什么继承之后同名函数形参不同也不会构成重载呢?  因为重载的条件必须在同一作用域
//虽然继承之后父类成员会变成子类的一部分,但是实际上父类的成员还是可以看做在父类的这个作用域中,就相当于子类当中有一个父类的对象

//1.引例
#include<iostream>
using namespace std;

//class person
//{
//public:
//    void print()
//    {
//        cout<<_name<<endl;
//        cout<<_age<<endl;
//    }
//    size_t _id=11111;
//
//private:
//    string _name="zhangsan";//名字
//    size_t _age=18;//年龄
//};
//
//
//class student:public person
//
//{
//public:
//    void print(int)
//    {
//        cout<<"使用的是子类的输出函数"<<endl;
//    }
//
//    size_t _id=10086;//此处的父类和子类都拥有一个名字为_id的成员函数
//    //但是在子类继承父类之后会有两个_id成员,通过对象访问的时候还是会根据就近原则优先访问自己的成员变量    如主函数中的例子
//};
//
//int a=10086;
//int main(void)
//{
////    //首先回顾一个知识     ----全局内和局域内有同名的变量,优先访问局部的变量   (就近原则)
////    int a=6;
////    cout<<a<<endl;  //输出6
////    //如果想要输出全局变量的同名变量,就要使用::作用域限定符
////    cout<<::a<<endl;//输出10086
//
//
//    student s1;
//    cout<<s1._id<<endl;//现在的这样访问student类对象的成员,访问的是子类原本就有的_id,并不是继承父类的哪个_id       普通的这样访问就是访问子类的_id
//
//    //这样的形式才能访问student类对象继承父类的同名成员
//    cout<<s1.person::_id<<endl;//其实在调试的时候就能发现,父类整个的在子类当中,就好像一个成员一样
//
//    s1.print(4);
//    s1.person::print();//这样是调用父类的同名函数的方法
//}













//三丶 派生类的默认成员函数        (准确的来说有8个默认构造函数)
//1.子类的构造函数必须调用父类的构造函数初始化父类的那一部分成员.  如果父类没有默认的构造函数,则必须在子类构造函数的初始化列表阶段显式调用
//2.子类的拷贝构造函数必须调用父类的拷贝构造完成父类的拷贝初始化
//3.子类的operator=必须调用父类的operato=完成父类的赋值
//4.子类的析构函数会在被调用完成后自动调用父类的析构函数来清理父类成员,这样才能保证子类对象先清理子类成员在清理父类成员的顺序
//5.子类对象初始化,先调用父类构造,在调用子类构造
//6.子类对象析构清理先调用派生类析构,再调用基类的析构



//1.继承中的默认成员函数的使用规则
//派生类的重点是4个默认的成员函数              研究的重点是自己设置和系统自动生成的有什么区别,自己写要做什么事情

//以下举例的是
#include<string>
//class person
//{
//
//public:
//    string name;
//    size_t age;
//
////    person()
////    {
////        name="zhangsan";
////        age=10086;
////        cout<<"父类的构造函数被调用啦"<<endl;
////    }
//
//    ~person()
//    {
//        cout<<"父类的析构函数被调用啦"<<endl;
//    }
//
//    person(person& x1)
//    {
//        cout<<"父类的拷贝构造函数被调用啦"<<endl;
//    }
//
//    person& operator=(person& p1)
//    {
//        cout<<"父类的operator=被调用啦"<<endl;
//    }
//};




//-------这是派生类使用默认成员函数的情况
////父类成员调用父类的构造和析构函数         派生类成员(自己定义的内置类型或者自定义类型)调用派生类的构造和析构
//class student:public person//
//{
//public:
//    size_t id;//学号
//};
//
//
//int main(void)
//{
//    student s1;
//    student s2(s1);
//
//    student s3;
//    s3=s2;
//}
//总结:派生类使用默认成员函数的时候,其继承的父类成员调用的是父类相应的构造析构,重载赋值,拷贝构造函数






//-----这是派生类将默认成员函数显式的写出来的情况
//写出来就要考虑在什么情况下写出来才有意义?怎么写?什么情况下才需要自己写?


//class person
//{
//
//public:
//    string name;
//    size_t age;
//
//    person(string s1="zhangsan",int num=1)
//    :name(s1)
//    ,age(num)
//    {
//        cout<<"父类的构造函数被调用啦"<<endl;
//    }
//
//    ~person()
//    {
//        cout<<"父类的析构函数被调用啦"<<endl;
//    }
////
//    person(const person& x1)
//    :name(x1.name)
//    ,age(x1.age)
//    {
//        cout<<"父类的拷贝构造函数被调用啦"<<endl;
//    }
////
//    person& operator=(const person& p1)
//    {
//        cout<<"父类的operator=被调用啦"<<endl;
//    }
//};
//class student:public person
//{
//    //自己写构造函数怎么去调用父类成员构造函数?
//    //父类成员调父类对应的构造拷贝构造,operato=和析构处理
//    //自己的成员按需求处理(自己成员需要深拷贝或者浅拷贝)
//public:
//    student(const char* arr="zhangsan",int num=10086)
//    :person(arr,num)//想要在子类中初始化父类成员函数,就需要显式的写出父类的成员函数        ---里面的参数看父类的构造函数是怎么实现的
//    ,id(1000)
//    {}
//
//
//    student(const student& s)
//    :person(s)//会自动切片,自动的,切了就传给父类
//    ,id(s.id)
//    {}
//
//    student& operator=(const student& s1)
//    {
//        if(this!=&s1)
//        {
//            person::operator=(s1);//同样的道理会自动切片,但是想要调用父类的operator=和本身的函数重名了
//            //也就是说隐藏了
//            id=s1.id;
//        }
//        return *this;
//    }
//
//
//
//    ~student()//析构函数除非有开辟的空间需要销毁,否则默认这样就行
//    {
////        person::~person();//为什么要这样写?  因为析构函数在汇编中都会被同一的处理成 destructor(),构成了隐藏
//        //析构函数为什么会处理成一样,详细见多态的那个章节
//
//        //但是子类析构函数结束的时候,会自动的调用父类的析构函数
//        //先析构清理子类的成员,再去调用父类的析构清理继承的父类成员
//        //所以我们自己实现子类的析构函数中,不需要自己显式的调用父类析构函数
//        //这样才能保证先析构子类成员,再析构父类成员
//    }
//
//    size_t id;
//};
//
//int main(void)
//{
//    student s1("lisi",187);
//    student s2(s1);
//
//    student s3;
//    s3=s2;//赋值是已经存在的对象进行赋值
//    return 0;
//}

//总结:在什么情况下必须要自己写,不去使用默认的
// 在父类没有默认构造函数,需要我们自己显式的写构造
//如果子类有资源需要释放,就需要自己显式的写出来析构函数
//如果子类有存在浅拷贝问题,就需要自己实现拷贝构造和赋值













//四丶  继承和友元函数
//总结起来就一句话:友元关系不能继承.----也就是说基类的类里面有友元函数能够访问私有类或者保护类的成员,子类继承了之后,也会继承友元函数的声明.
//------但是子类中的友元函数不能访问子类中的私有成员或者保护成员
//class child;
//class person
//{
//public:
//    friend void my_print(const person& p1,const child& c1);
//private:
//    int _num=11;
//};
//
//void my_print(const person& p1,const child& c1)
//{
//    cout<<p1._num<<endl;
//    cout<<c1.num<<endl;
//}
//
//
//class child:public person
//{
//private:
//    int num=9;
//};
//
//int main(void)
//{
//    person p1;
//    child c1;
//    my_print(c1,p1);
//}
//也就是说父亲的友元函数虽然被子类继承,但是父类的友元函数不能访问子类的受保护成员












//五丶   继承和静态成员
//基类定义了static静态成员,则整个继承体系中只有一个这样的成员
//-----无论派生出多少个子类都只有一个static成员实例


//class person
//{
//public:
//    static int num;
//
//    person()
//    {
//        num++;
//    }
//};
//
//int person::num=10086;
//
//class child:public person
//{
//public:
//    child()
//    {
//        num++;
//    }
//
//};
//
//
//int main(void)
//{
//    person p1;
//    cout<<p1.num<<endl;
//
//    child c1;
//    cout<<c1.num<<endl;//不管是父类实例化还是子类实例化对象,   两个类第一次实例化的静态成员就是整个这两个类的实例化的对象的共享成员
//    //请记住,子类在使用构造函数的同时,会调用父类的构造函数
//}













//六丶  复杂的菱形继承和菱形虚拟继承

//1.单继承:一个子类只有一个直接父类时    -----称这个继承关系是单继承
//例如
//class T1
//{};
//
//class T2:public T1
//{};
//
//class T3:public T2
//{};
//上面的这些继承关系就叫做单继承




//2.多继承:一个子类有两个或者以上的直接父类时    ----这个继承关系叫做多继承
//class T1
//{};
//
//class T2
//{};
//
//class T3:public T2,public T1
//{};
//T3这个类的实现是继承了T1和T2两个类    所以上面的这些继承关系叫做多继承





//3.菱形继承:  -----菱形继承是多继承的一种特殊情况               ---所以尽量避免菱形继承这种情况,java直接没有多继承
//class person
//{
//public:
//    string _name;
//};
//
//class student:public person//-----学生类继承了父类
//{
//public:
//    size_t _id;//学号
//};
//
//class teacher:public person//----教师类继承了父类
//{
//public:
//    size_t _num;//职工号
//};
//
//class ST:public student,public teacher//这个ST类同时继承了父类和学生类     多继承
//{
//protected:
//    string _majorCourse;//主修课程
//};
////此时,这个ST类就会有两份person类成员        ---此时ST类存在数据冗余和二义性的问题
////这里就显示出来多继承的第一个问题
//
//
//int main(void)
//{
//    ST a;
//    a._id=10087;
//    a._num=10086;
//
//
////    a._name="zhangsan";
//    //此时的问题就出现了       ---想要访问ST中的_name,name有两个,此时的赋值不知道要将"zhangsan赋值给哪个"      ----其解决办法如下
//    a.student::_name="zhangsan";
//    a.teacher::_name="狗蛋";//这样就能看出来这个ST类中存在两个变量
//
//
//    //名字学号占用空间小还可以          ----但是如果person中存在一个   arr[999999]  也就是一个非常大的数组呢?    再这样菱形继承就会造成空间的浪费
//    下面的虚拟继承就解决了这个问题
//    return 0;
//}






//4.虚拟继承            ----这种继承方式就能解决数据冗余的问题
//class person
//{
//public:
//    string _name;
//};
//
//class student:virtual public person//虚拟继承的位置在这里
//{
//public:
//    size_t _id;//学号
//};
//
//class teacher:virtual public person//虚拟继承的位置在这里
//{
//public:
//    size_t _num;//职工号
//};
//
//class ST:public student,public teacher
//{
//protected:
//    string _majorCourse;//主修课程
//};
//
//int main(void)
//{
//    ST a;//使用了虚拟继承之后就像上面的arr[99999]就只能保存一个了
//    a._name="zhangsan";//现在就不用再使用::来访问name了
//    cout<<a._name<<endl;
//    a.student::_name="李四";
//    cout<<a._name<<endl;
//    a.teacher::_name="王五";//这两种访问的方式都是一样的
//    cout<<a._name<<endl;
//}


//其实只要有一个共同的祖宗类都算菱形继承 .但是在实际设计中,尽量不要使用这样的设计









