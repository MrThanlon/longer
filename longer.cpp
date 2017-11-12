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
	//auto stringEnd_ptr=stringIn.end();
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
	auto aptr=assa.begin();
	auto aEnd=assa.end();
	assb.clear();//高速清除assb
	while(aptr!=aEnd)
	{
		assb.push_back(*aptr);
		++aptr;
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
	    //auto value_a=*aptr;
		//auto value_b=*bptr;
		//对ull进行相加,相加前判断是否溢出
		if(*aptr+*bptr+plusFlag<=full)//*aptr+*bptr+plusFlag<=full
		{
			*bptr=*bptr+*aptr+plusFlag;//不溢出,直接相加
			plusFlag=0;
		}
		else//溢出,加到下一位,*bptr=*aptr+*bptr-full
		{
			*bptr=*aptr+*bptr+plusFlag-full-1;//本元素的赋值
			//给下一位传递信号,让下1位+1
			plusFlag=1;
		}
		//auto value_plus=*bptr;
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

void sub(longer subb,longer &suba)
{
	//等同于b-a
//	auto aLenth=suba.size();
//	auto bLenth=subb.size();
	if(comp(suba,subb)==1)//a>b
		return;//直接返回
    if(comp(suba,subb)==0)//a=b
    {
        suba.clear();
        suba.push_back(0);
        return;
    }
	//b>=a,执行b-a
	auto aptr=suba.begin();
	auto aEnd=suba.end();
	auto bptr=subb.begin();
	auto bEnd=subb.end();
//	auto value_a=*aptr;
//	auto value_b=*bptr;
	//减法规则,总低位开始执行减法,若减数小于被减数则从高位取值
	sinlonger subFlag=0;//高位取值标记,0或1
	while(aptr!=aEnd)
	{
		if(*aptr<=(*bptr-subFlag))//(被减数-subFlag)大于等于减数,直接相减
		{
			*aptr=*bptr-*aptr;
			subFlag=0;
		}
		else//(减数-subFlag)小于被减数,从高位取值
		{
			*aptr=full+1-*aptr-subFlag+*bptr;
			subFlag=1;
		}
		++aptr;
		++bptr;
	}
	if(subFlag)//把subFlag减到0
    {
        suba.push_back(*bptr-1);
    	++bptr;
    }
    while(bptr!=bEnd)
    {
    	suba.push_back(*bptr);
    	++bptr;
    }
    if(*(suba.end()-1)==0)
        suba.erase(suba.end()-1);
}

void sub(longer subb,longer &suba,longer &subResult)
{
	//等同于b-a
//	auto aLenth=suba.size();
//	auto bLenth=subb.size();
	if(comp(suba,subb)==1)//a>b
		return;//直接返回
    if(comp(suba,subb)==0)//a=b
    {
        subResult.clear();
        subResult.push_back(0);
        return;
    }
	//b>=a,执行b-a
	auto aptr=suba.begin();
	auto aEnd=suba.end();
	auto bptr=subb.begin();
	auto bEnd=subb.end();
	subResult.clear();
//	auto subRptr=subResult.begin();
	//减法规则,总低位开始执行减法,若减数小于被减数则从高位取值
	sinlonger subFlag=0;//高位取值标记,0或1
	while(aptr!=aEnd)
	{
		if(*aptr+subFlag<=*bptr)//(被减数-subFlag)大于等于减数,直接相减
		{
			subResult.push_back(*bptr-*aptr);
			subFlag=0;
		}
		else//(减数-subFlag)小于被减数,从高位取值
		{
			subResult.push_back(full+1-*aptr-subFlag+*bptr);
			subFlag=1;
		}
		++aptr;
		++bptr;
	}
	if(subFlag)//把subFlag减到0
    {
        subResult.push_back(*bptr-1);
    	++bptr;
    }
    //因为a后面都是0,所以如果b没减完就全部推入subResult
    while(bptr!=bEnd)
    {
    	subResult.push_back(*bptr);
    	++bptr;
    }
    if(*(subResult.end()-1)==0)
        subResult.erase(subResult.end()-1);
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

inline void addForMulh(longer addFMa,longer &addFMb,sinlonger addLenth)
{
	//add函数变种,将两个参数错位叠加,结果保存到第二个参数
	//错位相加:第二个参数低位塞入addLenth个0,与第一个参数相加
	//clear之后再塞入,可以大幅加快速度
//	auto addFMaptr=addFMa.begin();
//	auto addFMaEnd=addFMa.end();
	longer addFMbCopy;//拷贝
	ass(addFMb,addFMbCopy);
	auto bCopy_ptr=addFMbCopy.begin();
	auto bCopyEnd=addFMbCopy.end();
	addFMb.clear();//清空
	//塞入0
	for(;addLenth>0;--addLenth)
		addFMb.push_back(0);
	//恢复拷贝
	while(bCopy_ptr!=bCopyEnd)
	{
		addFMb.push_back(*bCopy_ptr);
		++bCopy_ptr;
	}
	//加和
	add(addFMa,addFMb);
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
//	auto rlenth=mulResult.size();
	//mulResult中的longer增长
	auto rptr=mulResult.begin();
	auto rEnd=mulResult.end();
	if(aBiger==1)
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
	if(aBiger==1)//a比b长,a在上
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
				++inside_ptr;
				++aptr;
			}
			//处理未运算的mulFlag
            if(mulFlag!=0)
                *inside_ptr=mulFlag;
            mulFlag=0;
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
	//使用高性能方案,不调用insert,错位叠加(addForMulh)到结果
	rptr=mulResult.begin();//迭代器归位
	rEnd=mulResult.end();
	--rEnd;
	sinlonger resultAddLenth=1;
	while(rptr!=rEnd)
	{
		addForMulh(*rptr,*(rptr+1),resultAddLenth);
		++rptr;
		++resultAddLenth;
	}
	ass(*rEnd,mulhb);
}

void mulh(sinlonger mulha,longer &mulhb)
{
    //重载版,照抄上面,对a处理下优化即可
//    auto bLenth=mulhb.size();
	//结果位数一定小于bLenth+1
	vector<longer> mulResult;
	//存储每次下面的值与上面的值的乘积
	//mulResult中的longer增长
    //每个位的乘法计算,存储mulResult内层
	auto bptr=mulhb.begin();
	auto bEnd=mulhb.end();

	sinlonger mulFlag=0;//进位标记
			while(bptr!=bEnd)
			{
				if(full>=mulha**bptr+mulFlag)//mulha**bptr+mulFlag<=full
				{
					*bptr=mulha**bptr+mulFlag;
					mulFlag=0;
				}
				else//溢出
				{
					auto tempTotal=mulha**bptr+mulFlag;//总数
					//下位存储增值
					mulFlag=tempTotal/(full+1);
					//本位存储
					*bptr=tempTotal-(mulFlag*(full+1));
				}
			++bptr;
			}
			//处理未运算的mulFlag
            if(mulFlag!=0)
                mulhb.push_back(mulFlag);
            mulFlag=0;
	//清除mulhb末尾为0的元素
    if(*(mulhb.end()-1)==0)
        mulhb.erase(mulhb.end()-1);
}

inline void tempDivForDivl(
longer &TDFDa,longer &TDFDb,
sinlonger &TDFDmerchant,longer &TDFDremainder)
//低性能除法专用
{
	//等同于TDFDa/TDFDb
	//TDFDa比TDFDb长1位或者相等,这个函数用于计算他们的商和余数
	//结果写入sinlonger
	if(comp(TDFDa,TDFDb)<0)//不用想,写0
	{
		TDFDmerchant=0;
		ass(TDFDa,TDFDremainder);
		return;
	}
	if(comp(TDFDa,TDFDb)==0)//不用想,写1
	{
		TDFDmerchant=1;
		TDFDremainder.clear();
		TDFDremainder.push_back(0);
		return;
	}
	sinlonger tempDivdend=(*(TDFDa.end()-1)*(full+1)+*(TDFDa.end()-2));//临时被除数,两位
	sinlonger tempDivisor=0;
	if(TDFDa.size()==TDFDb.size())
        tempDivisor=(*(TDFDb.end()-1)*(full+1)+*(TDFDb.end()-2));//临时除数,两位
    else
        tempDivisor=(*(TDFDb.end()-1));//临时除数,一位
	TDFDmerchant=tempDivdend/tempDivisor;//初步计算
	//验证,精确计算,到TDFDbCopy刚好大于TDFDa,然后把TDFDmerchant减去1即可
	//为了高效不会每次都使用乘法,只在一开始使用乘法,然后用加法
	longer TDFDbCopy;
	ass(TDFDb,TDFDbCopy);//TDFDmerchant/=10;
    mulh(TDFDmerchant,TDFDbCopy);
	if(comp(TDFDbCopy,TDFDa)==0)//刚刚好,得整数
	{
		TDFDremainder.clear();
		TDFDremainder.push_back(0);
		return;
	}
	longer tempTDFDresult;
	if(comp(TDFDbCopy,TDFDa)==1)//大了
	{
		sub(TDFDbCopy,TDFDb,tempTDFDresult);
		--TDFDmerchant;//优化性能,反正都要判断一次
		for(;comp(tempTDFDresult,TDFDa)==1;--TDFDmerchant)
			sub(TDFDbCopy,TDFDb,tempTDFDresult);
		//++TDFDmerchant;//得到正确结果//刚好小于就是正确的
		sub(TDFDa,TDFDbCopy,TDFDremainder);//计算余数
		return;
	}
	//if(comp(TDFDbCopy,TDFDa)==-1)//小了
	//{//应该不需要判断了
		add(TDFDb,TDFDbCopy);
		++TDFDmerchant;
		for(;comp(TDFDbCopy,TDFDa)==-1;++TDFDmerchant)
			add(TDFDb,TDFDbCopy);
		--TDFDmerchant;//得到正确结果
		sub(TDFDbCopy,TDFDb,TDFDbCopy);
		sub(TDFDa,TDFDbCopy,TDFDremainder);//计算余数
	//}
}

void divl(longer divlDivdend,longer &divlDivisor,bool divlResultType)
{
	//模拟手工运算
	//resultType=0表示求商,1表示求模
	auto ldivdendLenth=divlDivdend.size();
	auto ldivisorLenth=divlDivisor.size();
	if(ldivdendLenth<ldivisorLenth)//除数大于被除数,0,返回
	{
		divlDivisor.clear();
		divlDivisor.push_back(0);
		return;
	}
	//高位指针(ldivdend_end)后推,后推次数为divisorLenth-1次
	auto ldivdend_ptr=divlDivdend.begin();
	auto ldivdend_end=divlDivdend.end();
	auto ldivisor_ptr =divlDivisor.begin();
//	auto ldivisor_end =divlDivisor.end();
	//调用乘法和比较函数,存入可能结果,确定后push_back
	sinlonger singleRemainder=0;//单次除法余数
	longer tempResult;//临时存储结果,高低位与最终结果相反
	longer longerRemainder;//余数,除数位数不是1的情况,长度与除数相同
	longer divlDivdendCopy;//临时被除数,完整版,比除数长1位
	sinlonger sinDivResult=0;//单次除法结果
	//执行除法运算,从高位(end)到低位(begin)
	if(ldivisorLenth==1)//除数只有1位就很简单
	{
		//按位除法
		while(ldivdend_end!=ldivdend_ptr)
		{
			--ldivdend_end;
			sinDivResult=((singleRemainder*(full+1)+*ldivdend_end)/(*ldivisor_ptr));
			tempResult.push_back(sinDivResult);
			//value3=
			singleRemainder=singleRemainder*(full+1)+*ldivdend_end-*ldivisor_ptr*sinDivResult;
		}
		auto tempRes_ptr=tempResult.begin();
		auto tempRes_end=tempResult.end();
		divlDivisor.clear();
		//结果赋值
		if(divlResultType)//求商
		{
			while(tempRes_ptr!=tempRes_end)
			{
				--tempRes_end;
				divlDivisor.push_back(*tempRes_end);
			}
			if(*(divlDivisor.end()-1)==0)//除去末尾的0
                divlDivisor.erase(divlDivisor.end()-1);
			return;
		}
		divlDivisor.push_back(singleRemainder);//求模
	}
	auto temp_ptr=ldivdend_end;
	for(;ldivisorLenth>1;--ldivisorLenth)
		--ldivdend_end;//被除数指针后推
	temp_ptr=ldivdend_end;//保留
	for(;ldivdend_end!=divlDivdend.end();++ldivdend_end)
		longerRemainder.push_back(*ldivdend_end);
	ldivdend_end=temp_ptr;//恢复
	auto longerRemainder_ptr=longerRemainder.begin();
	auto longerRemainder_end=longerRemainder.end();
	//tempDivisor=((*ldivisor_end)*(full+1)+*(ldivisor_end-1));
	while(ldivdend_end!=ldivdend_ptr)
	{
		//计算临时被除数,加入余数longerRemainder
		--ldivdend_end;
//		auto value1=*ldivdend_end;//debug
//		auto value2=*longerRemainder_ptr;
//		auto value3=longerRemainder.size();
//		auto value4=divlDivdendCopy.size();
		//生成完整的临时被除数
		divlDivdendCopy.clear();
		divlDivdendCopy.push_back(*ldivdend_end);//推入最低位
		longerRemainder_end=longerRemainder.end();//每次运算后可能改变
		longerRemainder_ptr=longerRemainder.begin();
		while(longerRemainder_ptr!=longerRemainder_end)
		{
			divlDivdendCopy.push_back(*longerRemainder_ptr);
			++longerRemainder_ptr;
		}
		//计算完整的临时被除数和除数的商和余数
		tempDivForDivl(divlDivdendCopy,divlDivisor,
		sinDivResult,longerRemainder);
		tempResult.push_back(sinDivResult);//推入结果
	}
	//输出结果
	if(divlResultType)//求商
	{
		//反向赋值tempResult到divlDivisor
		divlDivisor.clear();
		auto tempRes_ptr=tempResult.begin();
		auto tempRes_end=tempResult.end();
		while(tempRes_end!=tempRes_ptr)
		{
			--tempRes_end;
			divlDivisor.push_back(*tempRes_end);
		}
		return;
	}
	//输出余数
	ass(longerRemainder,divlDivisor);
}

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
