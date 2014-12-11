#include "Dictionary.h"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>



void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize, int mode)
{
    InStream *in;
    OutStream *out;
    Dictionary *dict;
    
    if(mode == Fixed)
        LZ78_Decompression_Fixed(in, out, dict, infilename, outfilename, dictSize);
    
}




void LZ78_Decompression_Fixed(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize)
{
    int status, signedIndex, i;
    unsigned int index, data, bitsToRead;

    in = initInStream();                                              //init InSteam
    out = initOutStream();                                            //init OutStream
    dictionary = initDictionary(dictSize);                            //init Dictionary
    
    in = openInStream(infilename, "rb+" , in);                         //open input file
    out = openOutStream(outfilename, "wb+" , out);                     //open output file

    while(1)
    {
        index = streamReadBits(in, 16);                                //read index
        signedIndex = (int)index;                                      //convert it to a signed index

        if( checkEndOfFile(in)  )                                      //check is it a EOF, if yes break from the loop
            break;
            
        data = streamReadBits(in, 8);                                  //read data
        
        if( checkEndOfFile(in)  )                                      //check is it a EOF, if yes 
        {
            assert( index != 0);
            for(i=0; i < dictionary->Entry[index-1].entrySize; i++)
                streamWriteBits(out, (unsigned int)(dictionary->Entry[index-1].data[i]), 8);
            break;
        }
        else
        {
            status = AddDataToDictionary(dictionary, index, data);      //add data to dictionary
            if(status == 0)                                             //if failed, refresh dictionary and add again
            {
                refreshDictionaryEntryData(dictionary,dictSize);
                status = AddDataToDictionary(dictionary, index, data);  //add data to dictionary
                assert(status != 0);                                    //here cannot be 0 because the dictionary has already refreshed
                assert(dictionary->currentIndex == 1);
            } 
            Decompression(out, index, data, dictionary);
        }
    }

    closeInStream(in);                                            //close input file
    closeOutStream(out);                                          //close output file
    
    assert(dictionary->currentIndex <= dictSize);
    
    destroyDictionary(dictionary,dictSize);                       //free dictionary
    freeInStream(in);                                             //free InStream
    freeOutStream(out);                                           //free OutStream
}




void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary)
{
    int signedIndex = (int)index;
    int i;
    char string[4096];
    char *convertedData = (char *)(&data);                      //typecast the int type data to char type
    
    assert(signedIndex >= 0);
    if( signedIndex-1 < 0)                                      //if index is 0
        streamWriteBits(out, data, 8);
    else                                                        //if index is not 0
    {   
        memset (string,0,4096);                                 //clear string
        strcpy(string,dictionary->Entry[index-1].data);
        strcat(string, convertedData);                          //combined the string with the data
        
        for(i=0; i < strlen(string); i++)
            streamWriteBits(out, (unsigned int)(string[i]), 8);
    }

}




/*
 * Add data into the dictionary
 *
 * Input :            
 *
 *					
 *
 * Return:
 *            1     dictionary is not full and data is written successfully
 *            0     dictionary has already full and data is not written into dictionary
 *          
 */
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data)
{
    int signedIndex = (int)index;                    //to change the unsigned index into signed index
    char *convertedData = (char *)(&data);
    // unsigned int mergedData;
    char string[4096];
    int status;
    
    assert(signedIndex >= 0);
    if(dictionary->currentIndex == dictionary->dictionarySize)
        return 0;
    
    if( (signedIndex-1) < 0)
    {
        status = addEntryData(dictionary, convertedData); 
        assert(status == 1);

    }
    else
    {
        memset (string,0,4096);                     //clear string
        strcpy(string,dictionary->Entry[index-1].data);
        strcat(string, convertedData);
        status = addEntryData(dictionary, string);
        assert(status == 1);
    }
}


unsigned int getVariableIndex(Dictionary *dictionary)
{
    int count = 0;
    int value = dictionary->currentIndex;
    
    if( dictionary->currentIndex == 0)
        return 1;
        
    assert( dictionary->currentIndex != 0);
    
    while (value != 0) {
        count++;
        value = value >> 1;
    }
    return count;
}
  





