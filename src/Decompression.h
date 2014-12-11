#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"


void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize);
void LZ78_Decompression(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize);
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data);
void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary);






#endif // Decompression_H
