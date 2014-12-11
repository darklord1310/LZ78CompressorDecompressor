#ifndef LZ78_CompressorDecompressor_H
#define LZ78_CompressorDecompressor_H

#include "Stream.h"
#include "Compression.h"
#include "Decompression.h"

void LZ78_CompressorDecompressor(char *InfileName,char *OutfileName,int dictSize,int mode);
void renameCompressedFile(char *InfileName,char *CompressedName);
#endif // LZ78_CompressorDecompressor_H