/*
void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize)
{
    int lastDecompressPosition = 0, lastDictionaryLocation = -1;
    int signedIndex, status;
    unsigned int index, data;
    char *string;
    InStream *in;
    OutStream *out;
    Dictionary *dictionary;
    
    in = initInStream();                                              //init InSteam
    out = initOutStream();                                            //init OutStream
    dictionary = initDictionary(dictSize);                            //init Dictionary
    
    in = openInStream(infilename, "rb+" , in);                         //open input file
    out = openOutStream(outfilename, "wb+" , out);                     //open output file

    while(1)
    {
        status = finalrebuildDictionaryForDecompression(dictionary, in , &lastDecompressPosition, lastDictionaryLocation);   //rebuild dictionary
        finalDecompression(in, out, dictionary, &lastDecompressPosition, status);                                            //Decompress
        
        if(status != -1)
            refreshDictionaryEntryData(dictionary, dictSize);
        else
            break;
    }

    closeInStream(in);                                          //close input file
    closeOutStream(out);                                       //close output file
    
    // destroyDictionary(dictionary,dictionary->currentIndex);       //free dictionary
    freeInStream(in);                                                //free InStream
    freeOutStream(out);                                              //free OutStream
    
}




void finalDecompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition, int lastDictionaryLocation)
{
    unsigned int index, data;
    int signedIndex , i, position;
    char *string;

    assert(*lastDecompressPosition >= 0);
    assert(lastDictionaryLocation >= -1);
    
    if(*lastDecompressPosition == 0)                               //check is it the first time get into this function
        rewind(in->file);                                          //if yes, rewind the file pointer to the first location
    else
        fseek(in->file , *lastDecompressPosition , SEEK_SET);      //if no, move the file pointer to the lastDecompress location
    
    while(1)
    {
        index = streamReadBits(in, 16);                             //read index
        signedIndex = (int)index;                                   //convert it to a signed index

        if( checkEndOfFile(in)  )                                   //check is it a EOF, if yes break from the loop
            break;
            
        data = streamReadBits(in, 8);                               //read data
        char *convertedData = (char*)(&data);                       //typecast data from unsigned int to char
        
        if( !checkEndOfFile(in)  )                                  //check if it is not EOF
        {
            if( signedIndex-1 < 0)                                      //if index is 0, straight away write the data to output
                streamWriteBits(out, (unsigned int)(*convertedData), 8);
            else                                                        //if index is not 0 combine the string with the data then only write to output
            {   
                string = strdup(dictionary->Entry[signedIndex-1].data);
                strcat(string, convertedData);                        
                for(i=0; i < strlen(string); i++)
                    streamWriteBits(out, (unsigned int)(string[i]), 8);
            }
            
            if(lastDictionaryLocation != -1)                           
            {
                if( getPositionInFile(in) == lastDictionaryLocation )
                {
                    *lastDecompressPosition = getPositionInFile(in);
                    break;
                }
            }
        }
        else
        {
            if(index != 0)
            {
                for(i=0; i < dictionary->Entry[index-1].entrySize; i++)
                    streamWriteBits(out, (unsigned int)(dictionary->Entry[index-1].data[i]), 8);
            }
            break;
        }
    }
}




/*
 * Build the dictionary for decompression
 *
 * Input :          lastDecompressPosition will be 0 at the first time passing in   
 *                  lastDictionaryLocation will be -1 at the first time passing in
 *					
 *
 * Return:
 *            -1     no need for further rebuild
 *          not -1   needed for further rebuild
 *          
 */
 /*
int finalrebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in, int *lastDecompressPosition, int lastDictionaryLocation)
{
    unsigned int index, data, convertedIndex;
    char convertedData;
    
    if( lastDictionaryLocation != -1)                           //if it is not -1 then we need to travel to last decompress position
        fseek(in->file , *lastDecompressPosition , SEEK_SET);
    
    while(1)
    {
        index = streamReadBits(in, 16);
  
        if( checkEndOfFile(in) )
            break;
            
        data = streamReadBits(in, 8);
        
        if( checkEndOfFile(in) )
            break;
            
        addDataToDictionary(dictionary, data, index);
        
        if(isDictionaryFull(dictionary) == 1 )
        {
            lastDictionaryLocation = getPositionInFile(in);
            break;
        }
    } 
    
    if(isDictionaryFull(dictionary) == 1 )
    {
        index = streamReadBits(in, 16);
        if( checkEndOfFile(in) )
            return -1;
        else
            return lastDictionaryLocation;
    }
    else
        return -1;
}
*/