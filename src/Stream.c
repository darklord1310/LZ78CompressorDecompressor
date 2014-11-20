#include "Stream.h"
#include <malloc.h>
#include <string.h>
#include <CException.h>

InStream *initInStream()
{
    InStream *in;
    in = malloc(sizeof(InStream));
    in->byteToRead = 0;
    in->bitIndex = 0;

    return in;
}


OutStream *initOutStream()
{
    OutStream *out;
    out = malloc(sizeof(OutStream));
    out->byteToWrite = 0;
    out->bitIndex = 0;

    return out;
}



void freeInStream(InStream *in)
{
    free(in);
}


void freeOutStream(OutStream *out)
{
    free(out);
}



InStream *openInStream(char *filename, char *mode, InStream *in)
{
    in->file = fopen( filename, mode);
    if( in->file == NULL)
        Throw(ERR_FAILED_TO_OPEN);
    else
        in->filename = filename;

    return in;
}



OutStream *openOutStream(char *filename, char *mode, OutStream *out)
{
    out->file = fopen( filename, mode);
    out->filename = filename;

    return out;
}

/*
unsigned int streamReadBit(InStream *in)
{
    int *dataRead = &(in->byteToRead);
    int bitRead ;
    
    fread(dataRead,sizeof(char),1, in->file);

    *bitRead = *dataRead & 1 ;
    
    return bitRead ;
}


unsigned int streamReadBits(InStream *in, int bitSize)
{



}
*/
