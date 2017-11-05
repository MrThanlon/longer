//定义
#include "longer.h"
//typedef std::vector<unsigned long> longer;
//typedef unsigned long sinlonger

//using std::vector;

//const unsigned long long full=18446744073709551615;//2^64-1
//const unsigned long long full=9999999999999999999;//10^19-1
const sinlonger full=99999999;//10^9-1
1000000000
void longerInit(sinlonger ull1,longer &loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
    loNumber.push_back(ull1);
}

void ass(longer &assa,longer &assb)
{
	auto aLenth=assa.size();
	auto bLenth=assb.size();
	auto aptr=assa.begin();
	auto aEnd=assa.end();
	auto bptr=assb.begin();
	auto bEnd=assb.end();
	if(aLenth<=bLenth)//b可以容纳a
	{
		while(aptr!=aEnd)
		{
			*bptr=*aptr;//赋值
			++bptr;//指针+1
			++aptr;
		}
		//删除b末尾元素
		while(aLenth!=bLenth)
		{
			assb.erase(--assb.end());//删除尾元素
			--bLenth;
		}
	}
	else//b无法容纳a,使用b.push_back(*aptr)
	{
		while(bptr!=bEnd)
		{
			*bptr=*aptr;//赋值
			++bptr;//指针+1
			++aptr;
		}
		while(aptr!=aEnd)
		{
			assb.push_back(*aptr);
			++aptr;
		}
	}
}

void add(longer adda,longer &addb)
{
	/*两个二进制n位数相加,
	和一定小于最小的n+1位的二进制数,
	所以直接先对长位vector增一个元素,
	用不到再删掉.*/
	auto aLenth=adda.size();
	auto bLenth=addb.size();
	while(aLenth>bLenth)//若a比b长,先对b增位,
	{
		addb.push_back(0);
		bLenth=addb.size();
	}
	addb.push_back(0);//再增1位
	bLenth=addb.size();
	auto aptr=adda.begin();
	auto aEnd=adda.end();
	auto bptr=addb.begin();
	auto bEnd=addb.end();

	sinlonger plusFlag=0;//+1信号传递
	while(aptr!=aEnd)//对a执行加到b动作
	{
		//对ull进行相加,相加前判断是否溢出
		if(full-plusFlag-*aptr>=*bptr)//*aptr+*bptr+plusFlag<=full
		{
			*bptr=*bptr+*aptr;//不溢出,直接相加
			plusFlag=0;
		}
		else//溢出,加到下一位,*bptr=*aptr+*bptr-full
		{
			*bptr=*aptr+*bptr+plusFlag-full-1;//本元素的赋值
			//给下一位传递信号,让下1位+1
			plusFlag=1;
		}
		++aptr;
		++bptr;
	}
	while(plusFlag)//计算至没有+1信号
	{
	    if(*bptr+plusFlag==full+1)
        {
            plusFlag=1;
            *bptr=0;
		}
        else
        {
            ++*bptr;
            plusFlag=0;
        }
        ++bptr;
	}
	//判断b尾元素是否为0,为0则删除
	bEnd=addb.end();
	--bEnd;
	if(*bEnd==0)
		addb.erase(bEnd);
}

void sub(longer suba,longer &subb)
{
	auto aLenth=suba.size();
	auto bLenth=subb.size();
	if(aLenth>bLenth)//显然a>b
		return;//直接返回
	//b>=a,执行b-a
	auto aptr=suba.begin();
	auto aEnd=suba.end();
	auto bptr=subb.begin();
	auto bEnd=subb.end();
	//减法规则,总低位开始执行减法,若减数小于被减数则从高位取值
	sinlonger subFlag=0;//高位取值标记,0或1
	while(aptr!=aEnd)
	{
		if(*aptr<=(*bptr-subFlag))//(减数-subFlag)大于等于被减数,直接相减
		{
			*bptr=*bptr-*aptr;
			subFlag=0;
		}
		else//(减数-subFlag)小于被减数,从高位取值
		{
			*bptr=full-*aptr+*bptr;
			subFlag=1;
		}
		++aptr;
		++bptr;
	}
	//判断b尾元素是否为0,为0则删除
	--bEnd;
	if(*bEnd==0)
		subb.erase(bEnd);
}

