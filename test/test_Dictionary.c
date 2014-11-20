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
    TEST_ASSERT_EQUAL(3, dict->dictionarySize);
    TEST_ASSERT_EQUAL(0, dict->currentIndex);
}
