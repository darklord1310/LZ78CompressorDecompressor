#include "Compression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <string.h>
#include <stdio.h>

void LZ78_Compressor(Dictionary *dictionary, InStream *in, OutStream *out)
{       
    char readByte, dataString[1024] ;
    int returnedIndex, saveIndex;
    
    while ( (readByte = (char)(streamReadBits(in,8))) != EOF )
    {         
        if(isDictionaryFull(dictionary))
            refreshDictionaryEntryData(dictionary,dictionary->dictionarySize);
        
        if(isDictionaryEmpty(dictionary)) // if dictionary is empty
        {
            addEntryData(dictionary, &readByte); // directly add it into dictionary
            LZ78_Output(out,readByte,0); // output (0,x) *without braces
        }       
        else
        {
            returnedIndex = compare_DictionaryData(&readByte,dictionary); //check is there any matched data in dictionaryEntry
            if ( returnedIndex >= 0 ) // if true
            {
                saveIndex = returnedIndex ; // store the index of first match in dictionaryEntry
                memset (dataString,0,1024); //clear dataString
                
                while(returnedIndex != -1)
                {
                    readByte = (char)(streamReadBits(in,8)) ;// read next character
                    
                    if (readByte == EOF)
                        LZ78_Output(out,readByte,saveIndex+1);
                    else    
                    {
                        strcat(dataString,&readByte); //add next character to dataString
                        returnedIndex = compare_DictionaryData(dataString,dictionary); //check again is there any matched data
                    
                        if (returnedIndex != -1 )    
                            saveIndex = returnedIndex ; // store the index of last match in dictionaryEntry
                    }
                }
                
                if(addEntryData(dictionary,dataString)) // add dataString into dictionary
                    LZ78_Output(out,readByte,saveIndex+1); // produce output (dictionaryIndex+1)(X) *without ()
            }
            else // no matched data
            {
                if(addEntryData(dictionary,&readByte))
                    LZ78_Output(out,readByte,0); // output (0,x) *without braces
            }
        }
    }
}


void LZ78_Output(OutStream *out,char outputByte,int index)
{
    streamWriteBits(out,index,16);
    streamWriteBits(out,(int)(outputByte),8);
}


/* *
 *  Compare data in the dictionary with input
 *
 * Return index of match entry if found
 * Return -1 if not found
 */
int compare_DictionaryData(char *inputString,Dictionary *dictionary)
{
    int i ;
    
    for ( i = 0 ; i < (dictionary->currentIndex) ; i ++ )
    {
        if (strcmp(inputString,(dictionary->Entry[i].data)) == 0)
            return i ;
    }

    return (-1);
}

