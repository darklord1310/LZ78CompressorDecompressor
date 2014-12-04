#ifndef Compression_H
#define Compression_H

#include "Dictionary.h"
#include "Stream.h"

int compare_DictionaryData(char *inputString,Dictionary *dictionary);
void LZ78_Compressor(Dictionary *dictionary, InStream *in, OutStream *out);
void LZ78_Output(OutStream *out,char outputByte,int index,int EOFstate);
void merge_InputDataDictionaryData(char *inputString,Dictionary *dictionary,int index);
int findLastMatchEntry(Dictionary *dictionary, InStream *in, char *dataString, char *readByte, int *returnedIndex, int *EOFstate);
#endif // Compression_H
