#include "unity.h"
#include "string.h"
#include "Dictionary.h"
#include "stdio.h"
void setUp(void)
{
}

void tearDown(void)
{
}


void test_initDictionary_with_size_of_5_should_return_not_null()
{
	Dictionary **dict = initDictionary(5);

    TEST_ASSERT_NOT_NULL(dict);
    TEST_ASSERT_NOT_NULL(dict[0]);
    TEST_ASSERT_NOT_NULL(dict[1]);
    TEST_ASSERT_NOT_NULL(dict[2]);
    TEST_ASSERT_NOT_NULL(dict[3]);
    TEST_ASSERT_NOT_NULL(dict[4]);
    
    TEST_ASSERT_NULL(dict[5]);
    
    destroyDictionary(dict,5);
}


void test_write_entry_and_sizeofEntry_to_dictionary_should_be_able_to_read_it_Back()
{
    Dictionary **dict = initDictionary(5);

    dict[0]->entry = "A" ;          dict[0]->sizeofEntry = strlen(dict[0]->entry);
    dict[1]->entry = "AB" ;         dict[1]->sizeofEntry = strlen(dict[1]->entry);
    dict[2]->entry = "ABC" ;        dict[2]->sizeofEntry = strlen(dict[2]->entry);
    dict[3]->entry = "abcde";       dict[3]->sizeofEntry = strlen(dict[3]->entry);
    dict[4]->entry = "ABCDE" ;      dict[4]->sizeofEntry = strlen(dict[4]->entry);

    TEST_ASSERT_EQUAL_STRING("A",dict[0]->entry);
    TEST_ASSERT_EQUAL_STRING("AB",dict[1]->entry);
    TEST_ASSERT_EQUAL_STRING("ABC",dict[2]->entry);
    TEST_ASSERT_EQUAL_STRING("abcde",dict[3]->entry);
    TEST_ASSERT_EQUAL_STRING("ABCDE",dict[4]->entry);
    
    TEST_ASSERT_EQUAL(1,dict[0]->sizeofEntry);
    TEST_ASSERT_EQUAL(2,dict[1]->sizeofEntry);
    TEST_ASSERT_EQUAL(3,dict[2]->sizeofEntry);
    TEST_ASSERT_EQUAL(5,dict[3]->sizeofEntry);
    TEST_ASSERT_EQUAL(5,dict[4]->sizeofEntry);
  
    destroyDictionary(dict,5);
}