char comp(longer &compa,longer &compb)
{
	auto aLenth=compa.size();
	auto bLenth=compb.size();
	if(aLenth>bLenth)//a>b
		return 1;
	if(aLenth<bLenth)//a<b
		return -1;
	//aLenth=bLenth
	auto aptr=compa.begin();
	auto aEnd=compa.end();
	auto bptr=compb.begin();
	auto bEnd=compb.end();
	while(aEnd!=aptr)//从最高位判断到最低位
	{
		--aEnd;--bEnd;//指针-1
		if(*aEnd>*bEnd)
			return 1;
		if(*aEnd<*bEnd)
			return -1;
	}
	if(*aptr>*bptr)
		return 1;
	if(*aptr<*bptr)
		return -1;
	return 0;//a=b
}

void mulh(longer mulha,longer &mulhb)
{
	//定理:n位数与m位数的积一定小于(n+m)位
	auto aLenth=mulha.size();
	auto bLenth=mulhb.size();
	//结果位数一定小于aLenth+bLenth
	vector<longer> mulResult;
	//存储每次下面的值与上面的值的乘积
	bool aBiger=0;//a更大标记
	if(aLenth>=bLenth)//a比b长,a在上
	{
		mulResult.resize(bLenth);
		aBiger=1;
	}
	else//b比a长,b在上
	{
		mulResult.resize(aLenth);
		aBiger=0;
	}
	auto rlenth=mulResult.size();
	//mulResult中的longer增长
	auto rptr=mulResult.begin();
	auto rEnd=mulResult.end();
	if(aBiger=1)
	{
		while(rptr!=rEnd)//增长每个longer,长位参数+1位
		{
			(*rptr).resize(aLenth+1);
			++rptr;
		}
	}
	else
	{
		while(rptr!=rEnd)//增长每个longer,长位参数+1位
		{
			(*rptr).resize(bLenth+1);
			++rptr;
		}
	}
    //单位乘法计算,存储mulResult内层
	auto aptr=mulha.begin();
	auto aEnd=mulha.end();
	auto bptr=mulhb.begin();
	auto bEnd=mulhb.end();

	rptr=mulResult.begin();//mulResult外层迭代器
	rEnd=mulResult.end();
	auto inside_ptr=(*rptr).begin();//mulResult内层迭代器
	auto insideEnd_ptr=(*rptr).end();

	unsigned long mulFlag=0;//进位标记
	if(aBiger=1)//a比b长,a在上
	{
		while(bptr!=bEnd)
		{
			inside_ptr=(*rptr).begin();
			while(aptr!=aEnd)
			{
				auto value_c=*aptr**bptr+mulFlag;
				if(full>=*aptr**bptr+mulFlag)//*aptr**bptr+mulFlag<=full
				{
					*inside_ptr=(*aptr)*(*bptr)+mulFlag;
					mulFlag=0;
				}
				else//超过
				{
					//本位存储
					*inside_ptr=((*aptr)*(*bptr)+mulFlag)%(full+1);
					//下位存储增值
					mulFlag=(*aptr**bptr+mulFlag-*inside_ptr)/(full+1);
				}
				++inside_ptr;
				++aptr;
			}
			++rptr;
			aptr=mulha.begin();//aptr归位
			++bptr;
		}

	}
	else//b比a长,b在上
	{
		while(aptr!=aEnd)
		{
			inside_ptr=(*rptr).begin();
			while(bptr!=bEnd)
			{
				if(full>=*aptr**bptr+mulFlag)//*aptr**bptr+mulFlag<=full
				{
					*inside_ptr=*aptr**bptr+mulFlag;
					mulFlag=0;
				}
				else//溢出
				{
					//下位存储增值
					mulFlag=(*aptr**bptr+mulFlag)/(full+1);
					//本位存储
					*inside_ptr=*aptr**bptr-(mulFlag*(full+1));
				}
				++inside_ptr;
				++bptr;
			}
			++rptr;
			bptr=mulhb.begin();
			++aptr;
		}
	}
	if(mulFlag!=0)
    {
        if(inside_ptr!=insideEnd_ptr)
            *inside_ptr=mulFlag;
        else
            (*rptr).push_back(mulFlag);
    }
	//auto value2=*(*mulResult.begin()).begin();
	//清除mulResult内层末尾为0的元素
	rptr=mulResult.begin();//迭代器归位
	inside_ptr=(*rptr).begin();//内层迭代器归位
	insideEnd_ptr=(*rptr).end();
	while(rptr!=rEnd)
	{
		while(inside_ptr!=insideEnd_ptr)
		{
			--insideEnd_ptr;
			if(*insideEnd_ptr==0)
			{
				(*rptr).erase(insideEnd_ptr);
			}
			else
				break;
		}
		++rptr;
		inside_ptr=(*rptr).begin();
		insideEnd_ptr=(*rptr).end();
	}
	//auto value=*(*mulResult.begin()).begin();
	//mulResult获取完成,塞入首元素(0)增位
	//原则是第n位mulResult塞入(n-1)个0
	rptr=mulResult.begin();//迭代器归位
	rEnd=mulResult.end();
	inside_ptr=(*rptr).begin();//内层迭代器归位
	rlenth=mulResult.size();
	--rlenth;
	for(;rlenth>0;--rlenth)
	{
		--rEnd;
		auto temp_times=rlenth;
		for(;temp_times>0;--temp_times)
		{
			(*rEnd).insert((*rEnd).begin(),0);
		}
	}
	//调用add加和每个(*rptr加和)
	rptr=mulResult.begin();
	rEnd=mulResult.end();
	--rEnd;
	while(rptr!=rEnd)
	{
		add(*rptr,*(++rptr));
		//++rptr;
	}
	ass(*rEnd,mulhb);
}



