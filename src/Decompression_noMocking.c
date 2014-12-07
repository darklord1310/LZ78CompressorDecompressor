#include "Decompression_noMocking.h"
#include "Decompression.h"


void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize)
{
    int lastDecompressPosition = -1, status;
    int signedIndex;;
    unsigned int index, data;
    char *string;
    InStream *in;
    OutStream *out;
    Dictionary *dictionary;
    
    in = initInStream();
    out = initOutStream();
    dictionary = initDictionary(dictSize);
    
    in = openInStream(infilename, "rb+" , in);                         //open input file
    out = openOutStream(outfilename, "wb+" , out);                     //open output file

    do{

        status = rebuildDictionaryForDecompression(dictionary, in , &lastDecompressPosition);   //rebuild dictionary
        finalDecompression(in, out, dictionary, &lastDecompressPosition);
        
        if(status != -1)
            refreshDictionaryEntryData(dictionary, 4096);

    }while(status != -1);

    in = closeInStream(in);                                          //close input file
    out = closeOutStream(out);                                       //close output file
}




void finalDecompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition)
{
    unsigned int index, data, convertedIndex;
    int signedIndex , i;
    char *string;
    
    if( *lastDecompressPosition != -1)
        fseek(in->file , *lastDecompressPosition , SEEK_SET);
    else
        rewind(in->file);
    
    while(1)
    {
        index = streamReadBits(in, 16);                             //read index
        convertedIndex = swapUpper16bitsWithLower16bits(index);     //correct the bits sequence by swapping the upper8 bits with lower8 bits
        signedIndex = (int)convertedIndex;
        
        if( checkEndOfFile(in) || getPositionInFile(in) == *lastDecompressPosition)
            break;
            
        data = streamReadBits(in, 8);                               //read data
        char *convertedData = (char*)(&data);
        
        if( !checkEndOfFile(in) || getPositionInFile(in) != *lastDecompressPosition)
        {
            if( signedIndex-1 < 0)                                      //if index is 0
                streamWriteBits(out, (unsigned int)(*convertedData), 8);
            else                                                        //if index is not 0
            {   
                string = strdup(dictionary->Entry[convertedIndex-1].data);
                strcat(string, convertedData);                          //combined the string with the data
                for(i=0; i < strlen(string); i++)
                    streamWriteBits(out, (unsigned int)(string[i]), 8);
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
}