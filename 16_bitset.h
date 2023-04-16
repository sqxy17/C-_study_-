#pragma once
//这个头文件是为了解决16_的题目,来说明什么是位图

#include<vector>
#include<iostream>
using namespace std;

template<size_t N>//非类型模板参数
class bit_set
{
public:
	bit_set()
	{
		_bits.resize(N/8+1)//vector的resize开辟的空间是vector<>存放的类型的个数   永远多开一个char类型的元素
	}



	//接下来是两个核心的接口
	void set(size_t x)//将对应数字的那个比特位改成1
	{
		//不用去理会大端还是小端,反正都是从低位开始的
		size_t i = x / 8;//这个i代表在vector的第几个char中
		size_t j = x % 8;//这个j代表在第i个char的位置上的第j个比特位

		_bits[i] |= (1 << j);//这一步就是将j位置的比特位变成1
	}

	void reset(size_t x)//将x对应的标价为改成0
	{
		//~这个叫按位取反
		size_t i = x / 8;//这个i代表在vector的第几个char中
		size_t j = x % 8;//这个j代表在第i个char的位置上的第j个比特位

		_bits[i] &= (~(1 << j));
	}

	bool test(size_t x)//就是看看x对应的标记位存不存在
	{

	}
private:
	vector<char> _bits;//一次操控8位
	//vector<int> _bits;//在这里存放就是一次操控32位
};