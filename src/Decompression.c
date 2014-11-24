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
   
}


int getAPairOfIndexAndData(Dictionary *dictionary, InStream *in)
{
    
    unsigned int index, data;

    
    // index = streamReadBits(in, 16);
    // data = streamReadBits(in, 8);
   
    
}


int addDataToDictionary(Dictionary *dictionary, unsigned int data)
{
    int indicator;
    char *convertedData = (char *)(&data);      //typecast the int type data to char type
    
    indicator = addEntryData(dictionary, convertedData);
    
    if(indicator == 1)
        return 1;
    else
        return 0;
}


