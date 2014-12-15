#include "Utility.h"
#include <string.h>
#include "malloc.h"
#include "Stream.h"

/*  Determine Number of Bits Required to be written
 *
 *  Input : value          	: value is the index to be written
 *			dictionaryIndex	: dictionaryIndex is the current index of the dictionary
 *
 *	Output : return number of bits required
 */ 
int determineNumberOfBitsRequired(int value,int dictionaryIndex)
{
    int count = 0;
    
    if (value > dictionaryIndex)
        dictionaryIndex = value ;
    
    if (dictionaryIndex == 0 )
        return 1;
    
    while (dictionaryIndex!= 0) 
    {
        count++;
        dictionaryIndex = dictionaryIndex >> 1;
    }
    return count;
}

/*  Rename compressedFile to .LZ and place them to correct directry
 *
 *  Input : InfileName          : InfileName is the input file name
 *			CompressedfileName	: CompressedfileName is used to store the CompressedfileName
 *			mode				: Fixed will store the compressed file into test/support/Compressed/Fixed
 *								  Variable will store the compressed file into test/support/Compressed/Variable
 *
 */ 
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


/*      This function is used to determine the file size of 
 *      two input files
 *
 *      Inputs:
 *                  infilename1   the filename for input file 1
 *                  infilename2   the filename for input file 2
 *
 *      Return:
 *                  1   if the two files have the same size
 *                  0   if the two files have a different size
 */
int verifyDecompressedFile(char *infilename1, char *infilename2)
{
    unsigned int value1, value2;
    int counter1 = -1, counter2 = -1;
    InStream *in1, *in2;
    
    in1 = initInStream();                                              
    in2 = initInStream();                                              
    
    in1 = openInStream(infilename1, "rb+" , in1);                         
    in2 = openInStream(infilename2, "rb+" , in2);                      
    
    do
    {
        value1 = streamReadBits(in1, 8);
        counter1++;
    }while(!checkEndOfFile(in1) );

    do
    {
        value2 = streamReadBits(in2, 8);
        counter2++;
    }while(!checkEndOfFile(in2) );
    
    closeInStream(in1);                                           
    closeInStream(in2);   
    freeInStream(in1);                                           
    freeInStream(in2);        

    if( counter2 == counter1)
        return 1;
    else
        return 0;
}
