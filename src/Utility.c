#include "Utility.h"
#include <string.h>
#include "malloc.h"

int determineNumberOfBitsRequired(int index)
{
    int bitTest, i ,result = 0;
    
    if (index == 0 )
        return 1;
    
    for ( i = 0 ; i < (sizeof(int) * 8) ; i ++)
    {
        bitTest = index & ( 1 << i ) ;
        
        if (bitTest != 0 )
            result = i;
    }
    
    return (result + 1);
}

void renameCompressedFile(char *InfileName,char *CompressedfileName)
{
    int dotPtrLength;
    char *dotPtr ;

    strcpy(CompressedfileName,InfileName);
    dotPtr = strrchr(CompressedfileName,'.');
    if (dotPtr != NULL)
    {
        dotPtrLength = strlen(dotPtr);
        memmove(dotPtr,".LZ",dotPtrLength+1);
    }
    else
        strcat(CompressedfileName,".LZ");
}