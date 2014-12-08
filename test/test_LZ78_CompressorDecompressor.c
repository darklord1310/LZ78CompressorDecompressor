#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "unity.h"
#include "LZ78_CompressorDecompressor.h"
#include "Stream.h"
#include "Compression.h"
#include "Decompression_noMocking.h"
#include "Decompression.h"
#include "Dictionary.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_LZ78_CompressorDecompressortest_LZ78_CompressorDecompressor_txt(void)
{
	char *InfileName = "test/support/test_LZ78_CompressorDecompressor.txt" ;
	char *OutfileName = "test/support/test_LZ78_CompressorDecompressor_Decompressed.txt" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,5,Fixed);
}

void test_LZ78_CompressorDecompressor_README(void)
{
	char *InfileName = "test/support/README" ;
	char *OutfileName = "test/support/README_Decompressed" ;
	LZ78_CompressorDecompressor(InfileName,OutfileName,4096,Fixed);
}