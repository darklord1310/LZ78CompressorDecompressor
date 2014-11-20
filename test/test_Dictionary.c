#include "unity.h"
#include "Dictionary.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initDictionary_with_size_of_3_should_return_dictionary_with_size_of_3()
{
	Dictionary *dict = initDictionary(3);
    
    TEST_ASSERT_NOT_NULL(dict);
    TEST_ASSERT_NOT_NULL(dict->Entry);
    TEST_ASSERT_NOT_NULL(dict->Entry->data);
    TEST_ASSERT_EQUAL(3, dict->dictionarySize);
    TEST_ASSERT_EQUAL(0, dict->currentIndex);
}



void test_getSizeOfString_given_string_abc_should_return_3()
{
    int length = getSizeOfString("abc");
    
    
    TEST_ASSERT_EQUAL(3, length);
}


void test_getSizeOfString_given_empty_string_should_return_0()
{
    int length = getSizeOfString("");
    
    TEST_ASSERT_EQUAL(0, length);
}



// void test_addEntry_given_string_zzz_should_return_zzz_and_currentIndex_should_point_to_1()
// {

    // Dictionary *dict = initDictionary(3);
    // char *stringReturn = addEntry(dict, "zzz");



// }
