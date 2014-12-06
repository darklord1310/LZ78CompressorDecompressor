#include "Decompression_noMocking.h"


int getPositionInFile(InStream *in)
{
    int position = ftell(in->file);


    return position;

}

void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize)
{
    int status = 0, signedIndex;
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
        if(status == 1)
            refreshDictionaryEntryData(dictionary, 4096);
    
        status = rebuildDictionaryForDecompression(dictionary, in);   //rebuild dictionary
        rewind(in->file);
        Decompression(in, out, dictionary);

    }while(status == 1);

    in = closeInStream(in);                                          //close input file
    out = closeOutStream(out);                                       //close output file
}