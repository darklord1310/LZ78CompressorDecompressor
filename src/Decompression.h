#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in);
void Decompression(InStream *in, OutStream *out, Dictionary *dictionary);
unsigned int swapUpper16bitsWithLower16bits(unsigned int value);







#endif // Decompression_H
