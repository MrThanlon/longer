/*
©HuangZY
这个库定义了一系列方法,可以将
std::vector<unsigned long long>
作为一个整数使用,支持加减乘除求模,
因为longer的原型是
std::vector<unsigned long long>
所以如果使用指针,解引用会引发错误,请注意.

longer声明并初始化:

longer赋值使用ass函数,右值在前,必须也是longer.
*/
#include <vector>
#include <iostream>
#define ull unsigned long long

typedef std::vector<unsigned long long> longer;

using std::vector;

//声明
void longerInit(ull,longer&);
void longerInit(ull,ull,longer&);
void longerInit(ull,ull,ull,longer&);
void longerInit(ull,ull,ull,ull,longer&);
void longerInit(ull,ull,ull,ull,ull,longer&);//临时用
/*赋初值,将ull的值放入新建立的longer,
如果不是会清楚除了首位以外所以的元素,
ull要小于10^19-1,
*/


void ass(longer&,longer&);
/*ass函数赋值,接收两个longer的引用,
将第一个参数的值赋予给第二个参数*/

void add(longer&,longer&);
/*Add函数求和,接收两个longer的引用,
求和后的结果保存在第二个参数中,
把大的数放在后面可以提高性能.*/

void sub(longer&,longer&);
/*Sub函数求差,接收两个longer的引用,
求差后的结果保存在第二个参数的中,
第一个参数必须大于第二个参数,
否则将引发不可预知的错误.*/

char comp(longer&,longer&);
/*Come函数用于比较两个longer的大小,
若前者大于后者则返回1,反之返回-1,相等返回0*/

void mulh(longer&,longer&);//高性能版乘法(测试)
/*mul函数求积,接收两个longer的引用,
求积后的结果保存在第二个参数中.*/

void mull(longer&,longer&);//低性能版乘法,基于加法

//void mod(longer&,longer&);
/*mod函数求模,接收两个longer的引用,
第一个参数模第二个参数,
求模后的结果保存在第二个参数中.*/

//void div(longer&,longer&);
/*div函数求商,接收两个longer的引用,
求商后的结果保存在第二个参数中.*/

//void squ(longer&,longer&);
/*squ函数求幂,接收两个longer的引用,
表示第二个参数的第一个参数次方,
求幂后的结果保存在第二个参数中,*/

void lcout(longer&);
/*lcout函数输出,接收一个longer的引用,
使用ctd::cout,所以自动包含#include<iostream>.*/