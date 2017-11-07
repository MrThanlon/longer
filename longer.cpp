//定义
#include "longer.h"
//typedef std::vector<unsigned long> longer;
//typedef unsigned long sinlonger

//using std::vector;

//const unsigned long long full=18446744073709551615;//2^64-1
//const unsigned long long full=9999999999999999999;//10^19-1
const sinlonger fullBites=9;
const sinlonger full=pow(10,fullBites)-1;//10^9-1

void str2longer(string& stringIn,longer& longerIn)
{
	//清空longer
	auto longer_ptr=longerIn.begin();
	auto longerEnd_ptr=longerIn.end();
	while(longer_ptr!=longerEnd_ptr)
	{
		--longerEnd_ptr;
		longerIn.erase(longerEnd_ptr);
	}
	longerEnd_ptr=longerIn.end();
	if(stringIn.empty())//空串
		return;
	//处理头部字符串
	auto headLenth=stringIn.size()%8;//头部长度
	auto string_ptr=stringIn.begin();
	auto stringEnd_ptr=stringIn.end();
	string headString="";
	for(;headLenth>0;--headLenth)
	{
		headString.push_back(*string_ptr);
		++string_ptr;
	}
	//只有headString,优化速度
	sinlonger stringInParts=stringIn.size()/8;//除去头部
	auto totalParts=stringInParts;
	if(stringInParts==0)//没到8位,转完就返回了
	{
		longerIn.push_back(atoi(headString.data()));
		return;
	}
	//余部字符串输入新串singleString[],然后atoi转换
	string singleString[stringInParts];
	for(;stringInParts>0;--stringInParts)
	{
		char tempAssig=8;
		for(;tempAssig>0;--tempAssig)
		{
			singleString[stringInParts-1].push_back(*string_ptr);
			//字符串为最大到0,最大为首位,0为最低位,最大为totalParts-1
			++string_ptr;
		}
		//auto value_string=atoi(singleString[stringInParts-1].data());
		//longerIn.push_back(atoi(singleString[stringInParts].data()));
		string test=singleString[stringInParts-1];
	}
	//此时没有执行stringInParts=0的情况,需要补充执行
	//singleString[stringInParts].push_back(*string_ptr);
	//推入longer与转换方向相反,从0到最大
	for(;stringInParts<=totalParts-1;++stringInParts)
		longerIn.push_back(atoi(singleString[stringInParts].data()));
	//最后推入头部
	if(atoi(headString.data()))
     	longerIn.push_back(atoi(headString.data()));
    //判断b尾元素是否为0,为0则删除
    auto lEnd=longerIn.end();
    auto lBegin=longerIn.begin();
	--lEnd;
	while(lEnd!=lBegin)
    {
        if(*lEnd==0)
            longerIn.erase(lEnd);
        else
            break;
        --lEnd;
    }
    if(*lBegin==0)
        longerIn.erase(lBegin);
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
		while(rptr!=rEnd)//增长内层longer,长位参数+1位
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
    //每个位的乘法计算,存储mulResult内层
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
				if(full>=*aptr**bptr+mulFlag)//*aptr**bptr+mulFlag<=full
				{
					*inside_ptr=(*aptr)*(*bptr)+mulFlag;
					mulFlag=0;
				}
				else//溢出
				{
					//本位存储
					*inside_ptr=((*aptr)*(*bptr)+mulFlag)%(full+1);
					//下位存储增值
					mulFlag=(*aptr**bptr+mulFlag-*inside_ptr)/(full+1);
				}
				value_err=*inside_ptr;
				++inside_ptr;
				++aptr;
			}
			//处理未运算的mulFlag
            if(mulFlag!=0)
                *inside_ptr=mulFlag;
            mulFlag=0;
            value_err=*inside_ptr;
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
			++bptr;
            ++inside_ptr;
			}
			//处理未运算的mulFlag
            if(mulFlag!=0)
                *inside_ptr=mulFlag;
            mulFlag=0;
			++rptr;
			bptr=mulhb.begin();
			++aptr;
		}
	}
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
	//mulResult获取完成,塞入首元素(0)增位
	//原则是第n位mulResult塞入(n-1)个0
	rptr=mulResult.begin();//迭代器归位
	rEnd=mulResult.end();
	inside_ptr=(*rptr).begin();//内层迭代器归位
	rlenth=mulResult.size();
	--rlenth;//第一位不塞入
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
		add(*rptr,*(rptr+1));
		++rptr;
	}
	ass(*rEnd,mulhb);
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
	unsigned char LongerLenth=1;
	while(iEnd!=iptr)
	{
		--iEnd;
		LongerLenth=1;
		//std::cout<<*iEnd<<",";
		//对于小于10^8的数字在前面输出0,输出数量=9-位数
		sinlonger longerTry=10;
		for(;(*iEnd)>=longerTry;++LongerLenth)
		 	longerTry=10*longerTry;
		LongerLenth=9-LongerLenth;
		for(;LongerLenth>0;--LongerLenth)
			std::cout<<"0";
		std::cout<<*iEnd;
	}
}
