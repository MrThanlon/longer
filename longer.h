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
#include <string>
#include <cstdlib>
#include <math.h>

typedef unsigned long long sinlonger;
typedef std::vector<sinlonger> longer;

using std::vector;
using std::string;

//声明

void str2longer(string&,longer&);
/*字符串转longer函数,理论支持长度为2^61的十进制数,
不要输入字母,否则引发错误.
调用此函数一定会清空longer,无论是有否输入.*/

void ass(longer&,longer&);
/*ass函数赋值,接收longer,
将第一个参数的值赋予给第二个参数*/

void add(longer,longer&);
/*Add函数求和,接收longer,
求和后的结果保存在第二个参数中,
把大的数放在后面可以提高性能.*/

void sub(longer,longer&);//结果写入第二个参数
void sub(longer,longer&,longer&);//结果写入第三个参数
/*Sub函数求差,接收longer的,第一个参数减去第二个参数
求差后的结果保存在第二个参数的中,
第一个参数必须大于第二个参数,
否则不执行任何动作*/

char comp(longer&,longer&);
/*Come函数用于比较longer的大小,
若前者大于后者则返回1,反之返回-1,相等返回0*/

void mulh(longer,longer&);//高性能版乘法(alpha)
void mulh(sinlonger,longer&);//重载,可以用sinlonger乘了
//void mulh(sinlonger,longer&);//重载
/*mul函数求积,接收longer,
求积后的结果保存在第二个参数中.*/

//void mod(longer&,longer&);
/*mod函数求模,接收longer,
第一个参数模第二个参数,
求模后的结果保存在第二个参数中.*/
void tempDivForDivl(longer&,longer&,sinlonger&,sinlonger&);

void divl(longer,longer&,bool);//低性能版,临时用
/*div函数求商,接收longer,bool,bool=1求商,0求模
等同于第一个参数除以第二个参数,
求商或者求模后的结果保存在第二个参数中.*/

void mulhForDivl(sinlonger,longer&);//divl专用,请勿擅自使用

//void squ(longer&,longer&);
/*squ函数求幂,接收longer,
表示第二个参数的第一个参数次方,
求幂后的结果保存在第二个参数中,*/

void lcout(longer);
/*lcout函数输出,接收一个longer,
使用ctd::cout,所以自动包含#include<iostream>.*/

void addForMulh(longer,longer&,sinlonger);//乘法mulh专用函数
