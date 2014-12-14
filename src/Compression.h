#ifndef Compression_H
#define Compression_H

#include "Dictionary.h"
#include "Stream.h"
#include "Utility.h"

void LZ78_Compressor(Dictionary *dictionary, InStream *in, OutStream *out, int mode);
void LZ78_Output(Dictionary *dictionary,OutStream *out,unsigned char outputByte,int index,int EOFstate, int mode);
void copy_DictionaryDataInputData(unsigned char *inputString,Dictionary *dictionary,int index);

int findLastMatchEntry(Dictionary *dictionary, InStream *in,unsigned char *dataString,int *dataStringSize,unsigned char *readByte, int returnedIndex, int *EOFstate);
int compare_DictionaryData(unsigned char *inputString,Dictionary *dictionary,int bytesToCompare);
#endif // Compression_H
