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

OutStream *closeOutStream(OutStream *out)
{
    if (out->bitIndex != 0)
        streamFlush(out);
        
    fclose(out->file);
}

InStream *closeInStream(InStream *in)
{
    fclose(in->file);
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

void streamWriteBit(OutStream *out,int bitToWrite)
{
    out->byteToWrite = (out->byteToWrite) << 1 ; //shift left 1 time
    out->byteToWrite = out->byteToWrite | bitToWrite ;
    out->bitIndex ++ ;
}

void streamWriteBits(OutStream *out,unsigned int value,int bitSize)
{
    int bitToWrite[bitSize],bitTest, i ,j ;
    
    j = bitSize - 1;
    
    for ( i = 0 ; i < bitSize ; i ++) //reverse value to Write MSB first
    {
        bitTest = (value >> i) & 1; 
        if (bitTest != 0)
            bitToWrite[j] = 1;
        else    
            bitToWrite[j] = 0;
        j -- ;
    }
    
   
    for ( i = 0 ; i < bitSize ; i ++) //write value to buffer
    {
        if (out->bitIndex == 8)
            streamFlush(out);

        streamWriteBit(out,bitToWrite[i]);
    }
    printf("Byte to write %c",out->byteToWrite);
}    
    
void streamFlush(OutStream *out)
{
    int n;
    n = fwrite(&(out->byteToWrite),1,1,out->file);
    
    out->byteToWrite = 0;
    out->bitIndex = 0 ;
}

int checkEndOfFile(InStream *in)
{
    if(feof (in->file))
        return 1;
        
    else 
        return 0 ;

}