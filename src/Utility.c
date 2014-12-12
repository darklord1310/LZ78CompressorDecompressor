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

void renameCompressedFile(char *InfileName,char *CompressedfileName,int mode)
{
    char *dotPtr, *findSource ,*backSlash, *storage;

    strcpy(CompressedfileName,InfileName);
    
    findSource = strstr(CompressedfileName,"/Source/"); 
    if (findSource!= NULL)
    {
        backSlash = strrchr(CompressedfileName,'/'); // find last backslash '/'
        storage = calloc(strlen(backSlash)+1,sizeof(char));
        strcpy(storage,backSlash); //save a copy of string starting from last backslash
        
        if (mode == Fixed) //change from /Source/ to /Compressed/Fixed
            memmove(findSource,"/Compressed/Fixed",strlen("/Compressed/Fixed")+1);
        else //change from /Source/ to /Compressed/Variable
            memmove(findSource,"/Compressed/Variable",strlen("/Compressed/Variable")+1);
            
        strcat(CompressedfileName,storage);
        free(storage);
    }
    
    dotPtr = strrchr(CompressedfileName,'.'); //find last dot '.'
    if (dotPtr != NULL)
        memmove(dotPtr,".LZ",strlen(dotPtr)+1); //change the file format to .LZ
    else
        strcat(CompressedfileName,".LZ"); //make the file format to .LZ
        
}

