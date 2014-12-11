#include "unity.h"
#include "LZ78_CompressorDecompressor.h"
#include "Stream.h"
#include "Compression.h"
#include "Decompression.h"
#include "Dictionary.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void xtest_LZ78_CompressorDecompressortest_LZ78_CompressorDecompressor_txt(void)
{
	char *InfileName = "test/support/test_LZ78_CompressorDecompressor.txt" ;
	char *OutfileName = "test/support/test_LZ78_CompressorDecompressor_Decompressed.txt" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,5,Fixed);
}

void xtest_LZ78_CompressorDecompressor_README(void)
{
	char *InfileName = "test/support/README" ;
	char *OutfileName = "test/support/README_Decompressed" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,4096,Fixed);
}


void xtest_LZ78_CompressorDecompressor_libjansson_4_dll(void)
{
	char *InfileName = "test/support/libjansson-4.dll" ;
	char *OutfileName = "test/support/libjansson-4.dll_Decompressed" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,4096,Fixed);
}


void xtest_LZ78_CompressorDecompressor_StringObject(void)
{
	char *InfileName = "test/support/StringObject.o" ;
	char *OutfileName = "test/support/StringObject_Decompressed.o" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,4096,Fixed);
}

void testing()
{
    char *InfileName = "test/support/assignment 2(latest).cpp" ;
	char *OutfileName = "test/support/assignment 2(latest)_Decompressed" ;
    int dictSize = 4096;
    
    LZ78_CompressorDecompressor(InfileName,OutfileName, dictSize, Fixed);

}