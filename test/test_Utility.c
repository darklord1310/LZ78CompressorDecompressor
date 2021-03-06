#include "unity.h"
#include "Utility.h"
#include <string.h>
#include "malloc.h"
#include "Stream.h"

void setUp(void)
{
}

void tearDown(void)
{
}
/*Value <= dictionaryIndex*/
/*Value <= dictionaryIndex*/
void test_determineNumberOfBitsRequired_given_dictIndex_0_should_return_1()
{
    TEST_ASSERT_EQUAL(1,determineNumberOfBitsRequired(0,0));

}

void test_determineNumberOfBitsRequired_given_dictIndex_1_should_return_1()
{
    TEST_ASSERT_EQUAL(1,determineNumberOfBitsRequired(0,1));

}

void test_determineNumberOfBitsRequired_given_dictIndex_2_should_return_2()
{
    TEST_ASSERT_EQUAL(2,determineNumberOfBitsRequired(0,2));
}

void test_determineNumberOfBitsRequired_given_dictIndex_5_should_return_3()
{
    TEST_ASSERT_EQUAL(3,determineNumberOfBitsRequired(0,5));
}

void test_determineNumberOfBitsRequired_given_dictIndex_8_should_return_4()
{
    TEST_ASSERT_EQUAL(4,determineNumberOfBitsRequired(0,8));
}

void test_determineNumberOfBitsRequired_given_dictIndex_4096_should_return_13()
{
    TEST_ASSERT_EQUAL(13,determineNumberOfBitsRequired(0,4096));
}

/*Value > dictionaryIndex*/
/*Value > dictionaryIndex*/
void test_determineNumberOfBitsRequired_given_value_2_dictIndex_1_should_return_2()
{
    TEST_ASSERT_EQUAL(2,determineNumberOfBitsRequired(2,1));
}


void test_determineNumberOfBitsRequired_given_value_4_dictIndex_2_should_return_3()
{
    TEST_ASSERT_EQUAL(3,determineNumberOfBitsRequired(4,2));
}


void test_renameCompressedFile_given_abc_dot_txt_should_rename_to_abc_dot_LZ()
{
    char *CompressedName;
    char *InfileName = "abc.txt" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("abc.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_noname_should_rename_to_noname_dot_LZ()
{
    char *CompressedName;
    char *InfileName = "noname" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("noname.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_object_dot_o_should_rename_to_object_dot_o()
{
    char *CompressedName;
    char *InfileName = "object.o" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("object.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_Fixed_mode_at_Source_should_change_to_Compressed_Fixed()
{
    char *CompressedName;
    char *InfileName = "test/support/Source/test_LZ78_CompressorDecompressor.txt" ;
    
    CompressedName = calloc(strlen(InfileName)+20,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("test/support/Compressed/Fixed/test_LZ78_CompressorDecompressor.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_Variable_mode_at_Source_should_change_to_Compressed_Variable()
{
    char *CompressedName;
    char *InfileName = "test/support/Source/test_LZ78_CompressorDecompressor.txt" ;
    
    CompressedName = calloc(strlen(InfileName)+20,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName,Variable);
    
    TEST_ASSERT_EQUAL_STRING("test/support/Compressed/Variable/test_LZ78_CompressorDecompressor.LZ",CompressedName);
    
    free(CompressedName);
}