void mull(longer mulla,longer &mullb)
{
	longer mullbBackup;
	ass(mullb,mullbBackup);
	longer iTimes;
	longerInit(1,iTimes);
	longer dChange;
	longerInit(1,dChange);
	for(;comp(mulla,iTimes);add(dChange,iTimes))
	{
		add(mullb,mullbBackup);
		//lcout(mullbBackup);
		//std::cout<<" ";
	}
	ass(mullbBackup,mullb);
}

/*
void div(longer a,longer b)
{

}
*/

void lcout(longer inLonger)
{
	auto iptr=inLonger.begin();
	auto iEnd=inLonger.end();
	--iEnd;
	std::cout<<*iEnd;
	//--iEnd;
	unsigned char LongerLenth=0;
	while(iEnd!=iptr)
	{
		--iEnd;
		//std::cout<<*iEnd<<",";
		//对于小于10^8的数字在前面输出0,输出数量=9-位数
		for(;(*iEnd)/10>0;(*iEnd)/=10)
            ++LongerLenth;
        //++LongerLenth;
        for(;8-LongerLenth>0;++LongerLenth)
            std::cout<<"0";
		std::cout<<*iEnd;
	}
}
/*
void lcout(longer&inLonger)
{
	//从高位输出到低位
	//原数字是18446744073709551616进制,需要转换输出
	//1,0=18446744073709551616=1*18446744073709551616+0
	//1,1,1=1*2^128+1*2^64+1*2^0
	auto iLenth=inLonger.size()
	if(iLenth<=1)
	{
		std::cout<<*inLonger.begin();
		return;
	}
	auto iptr=inLonger.begin();
	auto iEnd=inLonger.end();
	//导出每个数字
	unsigned char assNumber=0;
	unsigned char singleNumber[iLenth][20];//导出数字,第一个是元素数,第二个是每个数
	//备份
	longer inLongerBackup;
	ass(inLonger,inLongerBackup);
	auto ibptr=inLongerBackup.begin();
	auto ibEnd=inLongerBackup.end();

	iLenth=0;

	while(ibptr!=ibEnd)
	{
		for(;assNumber<20;++assNumber)
		{
			singleNumber[iLenth][assNumber]=*ibptr%10;
			*ibptr/=10;
		}
		++ibptr;
		++iLenth;
	}
	//18446744073709551616进制,20个10进制
	//1,1553255926290448384=2e19
	//原数字是18446744073709551616进制,需要转换输出
	//1,0=18446744073709551616=1*18446744073709551616+0
	//1,1,1=1*2^128+1*2^64+1*2^0
	std::vector<unsigned> outNumber(1,0);//0-4294967295
	//每个元素存放10位数
	//不够的时候push_back
	auto optr=outNumber.begin();
	auto oEnd=outNumber.end();
	iLenth=0;

	//未完成
	while(iptr!=iEnd)//遍历每个元素进行处理
	{
		//遍历这个元素的20个数字
		for(assNumber=0;assNumber<20;++assNumber)//0-19
		{
			//合成:
			singleNumber[iLenth][assNumber]
		}
	}
	//最终输出,反向
	oEnd=outNumber.end();
	optr=outNumber.begin()
	for(;optr!=oEnd;--oEnd)
	{
		std::cout<<*oEnd;
	}
}*/
