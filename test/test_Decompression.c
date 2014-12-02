#include "unity.h"
#include "Decompression.h"
#include "Dictionary.h"
#include "mock_Stream.h"

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
    
    addDataToDictionary(dict, 97, 0);
    
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    destroyDictionary(dict,3);
}



/*
 * Given data1 = 0a            
 *       data2 = 1b     
 *
 *      Dictionary
 *      0.  a
 *      1.  ab
 *
 */
void test_addDataToDictionary_given_data1_and_data2_when_write_data2_should_merge_a_and_b_together_and_write_into_dictionary_entry1()
{
    Dictionary *dict = initDictionary(3);
        
    addDataToDictionary(dict, 97, 0);
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    
    addDataToDictionary(dict, 98, 1);  
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("ab" ,dict->Entry[1].data);
    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given data1 = 0a            
 *       data2 = 1b
 *       data3 = 2c
 *
 *      Dictionary
 *      0.  a
 *      1.  ab
 *      2.  abc
 *
 */
void test_addDataToDictionary_given_data1_data_2_and_data3_when_write_data3_should_merge_ab_and_c_together_and_write_into_dictionary_entry2()
{
    Dictionary *dict = initDictionary(3);
        
    addDataToDictionary(dict, 97, 0);
    addDataToDictionary(dict, 98, 1);
    addDataToDictionary(dict, 99, 2);
    TEST_ASSERT_EQUAL(3, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("abc" ,dict->Entry[2].data);
    TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given input = 0a0$
 * In binary   = 00000000 00000000      01100001     00000000 00000000      00100100
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *                      0                  a                0                  $
 *      Dictionary
 *      0.  a
 *      1.  $
 *
 */
void test_rebuildDictionaryForDecompression_given_dictionary_size_3_is_larger_than_data_written_should_rebuild_accordingly_and_currentIndex_is_2_and_should_return_0(void)
{
    //Create test fixture
    int status;
	InStream *in;	
    Dictionary *dict = initDictionary(3);    

	//Mock
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 97);
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 36);


	//Run
    status = rebuildDictionaryForDecompression(dict, in);
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("$" ,dict->Entry[1].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[1].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given input = 0a0$
 * In binary   = 00000000 00000000      01100001     00000000 00000000      00100100
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *                      0                  a                0                  $
 *      Dictionary
 *      0.  a
 *
 */
void test_rebuildDictionaryForDecompression_given_dictionary_size_1_is_smaller_than_data_written_should_rebuild_accordingly_and_currentIndex_is_0_and_should_return_1(void)
{
    //Create test fixture
    int status;
	InStream *in;	
    Dictionary *dict = initDictionary(1);    

	//Mock
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 97);


	//Run
    status = rebuildDictionaryForDecompression(dict, in);
    TEST_ASSERT_EQUAL(0, dict->currentIndex);
    TEST_ASSERT_EQUAL(1, status);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    destroyDictionary(dict,3);
}





/*
 * Given input = 0d1A2b2$
 * In binary   = 00000000 00000000      01100100     00000000 00000001      01000001        00000000 00000010   01100010       00000000 00000010    00100100
 *               |               |      |      |     |               |      |      |        |               |   |      |       |               |    |      |
 *                   16bits              8bits            16bits             8bits                16bits         8bits              16bits           8bits
 *                     0                   d                1                  A                   2               b                  2                $
 *      Dictionary
 *      0.  d
 *      1.  dA
 *      2.  dAb
 *      3.  dA$
 *
 */
void test_rebuildDictionaryForDecompression_given_dictionary_size_10_is_larger_than_data_written_should_rebuild_accordingly_currentIndex_is_4_and_should_return_0(void)
{
    // Create test fixture
	InStream *in;	
    int status;
    Dictionary *dict = initDictionary(10);    

	// Mock
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 100);
    streamReadBits_ExpectAndReturn(in, 16, 1);
    streamReadBits_ExpectAndReturn(in, 8, 65);
    streamReadBits_ExpectAndReturn(in, 16, 2);
    streamReadBits_ExpectAndReturn(in, 8, 98);
    streamReadBits_ExpectAndReturn(in, 16, 2);
    streamReadBits_ExpectAndReturn(in, 8, 36);

	// Run
    status = rebuildDictionaryForDecompression(dict, in);
    TEST_ASSERT_EQUAL(4, dict->currentIndex);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL_STRING("d" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL_STRING("dA" ,dict->Entry[1].data);
    TEST_ASSERT_EQUAL(2 ,dict->Entry[1].entrySize);
    TEST_ASSERT_EQUAL_STRING("dAb" ,dict->Entry[2].data);
    TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
    TEST_ASSERT_EQUAL_STRING("dA$" ,dict->Entry[3].data);
    TEST_ASSERT_EQUAL(3 ,dict->Entry[3].entrySize);
    
    destroyDictionary(dict,2);
}





void test_LZ78_Decompressor_given_input_as_shown_should_decompress_correctly()
{







}