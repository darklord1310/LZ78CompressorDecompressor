#include "CustomAssertions.h"
#include "unity.h"

void assertFile(char *Source, char *Target,int lineNumber)
{
	long unsigned int srcFileSize, targetFileSize, position  ;
	unsigned int srcData,targetData ,srcfileStatus = 0,targetFileStatus = 0;
	char ErrorMsg[1024] ={};
	
	InStream *src = initInStream();
	InStream *target = initInStream();
	
	src = openInStream(Source, "rb" , src);
    target = openInStream(Target, "rb" , target);
	
	fseek(src->file,0,SEEK_END);
	fseek(target->file,0,SEEK_END);
	
	srcFileSize = ftell(src->file);
	targetFileSize = ftell(target->file);
	
	UNITY_TEST_ASSERT_EQUAL_UINT32(srcFileSize,targetFileSize,lineNumber,"The target file size does not match the source file size!");
	
	rewind(src->file);
	rewind(target->file);
	
	
	while(1)
	{
		srcData = streamReadBits(src,8);
		targetData = streamReadBits(target,8);
		
		srcfileStatus = checkEndOfFile(src)	;
		targetFileStatus = checkEndOfFile(target);
		
		if(srcfileStatus)
		{
			closeInStream(src);
			freeInStream(src);
		}
		if(targetFileStatus)
		{
			closeInStream(target);
			freeInStream(target);
		}
		
		UNITY_TEST_ASSERT_EQUAL_UINT8(srcfileStatus,targetFileStatus,lineNumber,"Target file ended earlier or later than the source file!");
		
		if (srcData != targetData)
		{
			position = ftell(target->file);
			sprintf(ErrorMsg,"At position 0x%x, target data does not match source data!",position); 
			UNITY_TEST_ASSERT_EQUAL_UINT8(srcData,targetData,lineNumber,ErrorMsg);
		}
		
		if(srcfileStatus == 1 || targetFileStatus == 1)
			break;
	}
}