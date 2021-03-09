# include <stdio.h>
int func1()
{
	int eFishNum;
	int aFishNum, bFishNum, cFishNum, dFishNum; //the number of fish that each one left
	int totalNum;
	
	for(eFishNum = 4;;eFishNum+=4)
	{
		int i = 0;
		totalNum = eFishNum;
		
		for(i;i<5;i++)
		{
			if(totalNum%4 != 0)
				break;
			totalNum = 5*totalNum/4+1;
		
		}
		if(i == 5)
			break;
		
	}
 
	aFishNum = (totalNum-1)/5*4;
	bFishNum = (aFishNum-1)/5*4;
	cFishNum = (bFishNum-1)/5*4;
	dFishNum = (cFishNum-1)/5*4;
	eFishNum = (dFishNum-1)/5*4;

	printf("totalNum = %d\n",totalNum);
	printf("aFishNum = %d\n",aFishNum);
	printf("bFishNum = %d\n",bFishNum);
	printf("cFishNum = %d\n",cFishNum);
	printf("dFishNum = %d\n",dFishNum);
	printf("eFishNum = %d\n",eFishNum);
	
}

