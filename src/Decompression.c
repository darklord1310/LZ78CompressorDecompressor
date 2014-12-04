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
           
    while(1)
    {
        index = streamReadBits(in, 16);
        if( checkEndOfFile(in) )
            break;
            
        data = streamReadBits(in, 8);
        if( checkEndOfFile(in) )
            break;
            
        convertedData = (char)data;               //typecast int to char
        addDataToDictionary(dictionary, data, index);
        
        if(isDictionaryFull(dictionary) == 1 )
            break;
    }
    
    if(isDictionaryFull(dictionary) == 1 )
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
    
    rebuildDictionaryForDecompression(dictionary, in);          //rebuild dictionary
    

    
    
    
    streamWriteBits(out, (unsigned int)(*string), 8);           //write to output file 
    
    in = closeInStream(in);                                     //open input file
    out = closeOutStream(out);                                  //open output file
}



void Decompression(InStream *in, OutStream *out, Dictionary *dictionary)
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


