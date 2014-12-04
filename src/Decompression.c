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



void LZ78_Decompressor(char *infilename, char *outfilename, Dictionary *dictionary)
{
    int status, signedIndex;
    unsigned int index, data;
    char *string;
    InStream *in;
    OutStream *out;
    
    in = initInStream();
    out = initOutStream();
    
    in = openInStream(infilename, "rb" , in);                        //open input file
    out = openOutStream(outfilename, "wb" , out);                    //open output file
    

    status = rebuildDictionaryForDecompression(dictionary, in);      //rebuild dictionary
    

    
    
    

    
    in = closeInStream(in);                                         //open input file
    out = closeOutStream(out);                                      //open output file
}



void Decompression(InStream *in, OutStream *out, Dictionary *dictionary)
{
    unsigned int index, data;
    int signedIndex , i;
    char *string;
    
    while(1)
    {
        index = streamReadBits(in, 16);                             //read index
        signedIndex = (int)index;
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
                string = strdup(dictionary->Entry[index-1].data);
                strcat(string, convertedData);                          //combined the string with the data
                for(i=0; i < strlen(string); i++)
                    streamWriteBits(out, (unsigned int)(string[i]), 8);
            }
        }
        else
        {
            for(i=0; i < dictionary->Entry[index-1].entrySize; i++)
                streamWriteBits(out, (unsigned int)(dictionary->Entry[index-1].data[i]), 8);
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


