//定义

typedef std::vector<unsigned long long> longer;

using std::vector;

//const unsigned long long full=18446744073709551615;//2^64-1
const unsigned long long full=9999999999999999999;//10^19-1

void longerInit(ull ull1,longer &loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
	loptr=loNumber.begin();
	loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.push_back(ull1);
	}
}

void longerInit(ull ull1,ull ull2,longer&loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
	loptr=loNumber.begin();
	loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.push_back(ull1);
		loNumber.push_back(ull2);
	}
}

void longerInit(ull ull1,ull ull2,ull ull3,longer&loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
	loptr=loNumber.begin();
	loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.push_back(ull1);
		loNumber.push_back(ull2);
		loNumber.push_back(ull3);
	}
}
void longerInit(ull ull1,ull ull2,ull ull3,ull ull4,longer&loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
	loptr=loNumber.begin();
	loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.push_back(ull1);
		loNumber.push_back(ull2);
		loNumber.push_back(ull3);
		loNumber.push_back(ull4);
	}
}
void longerInit(ull ull1,ull ull2,ull ull3,ull ull4,ull ull5,longer&loNumber)
{
	auto loptr=loNumber.begin();
	auto loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.erase(loptr);
		++loptr;
	}
	loptr=loNumber.begin();
	loEnd=loNumber.end();
	while(loptr!=loEnd)
	{
		loNumber.push_back(ull1);
		loNumber.push_back(ull2);
		loNumber.push_back(ull3);
		loNumber.push_back(ull4);
		loNumber.push_back(ull5);
	}
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

	unsigned long long plusFlag=0;//+1信号传递
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
	unsigned long long subFlag=0;//高位取值标记,0或1
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
/*
void mulh(longer &mulha,longer &mulhb)
{
	//定理:n位数与m位数的积一定小于(n+m)位
	auto aLenth=mulha.size();
	auto bLenth=mmulhb.size();
	//结果位数一定小于aLenth+bLenth
	//所以先直接b.push_back,aLenth次
	int i=1;
	for(;i<=aLenth;++i)
	{
		mmulhb.push_back(0);
	}
	bLenth=aLenth+i-1;
	auto aptr=mulha.begin();
	auto aEnd=mulha.end();
	auto bptr=mmulhb.begin();
	auto bEnd=mmulhb.end();
	unsigned long long mulFlag=0;//进位标记
	if(aLenth>=bLenth-aLenth)//a比b长,a在上
	{
		while(bptr!=bEnd)
		{
			while(aptr!=aEnd)
			{
				if((full-mulFlag)>=*aptr**bptr)//*aptr**bptr+mulFlag<=full
				{
					*bptr=*aptr**bptr+mulFlag;
					mulFlag=0;
				}
				else//溢出
				{
					auto temp=*bptr;
					*bptr=*aptr**bptr+mulFlag;
					mulFlag=(*aptr**bptr+mulFlag-temp)/(full+1);
					//两个元素的积不会大于2位ull
					//在本位存储
				}
				++aptr;
			}
			++bptr;
		}

	}
	else//相反
	{
		while(aptr!=aEnd)
		{
			while(bptr!=bEnd)
			{
				if((full-mulFlag)>=*aptr**bptr)//*aptr**bptr+mulFlag<=full
				{
					*bptr=*aptr**bptr+mulFlag;
					mulFlag=0;
				}
				else//溢出
				{
					auto temp=*bptr;
					*bptr=*aptr**bptr+mulFlag;
					mulFlag=(*aptr**bptr+mulFlag-temp)/(full+1);
					//两个元素的积不会大于2位ull
					//在本位存储
				}
				++bptr;
			}
			++aptr;
		}
	}
}*/

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

void lcout(longer&inLonger)
{
	auto iptr=inLonger.begin();
	auto iEnd=inLonger.end();
	//--iEnd;
	//std::cout<<;
	while(iEnd!=iptr)
	{
		--iEnd;
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