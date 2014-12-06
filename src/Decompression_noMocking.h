#ifndef Decompression_noMocking_H
#define Decompression_noMocking_H


#include "Decompression.h"
#include "Stream.h"
#include "Dictionary.h"

int getPositionInFile(InStream *in);
void LZ78_Decompressor(char *infilename, char *outfilename, int dictSize);





#endif // Decompression_noMocking_H
