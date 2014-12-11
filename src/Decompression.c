#include "Dictionary.h"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>



int LZ78_Decompressor(char *infilename, char *outfilename, int dictSize)
{
    InStream *in;
    OutStream *out;
    Dictionary *dict;
    int status;
    
    status = LZ78_Decompression(in, out, dict, infilename, outfilename, dictSize);

    return status;
}




int LZ78_Decompression(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize)
{
    int status, signedIndex, i, n=1;
    unsigned int index, data;

    in = initInStream();                                              //init InSteam
    out = initOutStream();                                            //init OutStream
    dictionary = initDictionary(dictSize);                            //init Dictionary
    
    in = openInStream(infilename, "rb+" , in);                         //open input file
    out = openOutStream(outfilename, "wb+" , out);                     //open output file
    
    if( checkEndOfFile(in) )                                           //check is it an empty file
        return 0;

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
    
    return 1;
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

