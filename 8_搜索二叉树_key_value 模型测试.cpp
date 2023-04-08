#include"8_搜索二叉树_key_value 模型.h"
using namespace key_value;
#include<string>


//首先:测试一个最简单的字典模型                    ---请注意区分,字典树是一个单独的数据结构,并不是这样的
void testBSTree1()
{
    //这是一个简单的 key_balue 模型
    BSTree<string,string> dict;        //dict:字典                    假设这个不是字典模型,而是身份证-车票模型,这个车票可以用 vector 容器来存放
    dict.insert("sort","排序");
    dict.insert("left","左边");
    dict.insert("right","右边");
    dict.insert("map","地图,映射");

    //简单的测试就是,输入英文,查找出对应的中文
    string str;
    while(cin>>str)
    {
        BSTreeNode<string,string>* ret=dict.Find(str);
        if(ret)
        {
            cout<<"对应中文的解释:"<<ret->_value<<endl;
        }
        else
        {
            cout<<"没有这个单词的翻译"<<endl;
        }
    }
}



//统计次数也是一个 key_value 的场景
void testBSTree2()//统计水果出现的次数,或者一个英文文章中每个单词出现的次数              -----这个例子就是一个相对抽象的 key/value 场景
{
    string arr[]={"苹果","西瓜","香蕉","苹果","香蕉","西瓜","橘子"};
    BSTree<string,int>countTree;//此处的 value 就是次数,string 就是水果的名称                 ,这个是建立成一颗搜索树,

    for(auto e:arr)
    {
        BSTreeNode<string,int>* p=countTree.Find(e);
        if(p)
        {
            p->_value++;
        }
        else//为空的情况下就是第一次见到这个水果
        {
            countTree.insert(e,1);
        }
    }

    countTree.Inorder();
}

//int main(void)
//{
//    testBSTree2();
//}
