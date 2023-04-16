#pragma once
//���ͷ�ļ���Ϊ�˽��16_����Ŀ,��˵��ʲô��λͼ

#include<vector>
#include<iostream>
using namespace std;

template<size_t N>//������ģ�����
class bit_set
{
public:
	bit_set()
	{
		_bits.resize(N/8+1)//vector��resize���ٵĿռ���vector<>��ŵ����͵ĸ���   ��Զ�࿪һ��char���͵�Ԫ��
	}



	//���������������ĵĽӿ�
	void set(size_t x)//����Ӧ���ֵ��Ǹ�����λ�ĳ�1
	{
		//����ȥ����˻���С��,�������Ǵӵ�λ��ʼ��
		size_t i = x / 8;//���i������vector�ĵڼ���char��
		size_t j = x % 8;//���j�����ڵ�i��char��λ���ϵĵ�j������λ

		_bits[i] |= (1 << j);//��һ�����ǽ�jλ�õı���λ���1
	}

	void reset(size_t x)//��x��Ӧ�ı��Ϊ�ĳ�0
	{
		//~����а�λȡ��
		size_t i = x / 8;//���i������vector�ĵڼ���char��
		size_t j = x % 8;//���j�����ڵ�i��char��λ���ϵĵ�j������λ

		_bits[i] &= (~(1 << j));
	}

	bool test(size_t x)//���ǿ���x��Ӧ�ı��λ�治����
	{

	}
private:
	vector<char> _bits;//һ�βٿ�8λ
	//vector<int> _bits;//�������ž���һ�βٿ�32λ
};