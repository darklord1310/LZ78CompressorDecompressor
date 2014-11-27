#ifndef Compression_H
#define Compression_H

#include "Dictionary.h"

int compare_DictionaryData(char *inputString,Dictionary *dictionary);
void merge_InputDataDictionaryData(char *inputString,char *outputString,Dictionary *dictionary,int index);
void LZ78_Compressor(char *inputBuffer, char *outputBuffer, Dictionary *dictionary);
void LZ78_Output(char *inputString,char *outputBuffer,int index);

#endif // Compression_H