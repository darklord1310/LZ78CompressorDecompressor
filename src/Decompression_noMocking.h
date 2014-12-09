#ifndef Decompression_noMocking_H
#define Decompression_noMocking_H


#include "Stream.h"
#include "Dictionary.h"
#include "Decompression.h"


int LZ78_Decompressor(char *infilename, char *outfilename, int dictSize);


#endif // Decompression_noMocking_H
