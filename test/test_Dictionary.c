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


void test_initDictionary_with_size_of_3_should_return_dictionary_with_size_of_3()
{
	Dictionary *dict = initDictionary(3);
    
    TEST_ASSERT_NOT_NULL(dict);
    TEST_ASSERT_NOT_NULL(dict->Entry);
    TEST_ASSERT_NOT_NULL(dict->Entry->data);
    TEST_ASSERT_EQUAL(3, dict->dictionarySize);
    TEST_ASSERT_EQUAL(0, dict->currentIndex);
    
    destroyDictionary(dict,3);
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

void test_writing_Data_to_DictionaryEntry_should_able_to_read_them_out()
{
    Dictionary *dict = initDictionary(3);
    
    dict->Entry[0].data = "A" ; dict->Entry[0].entrySize = getSizeOfString(dict->Entry[0].data) ;
    dict->Entry[1].data = "AB" ; dict->Entry[1].entrySize = getSizeOfString(dict->Entry[1].data) ;
    dict->Entry[2].data = "ABC" ; dict->Entry[2].entrySize = getSizeOfString(dict->Entry[2].data) ;
    
    TEST_ASSERT_EQUAL_STRING("A",dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AB",dict->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("ABC",dict->Entry[2].data);
    
    TEST_ASSERT_EQUAL(1,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL(2,dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL(3,dict->Entry[2].entrySize);
    
    destroyDictionary(dict,3);
}

void test_isDictionaryFull_given_currentIndex_3_dicionary_size_3_should_return_1_for_full_dictionary()
{
    Dictionary *dict = initDictionary(3);
    
    dict->currentIndex = 3 ;
    
    TEST_ASSERT_EQUAL(1,isDictionaryFull(dict));
    
    destroyDictionary(dict,3);
} 

void test_isDictionaryFull_given_currentIndex_2_dicionary_size_3_should_return_0_for_not_full_dictionary()
{
    Dictionary *dict = initDictionary(3);
    
    dict->currentIndex = 2 ;
    
    TEST_ASSERT_EQUAL(0,isDictionaryFull(dict));
    
    destroyDictionary(dict,3);
} 

void test_addEntry_given_string_zzz_should_return_1_and_currentIndex_should_point_to_1()
{
    Dictionary *dict = initDictionary(3);
    
    TEST_ASSERT_EQUAL(1,addEntryData(dict, "zzz"));
    
    TEST_ASSERT_EQUAL(1,dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("zzz",dict->Entry[0].data);

    destroyDictionary(dict,3);
}

void test_addEntry_given_string_a_currentIndex_3_should_return_0_for_failure_to_add_and_dictionary_is_full()
{
    Dictionary *dict = initDictionary(3);
    dict->currentIndex = 3 ;
    
    TEST_ASSERT_EQUAL(0,addEntryData(dict, "a"));
    

    destroyDictionary(dict,3);
}