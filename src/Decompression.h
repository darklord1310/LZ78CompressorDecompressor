#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


char convertIntToChar(unsigned int inputdata);
int addDataToDictionary(Dictionary *dictionary, unsigned int data, unsigned int index);
int rebuildDictionaryForDecompression(char *filename, char *mode, Dictionary *dictionary, InStream *in);
void LZ78_Decompressor(char *infilename, char *outfilename, char *inmode, char *outmode, Dictionary *dictionary, InStream *in, OutStream *out);










#endif // Decompression_H
