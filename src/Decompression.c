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
 *            1     if dictionary full
 *            0     if dictionary not full
 *          
 */
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in)
{
    unsigned int index, data;
    char convertedData;
           
    do{
    
    index = streamReadBits(in, 16);
    data = streamReadBits(in, 8);
    addDataToDictionary(dictionary, data, index);
    convertedData = (char)data;               //typecast int to char
    
    if(isDictionaryFull(dictionary) == 1 )
        break;
    
    }while( convertedData != '$' );
    
    if(isDictionaryFull(dictionary) == 1 )
    {
        dictionary->currentIndex = 0;
        return 1;
    }
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
    
    rebuildDictionaryForDecompression(dictionary, in);          //rebuild dictionary
    
    string = strdup(Decompression(in, dictionary));             //decompress
    
    
    
    
    
    streamWriteBits(out, (unsigned int)(*string), 8);           //write to output file 
    
    in = closeInStream(in);                                     //open input file
    out = closeOutStream(out);                                  //open output file
}



char *Decompression(InStream *in, Dictionary *dictionary)
{
    unsigned int index, data;
    int signedIndex;
    char *string;
    
    index = streamReadBits(in, 16);                             //read index
    data = streamReadBits(in, 8);                               //read data
    
    signedIndex = (int)index;
    char *convertedData = (char*)(&data);
    
    if( signedIndex-1 < 0)                                      //if index is 0
        string = strdup(dictionary->Entry[signedIndex-1].data);
    else                                                        //if index is not 0
    {   
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);                          //combined the string with the data
    }

    return string;
}



void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index)
{
    int indicator;
    int signedIndex = (int)index;                    //to change the unsigned index into signed index
    char *convertedData = (char *)(&data);           //typecast the int type data to char type
    char *string;
    
    if( (signedIndex-1) < 0)
        indicator = addEntryData(dictionary, convertedData);
    else
    {
        string = strdup(dictionary->Entry[signedIndex-1].data);
        strcat(string, convertedData);
        indicator = addEntryData(dictionary, string);
    }
}


