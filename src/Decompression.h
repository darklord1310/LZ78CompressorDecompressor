#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"
#include "Decompression_noMocking.h"


void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
void rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in, int *lastDecompressPosition);
void Decompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition);
unsigned int swapUpper16bitsWithLower16bits(unsigned int value);







#endif // Decompression_H
