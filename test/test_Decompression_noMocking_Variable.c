#include "unity.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "Stream.h"
#include <assert.h>

void setUp(void)
{
}

void tearDown(void)
{
}


void test()
{
}



void test_aababc_Compressed_Variable_should_compress_into_aababc()
{
    int dictSize = 4096;
    char *infilename = "test/support/Source/aababc_Compressed_Variable.txt" ;
	char *outfilename = "test/support/Decompressed/Variable/aababc_Compressed_Variable_Decompressed" ;
    
	LZ78_Decompressor(infilename, outfilename, dictSize, Variable);

}



