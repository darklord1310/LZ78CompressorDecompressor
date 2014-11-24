#include "unity.h"
#include "Decompression.h"

void setUp(void)
{
}

void tearDown(void)
{

}




/*
 * Given data = 01100001    (97)
 *
 *      Dictionary
 *      0.  a
 *
 */
void test_addDataToDictionary_given_binary_97_should_write_a_into_dictionary_entry0()
{
    Dictionary *dict = initDictionary(3);

    int status = addDataToDictionary(dict, 97);

    TEST_ASSERT_EQUAL(1, status);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
}



/*
 * Given input = 0a0$
 * In binary   = 00000000 00000000      01100001     00000000 00000000      01000100
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *      Dictionary
 *      1.  a
 *      2.  $
 *
 */
void xtest_rebuildDictionaryForDecompression_given_dictionary_should_rebuild_accordingly(void)
{
    //Create test fixture
	// InStream *in;							

	//Mock
    // initInStream_ExpectAndReturn(in);
    // openInStream_ExpectAndReturn("test_streamReadBit.txt", "rb" , in);

	//Run


}
