#include "Dictionary.h"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>




/*
 * Build the dictionary for decompression, will return 1 if dictionary has full
 *
 * Input :
 *					
 *
 * Return:
 *            -1     if dictionary not full
 *          not -1   if dictionary has already full
 *          
 */
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in, int *lastDecompressPosition)
{
    unsigned int index, data, convertedIndex;
    char convertedData;
           
    while(1)
    {
        index = streamReadBits(in, 16);
        convertedIndex = swapUpper16bitsWithLower16bits(index);
        
        if( checkEndOfFile(in) )
            break;
            
        data = streamReadBits(in, 8);
        if( checkEndOfFile(in) )
            break;
            
        addDataToDictionary(dictionary, data, convertedIndex);
        
        if(isDictionaryFull(dictionary) == 1 )
        {
            *lastDecompressPosition = getPositionInFile(in) + 1;
            break;
        }
    } 
    
    if(isDictionaryFull(dictionary) == 1 )
        return *lastDecompressPosition;
    else
        return -1;

}


/* This function is to check for the main functionality of decompression, but this is not the final and real function
 * the final version of this function is located at Decompression_noMocking, it is not including here because I can'tan
 * mock the function like fseek and rewind
 */
void Decompression(InStream *in, OutStream *out, Dictionary *dictionary)
{
    unsigned int index, data, convertedIndex;
    int signedIndex , i;
    char *string;
    
    while(1)
    {
        index = streamReadBits(in, 16);                             //read index
        convertedIndex = swapUpper16bitsWithLower16bits(index);
        signedIndex = (int)convertedIndex;
        
        if( checkEndOfFile(in) )
            break;
            
        data = streamReadBits(in, 8);                               //read data
        char *convertedData = (char*)(&data);
        
        if( !checkEndOfFile(in) )
        {
            if( signedIndex-1 < 0)                                      //if index is 0
                streamWriteBits(out, (unsigned int)(*convertedData), 8);
            else                                                        //if index is not 0
            {   
                string = strdup(dictionary->Entry[convertedIndex-1].data);
                strcat(string, convertedData);                          //combined the string with the data
                for(i=0; i < strlen(string); i++)
                    streamWriteBits(out, (unsigned int)(string[i]), 8);
            }
        }
        else
        {
            if(convertedIndex != 0)
            {
                for(i=0; i < dictionary->Entry[convertedIndex-1].entrySize; i++)
                    streamWriteBits(out, (unsigned int)(dictionary->Entry[convertedIndex-1].data[i]), 8);
            }
            break;
        }
    }
}



void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index)
{
    int signedIndex = (int)index;                    //to change the unsigned index into signed index
    char *convertedData = (char *)(&data);           //typecast the int type data to char type
    char *string;

    if( (signedIndex-1) < 0)
        addEntryData(dictionary, convertedData);
    else
    {
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);
        addEntryData(dictionary, string);
    }
}



// this function is used to correct the read sequence of int value read by streamReadBits
unsigned int swapUpper16bitsWithLower16bits(unsigned int value)
{
    unsigned int low8bits = value & 0x000F;
    unsigned int upper8bits = (value >> 8);
    unsigned int newvalue = (low8bits << 8) | upper8bits;

    
    return newvalue;
}