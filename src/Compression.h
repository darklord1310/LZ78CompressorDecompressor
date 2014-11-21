#ifndef Compression_H
#define Compression_H

#include "Dictionary.h"

int compare_DictionaryData(char *input,Dictionary *dictionary);
void merge_InputDataDictionaryData(char *input,char *output,Dictionary *dictionary,int Index);

#endif // Compression_H
