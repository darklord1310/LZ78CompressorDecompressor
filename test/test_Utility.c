#include "unity.h"
#include "Utility.h"
#include <string.h>
#include "malloc.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_determineNumberOfBitsRequired_given_0_should_return_1()
{
    TEST_ASSERT_EQUAL(1,determineNumberOfBitsRequired(0));

}

void test_determineNumberOfBitsRequired_given_1_should_return_1()
{
    TEST_ASSERT_EQUAL(1,determineNumberOfBitsRequired(1));

}

void test_determineNumberOfBitsRequired_given_2_should_return_2()
{
    TEST_ASSERT_EQUAL(2,determineNumberOfBitsRequired(2));
}

void test_determineNumberOfBitsRequired_given_5_should_return_3()
{
    TEST_ASSERT_EQUAL(3,determineNumberOfBitsRequired(5));
}

void test_determineNumberOfBitsRequired_given_8_should_return_4()
{
    TEST_ASSERT_EQUAL(4,determineNumberOfBitsRequired(8));
}

void test_renameCompressedFile_given_abc_dot_txt_should_rename_to_abc_dot_LZ()
{
    char *CompressedName;
    char *InfileName = "abc.txt" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName);
    
    TEST_ASSERT_EQUAL_STRING("abc.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_noname_should_rename_to_noname_dot_LZ()
{
    char *CompressedName;
    char *InfileName = "noname" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName);
    
    TEST_ASSERT_EQUAL_STRING("noname.LZ",CompressedName);
    
    free(CompressedName);
}

void test_renameCompressedFile_given_object_dot_o_should_rename_to_object_dot_o()
{
    char *CompressedName;
    char *InfileName = "object.o" ;
    
    CompressedName = calloc(strlen(InfileName)+4,sizeof(char));
    
    renameCompressedFile(InfileName,CompressedName);
    
    TEST_ASSERT_EQUAL_STRING("object.LZ",CompressedName);
    
    free(CompressedName);
}