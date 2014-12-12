#include "unity.h"
#include "Utility.h"
#include <string.h>
#include "Dictionary.h"
#include "Compression.h"
#include "Stream.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBB
 * Fixed mode
 * Compressed output -> 1A2A3A4 1B6B7B8  
 *
 */


void test_LZ78_Compression_fixed_mode_given_input_file_sampleText_forCompresssion()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/Source/sampleText_forCompresssion.txt", "rb" , in);
    out = openOutStream("test/support/Compressed/Fixed/sampleText_forCompresssion.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Fixed);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[7].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}


/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBB
 * Variable mode
 * Compressed output -> 1A2A3A4 1B6B7B8 
 * 
 */

void test_LZ78_Compression_Variable_mode_given_input_file_sampleText_forCompresssion()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/Source/sampleText_forCompresssion.txt", "rb" , in);
    out = openOutStream("test/support/Compressed/Variable/sampleText_forCompresssion_Compressed_Variable.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[7].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}

/*sampleText_forCompresssion -> AAAAAAAAA BBBBBBBBBBC
 * Variable mode
 * Compressed output -> 1A2A3A4 1B6B7B8B1C0
 * 
 */

void test_LZ78_Compression_Variable_mode_given_input_file_sampleText_forCompresssion_2()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(100);
    
    in = openInStream("test/support/Source/sampleText_forCompresssion_2.txt", "rb" , in);
    out = openOutStream("test/support/Compressed/Variable/sampleText_forCompresssion_Compressed_Variable_2.txt", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);
    
    TEST_ASSERT_EQUAL_STRING("A",dictionary->Entry[0].data);
    TEST_ASSERT_EQUAL_STRING("AA",dictionary->Entry[1].data);
    TEST_ASSERT_EQUAL_STRING("AAA",dictionary->Entry[2].data);
    TEST_ASSERT_EQUAL_STRING("AAA ",dictionary->Entry[3].data);
    TEST_ASSERT_EQUAL_STRING("B",dictionary->Entry[4].data);
    TEST_ASSERT_EQUAL_STRING("BB",dictionary->Entry[5].data);
    TEST_ASSERT_EQUAL_STRING("BBB",dictionary->Entry[6].data);
    TEST_ASSERT_EQUAL_STRING("BBBB",dictionary->Entry[7].data);
    TEST_ASSERT_EQUAL_STRING("C",dictionary->Entry[8].data);
    TEST_ASSERT_EQUAL_STRING("",dictionary->Entry[9].data);
    
    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,100);
}

void test_LZ78_Compression_Variable_mode_given_input_file_README()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/Source/README", "rb" , in);
    out = openOutStream("test/support/Compressed/Variable/README_Compressed_Variable", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}

void test_LZ78_Compression_Variable_mode_given_input_file_StringObject_o()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/Source/StringObject.o", "rb" , in);
    out = openOutStream("test/support/Compressed/Variable/StringObject_Compressed_Variable.o", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}

void test_LZ78_Compression_Variable_mode_given_input_file_libjansson_4_dll_()
{
    InStream *in = initInStream();
    OutStream *out = initOutStream();
    Dictionary *dictionary = initDictionary(4096);
    
    in = openInStream("test/support/Source/libjansson-4.dll", "rb" , in);
    out = openOutStream("test/support/Compressed/Variable/libjansson-4_Compressed_Variable.dll", "wb" , out);
      
    LZ78_Compressor(dictionary,in,out,Variable);

    closeInStream(in);
    closeOutStream(out);
    freeInStream(in);
    freeOutStream(out);
    destroyDictionary(dictionary,4096);
}
