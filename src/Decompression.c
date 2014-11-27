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
    
    in = openInStream(infilename, inmode, in);                  //open input file
    out = openOutStream(outfilename, outmode, out);             //open output file
    
    status = rebuildDictionaryForDecompression(infilename, inmode, dictionary, in);     //rebuild dictionary
    
    index = streamReadBits(in, 16);                             //read index
    data = streamReadBits(in, 8);                               //read data
    
    signedIndex = index;
    char *convertedData = (char*)(&data);
    
    if( signedIndex-1 < 0)                                      //if index is 0
    {
        string = strdup(dictionary->Entry[signedIndex-1].data);
        streamWriteBits(out, (unsigned int)(*string), 8);       //just write to output file directly
    }
    else                                                        //if index is not 0
    {   
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);                          //combined the string with the data
        streamWriteBits(out, (unsigned int)(*string), 8);       //then write to output file
    }

    
    in = closeInStream(in);                                    //open input file
    out = closeOutStream(out);                                 //open output file

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


