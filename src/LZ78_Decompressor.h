#ifndef LZ78_Decompressor_H
#define LZ78_Decompressor_H


#include "Stream.h"
#include "Dictionary.h"
#include "Decompression.h"


int LZ78_Decompressor(char *infilename, char *outfilename, int dictSize);


#endif // Decompression_noMocking_H
