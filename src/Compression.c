#include "Compression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <string.h>
#include <stdio.h>

/* Modified LZ78 Compressor 
 *
 *  Index 0 is used to represent EOF for decompression usage
 *  Index 1 is used to represent data not found in dictionary
 *
 * Input :	dictionary	:	dictionary is the pointer to the LZ78 dictionary
 *			in			:	in is the pointer to InStream
 *			out			:	out is the pointer to OutStream
 *			mode 		:	Fixed -> fixed output dictionary index to 16bits
 *							Variable -> use just sufficient number of bits to represent the dictionary index
 */
void LZ78_Compressor(Dictionary *dictionary, InStream *in, OutStream *out, int mode)
{
    char readByte[2] ={}, dataString[1024] ;
    int returnedIndex, lastIndex, EOFstate = 0 , i = 0 ,dataStringSize;

    while (1)
    {
        readByte[0] = (char)(streamReadBits(in,8));

        if (checkEndOfFile(in)) // if EOF encountered
            break;  // break loop
            
        if(isDictionaryFull(dictionary))
            refreshDictionaryEntryData(dictionary,dictionary->dictionarySize);

        if(isDictionaryEmpty(dictionary)) // if dictionary is empty
        {
            addEntryData(dictionary, readByte,1); // directly add it into dictionary
            LZ78_Output(dictionary,out,readByte[0],1,EOFstate,mode); // output (1,x) *without ()
        }
        else // dictionary is not empty
        {
            returnedIndex = compare_DictionaryData(readByte,dictionary,1); //check is there any matched data in dictionaryEntry
            if ( returnedIndex >= 0 ) // if true
            {
                lastIndex = findLastMatchEntry(dictionary,in,dataString,&dataStringSize,readByte,returnedIndex, &EOFstate);

                if (EOFstate != 1)//prevent adding EOF into dictionary
                    addEntryData(dictionary,dataString,dataStringSize); // add dataString into dictionary

                LZ78_Output(dictionary,out,readByte[0],lastIndex+2,EOFstate,mode); // produce output (lastIndex+1 , X) *without ()
            }
            else // no matched data
            {
                addEntryData(dictionary,readByte,1);
                LZ78_Output(dictionary,out,readByte[0],1,EOFstate,mode); // output (1,x) *without ()
            }
        }

        if (EOFstate == 1) //EOF encountered previously
            break;
    }

}

/* Produce output for LZ78 Compressor
 *
 *
 * Input :	out			:	out is the pointer to OutStream
 *			outputByte	:	outputByte is the byte of data to be output
 *			index		: 	index is the dictionary index
 *			EOFstate	: 	EOFstate is used to prevent writing invalid data into the file
 *			mode 		:	Fixed -> fixed output dictionary index to 16bits
 *							Variable -> use just sufficient number of bits to represent the dictionary index
 */
void LZ78_Output(Dictionary *dictionary,OutStream *out,char outputByte,int index,int EOFstate, int mode)
{
    int bitsRequired = 0 ;

    if (mode == Fixed)
        bitsRequired = 16 ;
    else if (mode == Variable)
        bitsRequired = determineNumberOfBitsRequired(dictionary->currentIndex);

    streamWriteBits(out,index,bitsRequired);
    if (EOFstate == 0 ) // prevent writing EOF to file
        streamWriteBits(out,(unsigned int)(outputByte),8);
}


/* *
 *  Compare data in the dictionary with input data
 *
 *
 *	Input :	inputString	:	inputString is the pointer to the input data
 *		  	dictionary	:	dictionary is the pointer to the LZ78 dictionary
 *
 *	Output :	Return index of match entry if found
 * 				Return -1 if not found
 *
 */
int compare_DictionaryData(char *inputString,Dictionary *dictionary,int bytesToCompare)
{
    int i ;

   
    
    for ( i = 0 ; i < (dictionary->currentIndex) ; i ++ )
    {

        if (memcmp(inputString,(dictionary->Entry[i].data),bytesToCompare) == 0)
            return i ;
    }

    return (-1);
}

/*  Copy data in the selected index of dictionaryEntry to input data
 *
 *
 *	Input :	inputString	:	dataString is the pointer to the input data
 *		  	dictionary	:	dictionary is the pointer to the LZ78 dictionary which contains the data to be copied
 *           index       :   index of the dictionary containing the desired data
 */
void copy_DictionaryDataInputData(char *inputString,Dictionary *dictionary,int index)
{
   int bytesToCopy =  dictionary->Entry[index].entrySize ;
   
   memcpy(inputString,dictionary->Entry[index].data,bytesToCopy);
}


/*  Continuously read byte and find last match of the data in the dictionary
 *
 *	Input :	dictionary	:	dictionary is the pointer to the LZ78 dictionary which contains the data to be compared
 *           in          :   in is the pointer to InStream for reading a byte purpose
 *           dataString	:	dataString is used later to add the missing data into the dictionary
 *           readByte	:	readByte is used to output the byte of data in LZ78_Output
 *           returnedIndex : returnedIndex contains the first index of the match dictionaryEntry
 *           EOFstate    :   EOFstate is used to remember EOF has been encountered
 *
 *  Output :	Return index of last match entry
 *
 */
int findLastMatchEntry(Dictionary *dictionary, InStream *in, char *dataString,int *dataStringSize, char *readByte, int returnedIndex, int *EOFstate)
{
    int lastIndex = returnedIndex ; // store the index of first match in dictionaryEntry

    memset (dataString,0,1024); //clear dataString
    copy_DictionaryDataInputData(dataString,dictionary,lastIndex); //merge input character with data in dictionary
    *dataStringSize = dictionary->Entry[lastIndex].entrySize ; // get the size of dataString
    
    while(returnedIndex != -1)
    {
        readByte[0] = (char)(streamReadBits(in,8)) ;// read next character

        if (checkEndOfFile(in)) //if EOF detected
        {
            *EOFstate = 1 ; // use to remember EOF encountered for later uses
            returnedIndex = -1 ; //quit loop
        }
        else
        {
            memcpy( (dataString+*dataStringSize),readByte,1); //add next character to dataString
            *dataStringSize += 1; //increment dataStringSize
            returnedIndex = compare_DictionaryData(dataString,dictionary,*dataStringSize); //check again is there any matched data

            if (returnedIndex != -1 )  // if there is still existing a match in dictionaryEntry
                lastIndex = returnedIndex ; // store the index of last match in dictionaryEntry
        }
    }

    return lastIndex ;
}


