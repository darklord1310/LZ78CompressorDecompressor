#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in);
void Decompression(InStream *in, OutStream *out, Dictionary *dictionary);
void LZ78_Decompressor(char *infilename, char *outfilename, Dictionary *dictionary);








#endif // Decompression_H
