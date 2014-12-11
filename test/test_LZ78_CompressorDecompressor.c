#include "unity.h"
#include "LZ78_CompressorDecompressor.h"
#include "Stream.h"
#include "Compression.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "malloc.h"
#include "Utility.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LZ78_CompressorDecompressortest_LZ78_CompressorDecompressor_txt(void)
{
	char *InfileName = "test/support/Source/test_LZ78_CompressorDecompressor.txt" ;
	char *OutfileName = "test/support/Decompressed/Fixed/test_LZ78_CompressorDecompressor_Decompressed.txt" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName, 4096,Fixed);
}

void test_LZ78_CompressorDecompressor_README(void)
{
	char *InfileName = "test/support/Source/README" ;
	char *OutfileName = "test/support/Decompressed/Fixed/README_Decompressed" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName, 1 ,Fixed);
}

void test_LZ78_CompressorDecompressor_libjansson_4_dll(void)
{
	char *InfileName = "test/support/Source/libjansson-4.dll" ;
	char *OutfileName = "test/support/Decompressed/Fixed/libjansson-4_Decompressed.dll" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,1000,Fixed);
}

void test_LZ78_CompressorDecompressor_StringObject(void)
{
	char *InfileName = "test/support/Source/StringObject.o" ;
	char *OutfileName = "test/support/Decompressed/Fixed/StringObject_Decompressed.o" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,1,Fixed);
}



