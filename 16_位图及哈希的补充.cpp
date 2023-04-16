#define _CRT_SECURE_NO_WARNINGS 1
//一丶 用一个题目来进行讲解什么是位图
//1.给定40亿个不重复的无符号整数,没有排过序,给定一个无符号整数(size_tj8个字节),如何判断一个数是否在这40亿个数中.             这个数字最大是42亿九千万,
//ps1:不管用什么方式查找,首先存储是一个大问题,因为这么多整数,一个按照4个字节都要几个G
//ps2:所以我们可以开足以存放最大数字的个比特位
//ps3:思想是这样的,整数1存在,将申请的第一个比特位置为1,数字10086存在,将申请的第10086个比特位置为1...........也就是说只要申请42亿九千万(8字节最大数字)个比特位,就能保存所有数字

#include"16_bitset.h"

int main(void)
{
	bit_set<100>bs;
	bs.set(5);
	bs.set(4);
	bs.set(10);
}