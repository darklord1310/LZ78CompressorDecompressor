#ifndef Stream_H
#define Stream_H


#include <stdio.h>

typedef struct OutStream
{
    char *filename;
    FILE *file;
    int byteToWrite;
    int bitIndex;
}OutStream;


typedef struct InStream
{
    char *filename;
    FILE *file;
    int byteToWrite;
    int bitIndex;
}InStream;


InStream *openInStream(char *filename, char *mode);
OutStream *openOutputStream(char *filename, char *mode);
unsigned int streamReadBit(InStream *in);
unsigned int streamReadBits(InStream *in, int bitSize);
void streamWriteBit(OutStream *out, int bitToWrite);
void streamWriteBits(OutStream *out, unsigned int value, int bitSize);
void streamFlush(OutStream *out);
OutStream *closeOutStream(OutStream *out);
InStream *closeInStream(InStream *in);

#endif // Stream_H
