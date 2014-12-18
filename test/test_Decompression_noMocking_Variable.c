#include "unity.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "Stream.h"
#include "Utility.h"
#include <assert.h>
#include "CustomAssertions.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test()
{
}


// test case when dictionary is not needed to be refresh 
void test_aababc_Compressed_Variable_given_dictionary_size_4096_should_compress_into_aababc()
{
    int dictSize = 4096;
    char *infilename = "test/support/Source/aababc_Compressed_Variable.txt" ;
	char *outfilename = "test/support/Decompressed/Variable/aababc_Compressed_Variable_Decompressed" ;
    
	LZ78_Decompressor(infilename, outfilename, dictSize, Variable);
    TEST_ASSERT_EQUAL_FILE("test/support/Source/aababc.txt", outfilename);
    
}


// test case when dictionary is needed to be refresh 
void test_aababc_Compressed_Variable_given_dictionary_size_2_should_compress_into_aababc()
{
    int dictSize = 2;
    char *infilename = "test/support/Source/aababc_Compressed_Refresh_Variable.txt" ;
	char *outfilename = "test/support/Decompressed/Variable/aababc_Compressed_Refresh_Variable_Decompressed" ;
    
	LZ78_Decompressor(infilename, outfilename, dictSize, Variable);
    TEST_ASSERT_EQUAL_FILE("test/support/Source/aababc.txt", outfilename);

}