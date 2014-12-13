#include "Dictionary.h"
#include "Stream.h"
#include "Decompression.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
 * Responsible for the complete decompression process
 *
 * Input :    
 *            infilename is the name of the input file
 *            outfilename is the name of the output file
 *            dictSize is the size of the dictionary
 *            mode is for user to select either fixed index or variable index
 *          
 */
void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize, int mode)
{
    InStream *in;
    OutStream *out;
    Dictionary *dict;
    
    if(mode == Fixed)
        LZ78_Decompression_Fixed(in, out, dict, infilename, outfilename, dictSize);
    else
        LZ78_Decompression_Variable(in, out, dict, infilename, outfilename, dictSize);
}



/*
 * Responsible for the complete decompression process for fixed Index
 *
 * Input :    dictionary is the pointer to the Dictionary structure
 *			  in is the pointer pointing to the structure InStream
 *            out is the pointer pointing to the structure OutStream
 *            infilename is the name of the input file
 *            outfilename is the name of the output file
 *            dictSize is the size of the dictionary, maximum is 4096
 *          
 */
void LZ78_Decompression_Fixed(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize)
{
    int status, signedIndex, i;
    unsigned int index, data;

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
            assert( index != 1);
            for(i=0; i < dictionary->Entry[index-2].entrySize; i++)
                streamWriteBits(out, (unsigned int)(dictionary->Entry[index-2].data[i]), 8);
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


/*
 * Responsible for the complete decompression process for variable Index
 *
 * Input :    dictionary is the pointer to the Dictionary structure
 *			  in is the pointer pointing to the structure InStream
 *            out is the pointer pointing to the structure OutStream
 *            infilename is the name of the input file
 *            outfilename is the name of the output file
 *            dictSize is the size of the dictionary
 *          
 */
void LZ78_Decompression_Variable(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize)
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
        if(dictionary->currentIndex == dictionary->dictionarySize )
            bitsToRead = 1;
        else
            bitsToRead = getVariableIndex(dictionary);
        index = streamReadBits(in, bitsToRead);                        //read index

        if( checkEndOfFile(in) || index == 0 )                         //check is it a EOF or 0, if yes break from the loop
            break;
            
        data = streamReadBits(in, 8);                                  //read data

        if( checkEndOfFile(in)  )                                      //check is it a EOF, if yes 
        {
            assert( index != 1);
            for(i=0; i < dictionary->Entry[index-2].entrySize; i++)
                streamWriteBits(out, (unsigned int)(dictionary->Entry[index-2].data[i]), 8);
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




/*
 * Decompress the compression input
 *
 * Input :    out is the pointer which pointing to the OutSream structure
 *            dictionary is the pointer to the Dictionary structure
 *            index is the index that read from the compressed output
 *            data is the data that read from the compressed output
 *					
 */
void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary)
{
    int i;
    char string[4096];
    char *convertedData = (char *)(&data);                      //typecast the int type data to char type
    
    assert(index > 0);
    if( index == 1)                                             //if index is 1
        streamWriteBits(out, data, 8);
    else                                                        //if index is not 1
    {   
        memset (string,0,4096);                                 //clear string
        memcpy(string , dictionary->Entry[index-2].data , dictionary->Entry[index-2].entrySize);
        memmove(string + dictionary->Entry[index-2].entrySize, convertedData, 1);       //combined the string with the data

        for(i=0; i < dictionary->Entry[index-2].entrySize +1; i++)
            streamWriteBits(out, (unsigned int)(string[i]), 8);
    }

}




/*
 * Add data into the dictionary
 *
 * Input :    dictionary is the pointer to the Dictionary structure
 *            index is the index that read from the compressed output
 *            data is the data that read from the compressed output
 *					
 *
 * Return:
 *            1     dictionary is not full and data is written successfully
 *            0     dictionary has already full and data is not written into dictionary
 *          
 */
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data)
{
    char *convertedData = (char *)(&data);
    char string[4096];
    int status, i;
    
    assert(index > 0);
    if(dictionary->currentIndex == dictionary->dictionarySize)
        return 0;
    
    if( index-1 == 0)
    {
        status = addEntryData(dictionary, convertedData, 1); 
        assert(status == 1);

    }
    else
    {
        memset (string,0,4096);                     //clear string
        memcpy(string , dictionary->Entry[index-2].data , dictionary->Entry[index-2].entrySize);
        memmove(string + dictionary->Entry[index-2].entrySize, convertedData, 1);
        status = addEntryData(dictionary, string, dictionary->Entry[index-2].entrySize + 1);
        assert(status == 1);
    }
}




/*
 * This function will determine how many bits is needed to read for the index
 *
 * Input :    dictionary is the pointer to the Dictionary structure
 *					
 *
 * Return:
 *           the number of bits that needed to read
 *          
 */
unsigned int getVariableIndex(Dictionary *dictionary)
{
    int count = 0;
    int value = dictionary->currentIndex + 1;
    
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


    All the code below is the old algorithm which I have written.
    
    The reason I decided to rewrite the algorithm is because the new algorithm is easier, old algorithm has to keep track on the position
    of the file pointer which is not needed in the new algorithm.
   
    The old algorithm flow:
                            build the dictionary until  _______\        Start to decompress     _______\    If full reset and repeat, until dictionary
                                it is full                     /                                       /            is not overflow

    New algorithm flow    :
                            build the dictionary for    _______\       Decompress              ________\    If dictionary full, reset    _______\  If EOF not encounter, repeat
                                    once                       /                                       /                                        /

*/


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
        status = rebuildDictionaryForDecompression(dictionary, in , &lastDecompressPosition, lastDictionaryLocation);   //rebuild dictionary
        Decompression(in, out, dictionary, &lastDecompressPosition, status);                                            //Decompress
        
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




void Decompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition, int lastDictionaryLocation)
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




int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in, int *lastDecompressPosition, int lastDictionaryLocation)
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