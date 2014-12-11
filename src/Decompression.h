#ifndef Decompression_H
#define Decompression_H


#include "Dictionary.h"
#include "Stream.h"
#include "Utility.h"


void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize, int mode);
void LZ78_Decompression_Fixed(InStream *in, OutStream *out, Dictionary *dictionary, char *infilename, char *outfilename, int dictSize);
int AddDataToDictionary(Dictionary *dictionary, unsigned int index, unsigned int data);
void Decompression(OutStream *out, unsigned int index, unsigned int data, Dictionary *dictionary);
unsigned int getVariableIndex(Dictionary *dictionary);





#endif // Decompression_H
