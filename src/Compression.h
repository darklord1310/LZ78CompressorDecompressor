#ifndef Compression_H
#define Compression_H

#include "Dictionary.h"
#include "Stream.h"
#include "Utility.h"

void LZ78_Compressor(Dictionary *dictionary, InStream *in, OutStream *out, int mode);
void LZ78_Output(Dictionary *dictionary,OutStream *out,char outputByte,int index,int EOFstate, int mode);
void merge_InputDataDictionaryData(char *inputString,Dictionary *dictionary,int index);

int findLastMatchEntry(Dictionary *dictionary, InStream *in, char *dataString, char *readByte, int returnedIndex, int *EOFstate);
int determineNumberOfBitsRequired(int index);
int compare_DictionaryData(char *inputString,Dictionary *dictionary);
#endif // Compression_H
