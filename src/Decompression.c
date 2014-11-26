#include "Dictionary.c"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>




/*
 * Build the dictionary for decompression
 *
 * Input :
 *					
 *
 */
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in)
{

    int DictionaryFull;
    
    
    // do{
    
    // index = streamReadBits(in, 16);
    // data = streamReadBits(in, 8);
    // DictionaryFull = addDataToDictionary(dictionary, data, index);
        
    // }while( data != '$' || DictionaryFull);
   
}





int addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index)
{
    int indicator;
    int signedIndex = index;                    //to change the unsigned index into signed index
    char *convertedData = (char *)(&data);      //typecast the int type data to char type
    char *string;
    
    if( (signedIndex-1) < 0)
        indicator = addEntryData(dictionary, convertedData);
    else
    {
        strcpy(string, dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);
        strcpy(convertedData, string);
        indicator = addEntryData(dictionary, convertedData);
    }
    
    if(indicator == 1)
        return 1;
    else
        return 0;
}


