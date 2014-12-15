#ifndef Stream_H
#define Stream_H

#include <stdio.h>
#include <string.h>

typedef struct OutStream OutStream;
typedef struct InStream InStream;

typedef enum {ERR_FAILED_TO_OPEN} ERR;

struct OutStream
{
    char *filename;
    FILE *file;
    int byteToWrite;
    int bitIndex;
};


struct InStream
{
    char *filename;
    FILE *file;
    int byteToRead;
    int bitIndex;
};


InStream *openInStream(char *filename, char *mode, InStream *in);
OutStream *openOutStream(char *filename, char *mode, OutStream *out);

unsigned int streamReadBit(InStream *in);
unsigned int streamReadBits(InStream *in, int bitSize);

void streamWriteBit(OutStream *out, int bitToWrite);
void streamWriteBits(OutStream *out, unsigned int value, int bitSize);

void streamFlush(OutStream *out);

OutStream *closeOutStream(OutStream *out);
InStream *closeInStream(InStream *in);

InStream *initInStream();
OutStream *initOutStream();

void freeInStream(InStream *in);
void freeOutStream(OutStream *out);

int checkEndOfFile(InStream *in);

#endif // Stream_H
