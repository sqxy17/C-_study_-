#pragma once
//开散列的实现方式同样可以将内容的实现封装在另外一个命名空间
#include<iostream>
#include<vector>
using namespace std;








	//-----------------------------------------------------输入的参数的模板
	template<class K>
	struct Hash
	{
		size_t operator()(const K& key)
		{
			return key;
		}
	};


	template<>
	struct Hash<string>
	{

		size_t operator()(const string& s)
		{
			size_t value = 0;
			for (auto ch : s)
			{
				value *= 31;
				value += ch;
			}
			return value;
		}
	};







	//-----------------------------------------------------数组中的每个结点
	template<class K, class V>
	struct HashNode
	{
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}

		pair<K, V> _kv;
		HashNode<K, V>* _next = nullptr;
	};






	//----------------------------------------------------------开散列的哈希表的实现
	template<class K, class V, class HashFunc = Hash<K>>
	class HashTable
	{

	public:
		typedef HashNode<K, V> Node;


		//-----------------------------------------------------检查带插入元素是不是已经在表中存在-------------
		Node* find(const K& key)//遍历那个桶就行
		{
			HashFunc hf;
			if (_tables.size() == 0)
			{
				return nullptr;
			}
			else
			{
				size_t index = hf(key) % _tables.size();
				Node* cur = _tables[index];
				while (cur)
				{
					if (cur->_kv.first == key)
					{
						return cur;//后续就是返回的迭代器
					}
					else
					{
						cur = cur->_next;
					}
				}
			}

			return nullptr;
		}




		//-----------------------------------------------------------------还是从插入入手-----------------------------------------
		//ps1:这个地方插入的时候依然使用的是除留余数法
		//ps2:除留余数法最大的问题依然是哈希冲突,但是开散列的解决办法是和闭散列不一样的
		//ps3:但是在遇见极端场景的情况下,有可能非常多的元素全部都在一个链表上,这样的解决办法还是---控制负载因子,控制负载因子就扩容
		//ps4:当一个桶长度超过一定值以后,可能会转换成红黑树,这样做就是为了防止一个桶的链表过长(java中,一个桶的长度超过8之后,就会转换成红黑树),变成红黑树并不是整个插入的元素变成红黑树,而是长度过长的那一个桶变成红黑树

		bool insert(const pair<K, V>& kv)
		{
			//插入之前还是需要先进行检查有没有已经存在
			Node* ret = find(kv.first);
			if (ret)
			{
				return false;
			}

			if (_n == _tables.size())//判断负载因子来进行扩容
			{
				size_t newsize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				//这个地方就推荐使用这种方式来进行扩容了
				vector<Node*>newtables;
				newtables.resize(newsize);
				HashFunc hf;
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];//因为这个表是指针数组,里面存放的都是一个个的链表,没有存放的就是nullptr
					while (cur)
					{
						Node* next = cur->_next;//记录一下当前结点的下一个结点
						size_t index = hf(cur->_kv.first) % newtables.size();//当前结点的键模上新的数组

						newtables[index] = cur;
						cur->_next = newtables[index];

						cur = next;
					}
					_tables[i] = nullptr;
				}
				_tables.swap(newtables);//vector交换的代价是极低的
			}

			//正常的插入过程
			HashFunc hf;
			size_t index = hf(kv.first) % _tables.size();
			Node* newnode = new  Node(kv);

			newnode->_next = _tables[index];
			_tables[index] = newnode;
			++_n;

			return true;
		}

	private:
		////此外还能设置一个结构
		////但是这样设置迭代器的时候就可能不太方便了
		//struct Data
		//{
		//	forward_list<T> _list;//如果当前的桶的长度没有超过指定的长度就保存在单链表中
		//	set<T> _rbtree;//如果当前的桶的长度超过了指定的长度,就会转化成红黑树,保存在这里,也就是将上面的链表中的元素遍历之后,插入到这个红黑树当中
		//	size_t _len;
		//};

		//vector<Data> _tables;

		//简单版本的就是不用上面的那个结构,而是vector<Node*>
		vector<Node*> _tables;
		size_t _n = 0;//存放的实际的元素

	};