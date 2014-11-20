#include "unity.h"
#include "Dictionary.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_initDictionary_with_size_of_5_should_return_dictionary_with_size_of_5()
{
	Dictionary *dict = initDictionary(5);
    
    TEST_ASSERT_NOT_NULL(dict);
    TEST_ASSERT_NOT_NULL(&dict[0]);
    TEST_ASSERT_NOT_NULL(&dict[1]);
    TEST_ASSERT_NOT_NULL(&dict[2]);
    TEST_ASSERT_NOT_NULL(&dict[3]);
    TEST_ASSERT_NOT_NULL(&dict[4]);
    destroyDictionary(dict,5);
}
