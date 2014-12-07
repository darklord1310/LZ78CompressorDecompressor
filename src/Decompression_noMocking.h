#ifndef Decompression_noMocking_H
#define Decompression_noMocking_H


#include "Stream.h"
#include "Dictionary.h"
#include "Decompression.h"


void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize);
void finalDecompression(InStream *in, OutStream *out, Dictionary *dictionary, int *lastDecompressPosition, int lastDictionaryLocation);
int finalrebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in, int *lastDecompressPosition, int lastDictionaryLocation);




#endif // Decompression_noMocking_H
