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
    char *a = "ab";
    char b = 'b';
    int hex = 0x40;
    unsigned int result = ( (unsigned int)("ab") << 16) | b;
    printf("%#010x\n",result);


}



// test case when dictionary is not needed to be refresh and all index is only 0
void test_LZ78_Decompressor_given_input_0a0b0c_and_size_of_10_should_decompress_into_abc()
{
    int dictSize = 10;
    char *infilename = "test/support/LZ78decompressor_in_0a0b0c.txt";
    char *outfilename = "test/support/LZ78decompressor_out_0a0b0c.txt";
    
    LZ78_Decompressor(infilename, outfilename, dictSize);

}


// test case when dictionary is needed to be refresh and all index is only 0
void test_LZ78_Decompressor_given_input_0a0b0c_and_size_of_1_should_decompress_into_abc()
{
    int dictSize = 1;
    char *infilename = "test/support/LZ78decompressor_in_0a0b0c.txt";
    char *outfilename = "test/support/LZ78decompressor_out_0a0b0c_refresh.txt";
    
    LZ78_Decompressor(infilename, outfilename, dictSize);

}


// test case when dictionary is not needed to be refresh and index is not only 0
void test_LZ78_Decompressor_given_input_0a1b1a0b2a4_and_size_of_1000_should_decompress_into_aabaababab()
{
    int dictSize = 1000;
    char *infilename = "test/support/LZ78decompressor_in_0a1b1a0b2a4.txt";
    char *outfilename = "test/support/LZ78decompressor_out_0a1b1a0b2a4.txt";
    
    LZ78_Decompressor(infilename, outfilename, dictSize);
}



