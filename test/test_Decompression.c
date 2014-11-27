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
    
    int status;
    status = addDataToDictionary(dict, 97, 0);
    
    TEST_ASSERT_EQUAL(1, status);                       //write successfully
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
    int status;
        
    status = addDataToDictionary(dict, 97, 0);
    TEST_ASSERT_EQUAL(1, status);                   //write successfully
    TEST_ASSERT_EQUAL(1, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    
    
    status = addDataToDictionary(dict, 98, 1);  
    TEST_ASSERT_EQUAL(1, status);                   //write successfully
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
    int status;
        
    status = addDataToDictionary(dict, 97, 0);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    
    status = addDataToDictionary(dict, 98, 1);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    
    status = addDataToDictionary(dict, 99, 2);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    TEST_ASSERT_EQUAL(3, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("abc" ,dict->Entry[2].data);
    TEST_ASSERT_EQUAL(3 ,dict->Entry[2].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given data1 = 0a            
 *       data2 = 1b
 *       data3 = 2c
 *       data4 = 0d
 *
 *      Dictionary
 *      0.  a
 *      1.  ab
 *      2.  abc
 *      
 *      Should not add data4 into dictionary because dictionary already full
 */
void test_addDataToDictionary_given_data1_data2_data3_and_data4_when_write_data4_should_not_write_into_dictionary_and_should_return_0()
{
    Dictionary *dict = initDictionary(3);
    int status;
        
    status = addDataToDictionary(dict, 97, 0);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    
    status = addDataToDictionary(dict, 98, 1);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    
    status = addDataToDictionary(dict, 99, 2);
    TEST_ASSERT_EQUAL(1, status);               //write successfully
    
    status = addDataToDictionary(dict, 100, 0);
    TEST_ASSERT_EQUAL(0, status);
    TEST_ASSERT_EQUAL(3, dict->currentIndex);
    
    
    destroyDictionary(dict,3);
}



/*
 * Given input = 0a0$
 * In binary   = 00000000 00000000      01100001     00000000 00000000      01000100
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *      Dictionary
 *      0.  a
 *      1.  $
 *
 */
void xtest_rebuildDictionaryForDecompression_given_dictionary_size_3_should_rebuild_accordingly_and_return_0(void)
{
    int status;
        
    //Create test fixture
	InStream *in;	
    Dictionary *dict = initDictionary(3);    

	//Mock
    initInStream_ExpectAndReturn(in);
    openInStream_ExpectAndReturn("test_streamReadBit.txt", "rb" , in, in);
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 97);
    streamReadBits_ExpectAndReturn(in, 16, 0);
    streamReadBits_ExpectAndReturn(in, 8, 36);

	//Run
    in = initInStream();
    status = rebuildDictionaryForDecompression("test_streamReadBit.txt", "rb", dict, in);
    TEST_ASSERT_EQUAL(0, status);                       //because dictionary haven't full
    TEST_ASSERT_EQUAL(2, dict->currentIndex);
    TEST_ASSERT_EQUAL_STRING("a" ,dict->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("$" ,dict->Entry[1].data);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    TEST_ASSERT_EQUAL(1 ,dict->Entry[1].entrySize);
    
    destroyDictionary(dict,3);
}




/*
 * Given input = 0d0$
 * In binary   = 00000000 00000000      01100100     00000000 00000000      01000100
 *               |               |      |      |     |               |      |      |
 *                   16bits              8bits            16bits             8bits
 *      Dictionary
 *      0.  d
 *      1.  $
 *
 */
void xtest_rebuildDictionaryForDecompression_given_dictionary_size_2_should_rebuild_accordingly_and_return_1(void)
{
    // int status;
        
    //Create test fixture
	// InStream *in;	
    // Dictionary *dict = initDictionary(2);    

	//Mock
    // initInStream_ExpectAndReturn(in);
    // openInStream_ExpectAndReturn("test_streamReadBit.txt", "rb" , in, in);
    // streamReadBits_ExpectAndReturn(in, 16, 0);
    // streamReadBits_ExpectAndReturn(in, 8, 100);
    // streamReadBits_ExpectAndReturn(in, 16, 0);
    // streamReadBits_ExpectAndReturn(in, 8, 36);

	//Run
    // in = initInStream();
    // status = rebuildDictionaryForDecompression("test_streamReadBit.txt", "rb", dict, in);
    // TEST_ASSERT_EQUAL(1, status);                       //because dictionary already full
    // TEST_ASSERT_EQUAL(2, dict->currentIndex);
    // TEST_ASSERT_EQUAL_STRING("d" ,dict->Entry[0].data);
    // TEST_ASSERT_EQUAL_STRING("$" ,dict->Entry[1].data);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[0].entrySize);
    // TEST_ASSERT_EQUAL(1 ,dict->Entry[1].entrySize);
    
    
    // destroyDictionary(dict,2);
}