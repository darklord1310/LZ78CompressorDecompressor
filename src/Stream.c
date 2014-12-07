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

unsigned int streamReadBit(InStream *in)
{
    int bitTest ;
    
    bitTest = in->byteToRead & (1 << in->bitIndex) ; //read lSB first
    in -> bitIndex ++ ;
    
    if (bitTest != 0 )
        return 1 ; 
    else 
        return 0 ;
}


unsigned int streamReadBits(InStream *in, int bitSize)
{
    unsigned int dataRead = 0, bitRead = 0 ,i ;
    
    if (in->byteToRead == 0 && in->bitIndex == 0 ) //no data have been read yet
        fread(&(in->byteToRead),1,1,in->file);

    for ( i = 0 ; i < bitSize ; i ++)
    {
        if (in->bitIndex == 8 ) //fully extracted 1 byte
        {
            fread(&(in->byteToRead),1,1,in->file); //read new byte
            in->bitIndex = 0 ;
        }
        
        bitRead = streamReadBit(in);
        dataRead = dataRead | bitRead << i;
    }
    return dataRead ;
}

void streamWriteBit(OutStream *out,int bitToWrite)
{
    out->byteToWrite |= (bitToWrite << out->bitIndex) ; //write lSB first
    out->bitIndex ++ ;
}

void streamWriteBits(OutStream *out,unsigned int value,int bitSize)
{
    int bitToWrite, i ,j ;
    
    for ( i = 0 ; i < bitSize ; i ++) //write value to buffer
    {
        if (out->bitIndex == 8)
            streamFlush(out);

        bitToWrite = value & (1 << i ) ;
        
        if (bitToWrite != 0 )
            bitToWrite = 1 ;
        else 
            bitToWrite = 0 ;
            
        streamWriteBit(out,bitToWrite);
    }
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
    int result ;
    result = feof (in->file) ;
       
    if (result != 0)
        return 1;
    else 
}


int getPositionInFile(InStream *in)
{
    int position = ftell(in->file);


    return position;
}