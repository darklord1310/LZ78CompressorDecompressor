#include "Dictionary.h"
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
 * Return:  1       if dictionary full
 *          
 */
int rebuildDictionaryForDecompression(char *filename, char *mode, Dictionary *dictionary, InStream *in)
{
    unsigned int index, data;
    char convertedData;
    
    in = openInStream(filename, mode, in);
        
    do{
    
    index = streamReadBits(in, 16);
    data = streamReadBits(in, 8);
    addDataToDictionary(dictionary, data, index);
    convertedData = (char)data;               //typecast int to char
    
    if(isDictionaryFull(dictionary) == 1 )
        break;
    
    }while( convertedData != '$' );
    
    in = closeInStream(in);
    
    if(isDictionaryFull(dictionary) )
        return 1;
    else
        return 0;
}


void LZ78_Decompressor(char *infilename, char *outfilename, char *inmode, char *outmode, Dictionary *dictionary, InStream *in, OutStream *out)
{
    int status, signedIndex;
    unsigned int index, data;
    char *string;
    
    status = rebuildDictionaryForDecompression(infilename, inmode, dictionary, in);
    
    in = openInStream(infilename, inmode, in);
    index = streamReadBits(in, 16);
    data = streamReadBits(in, 8);
    signedIndex = index;
    
    if( signedIndex-1 < 0) 
        string = strdup(dictionary->Entry[signedIndex-1].data);
    


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
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);
        indicator = addEntryData(dictionary, string);
    }
    
    if(indicator == 1)
        return 1;
    else
        return 0;
}


