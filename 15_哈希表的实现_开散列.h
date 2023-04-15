#pragma once
//��ɢ�е�ʵ�ַ�ʽͬ�����Խ����ݵ�ʵ�ַ�װ������һ�������ռ�
#include<iostream>
#include<vector>
using namespace std;







namespace LinkHash
{
	//-----------------------------------------------------����Ĳ�����ģ��
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







	//-----------------------------------------------------�����е�ÿ�����
	template<class K,class V>
	struct HashNode
	{
		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, next(nullptr)
		{}

		pair<K, V> _kv;
		HashNode<K,V>* _next = nullptr;
	};






	//----------------------------------------------------------��ɢ�еĹ�ϣ���ʵ��
	template<class K,class V,class HashFunc=Hash<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:
		//-----------------------------------------------------��������Ԫ���ǲ����Ѿ��ڱ��д���-------------
		Node* find(const K& key)
		{
			
		}




		//-----------------------------------------------------------------���ǴӲ�������-----------------------------------------
		//ps1:����ط������ʱ����Ȼʹ�õ��ǳ���������
		//ps2:��������������������Ȼ�ǹ�ϣ��ͻ,���ǿ�ɢ�еĽ���취�Ǻͱ�ɢ�в�һ����
		//ps3:�������������˳����������,�п��ܷǳ����Ԫ��ȫ������һ��������,�����Ľ���취����---���Ƹ�������,���Ƹ������Ӿ�����
		//ps4:��һ��Ͱ���ȳ���һ��ֵ�Ժ�,���ܻ�ת���ɺ����,����������Ϊ�˷�ֹһ��Ͱ���������(java��,һ��Ͱ�ĳ��ȳ���8֮��,�ͻ�ת���ɺ����),��ɺ�������������������Ԫ�ر�ɺ����,���ǳ��ȹ�������һ��Ͱ��ɺ����

		bool insert(const pair<K, V>& kv)
		{
			//����֮ǰ������Ҫ�Ƚ��м����û���Ѿ�����
			Node* ret=find(kv.first);
			if (ret)
				return false;
			if (_n==_tables.size())//�жϸ�����������������
			{
				size_t newsize = _tables.size() == 0 ? 10 : _tables.szie() * 2;
				//����ط����Ƽ�ʹ�����ַ�ʽ������������
				vector<Node*>newtables;
				newtables.resize(newsize)
			}
			HashFunc hf;
			size_t index = hf(kv.first) % _tables.size();
			Node* newnode = new  Node(kv);

			newnode->next = _tables[index];
			_tables[index] = newnode;
			++_n;

			return true;
		}

	private:
		////���⻹������һ���ṹ
		////�����������õ�������ʱ��Ϳ��ܲ�̫������
		//struct Data
		//{
		//	forward_list<T> _list;//�����ǰ��Ͱ�ĳ���û�г���ָ���ĳ��Ⱦͱ����ڵ�������
		//	set<T> _rbtree;//�����ǰ��Ͱ�ĳ��ȳ�����ָ���ĳ���,�ͻ�ת���ɺ����,����������,Ҳ���ǽ�����������е�Ԫ�ر���֮��,���뵽������������
		//	size_t _len;
		//};
	
		//vector<Data> _tables;
		
		//�򵥰汾�ľ��ǲ���������Ǹ��ṹ,����vector<Node*>
		vector<Node*> _tables;
		size_t _n=0;//��ŵ�ʵ�ʵ�Ԫ��
	};
}