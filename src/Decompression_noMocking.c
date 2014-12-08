#include "Decompression_noMocking.h"
#include "Decompression.h"



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
        finalDecompression(in, out, dictionary, &lastDecompressPosition, status);
        
        if(status != -1)
            refreshDictionaryEntryData(dictionary, dictSize);
        else
        {
            printf("break\n");
            break;
        }
    }

    in = closeInStream(in);                                          //close input file
    out = closeOutStream(out);                                       //close output file
}




void finalDecompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition, int lastDictionaryLocation)
{
    unsigned int index, data, convertedIndex;
    int signedIndex , i, position;
    char *string;
    
    // printf("lastdecompressposition: %d\n", *lastDecompressPosition);
    if(*lastDecompressPosition == 0)                               //check is it the first time get into this function
        rewind(in->file);                                          //if yes, rewind the file pointer to the first location
    else
    {
        // if( lastDictionaryLocation != -1)
            fseek(in->file , *lastDecompressPosition , SEEK_SET);  //if no, move the file pointer to the lastDecompress location
    }
    
    
    while(1)
    {
        printf("lastdictionaryposition : %d\n", lastDictionaryLocation);
        index = streamReadBits(in, 16);                             //read index
        signedIndex = (int)index;                          //convert it to a signed index
        printf("index : %d\n" , index);
        // position = getPositionInFile(in);
        // printf("position: %d\n",  position);
        if( checkEndOfFile(in)  )                                   //check is it a EOF, if yes break from the loop
        {
            // *lastDecompressPosition = getPositionInFile(in);
            break;
        }
            
        data = streamReadBits(in, 8);                               //read data
        char *convertedData = (char*)(&data);                       //typecast data from unsigned int to char
        printf("data : %s\n" , convertedData);
        // position = getPositionInFile(in);
        // printf("position: %d\n",  position);
        if( !checkEndOfFile(in)  )                                  //check if it is not EOF
        {
            printf("write to output\n");
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
            if(convertedIndex != 0)
            {
                for(i=0; i < dictionary->Entry[convertedIndex-1].entrySize; i++)
                    streamWriteBits(out, (unsigned int)(dictionary->Entry[convertedIndex-1].data[i]), 8);
            }
            break;
        }
    }

    printf("out of the loop\n");
}




/*
 * Build the dictionary for decompressionl
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
        {
            printf("position in dict: %d\n", lastDictionaryLocation);
            return lastDictionaryLocation;
        }
    }
    else
        return -1;
}