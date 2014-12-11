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
void test_LZ78_Decompression_given_input_0a0b0c_and_size_of_10_should_decompress_into_abc()
{
    int status, dictSize = 1000;
    char *infilename = "test/support/assignment 2(latest).cpp_Compressed";
    char *outfilename = "test/support/testing.txt";
    Dictionary *dict;
    InStream *in;
    OutStream *out;
    
    status = LZ78_Decompression(in, out, dict, infilename, outfilename, dictSize);
    TEST_ASSERT_EQUAL(1, status);

}



