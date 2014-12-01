#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


void addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
int rebuildDictionaryForDecompression(Dictionary *dictionary, InStream *in);
char *Decompression(InStream *in, Dictionary *dictionary);
void LZ78_Decompressor(char *infilename, char *outfilename, char *inmode, char *outmode, Dictionary *dictionary, InStream *in, OutStream *out);








#endif // Decompression_H
