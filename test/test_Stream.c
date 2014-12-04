#include "unity.h"
#include "Stream.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}


void test_initInStream_should_malloc_correctly(void)
{
    InStream *in = initInStream();
    TEST_ASSERT_NOT_NULL(in);
	TEST_ASSERT_EQUAL(0, in->bitIndex);
	TEST_ASSERT_EQUAL(0, in->byteToRead);
    freeInStream(in);
}


void test_initOutStream_should_malloc_correctly(void)
{
    OutStream *out = initOutStream();
    TEST_ASSERT_NOT_NULL(out);
	TEST_ASSERT_EQUAL(0, out->bitIndex);
	TEST_ASSERT_EQUAL(0, out->byteToWrite);
    freeOutStream(out);
}


void test_openInStream_open_a_text_file_available_should_not_throw_error(void)
{
    CEXCEPTION_T ERR;
    
    InStream *in = initInStream();
    
    Try
	{
        in = openInStream("test/support/test_in.txt", "rb" , in);
        TEST_ASSERT_NOT_NULL(in);
        TEST_ASSERT_NOT_NULL(in->file);
        TEST_ASSERT_EQUAL("test/support/test_in.txt", in->filename);
    }
    Catch(ERR){
        TEST_ASSERT_EQUAL(ERR_FAILED_TO_OPEN, ERR);
		printf("File not exist!\n");
    }
    closeInStream(in);
    freeInStream(in);
}


// abc is not existed
void test_openInStream_open_a_text_file_unavailable_should_throw_error(void)
{
    CEXCEPTION_T ERR;
    
    InStream *in = initInStream();
    
    Try
	{
        in = openInStream("test/support/abc.txt", "rb" , in);

    }
    Catch(ERR){
        TEST_ASSERT_EQUAL(ERR_FAILED_TO_OPEN, ERR);
		printf("File not exist!\n");
    }
    freeInStream(in);
}



void test_openOutStream_should_open_file_successfully(void)
{
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/zzz.txt", "rb" , out);
    TEST_ASSERT_NOT_NULL(out);
    TEST_ASSERT_NOT_NULL(out->file);
    TEST_ASSERT_EQUAL("test/support/zzz.txt", out->filename);
    closeOutStream(out);
    freeOutStream(out);

}

void xtest_streamWriteBit_1time_given_input_1_should_write_1_to_byteToWrite_and_increment_bitIndex_to_1()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    freeOutStream(out);
}

void xtest_streamWriteBit_2time_given_input_1_0_should_write_1_0_to_byteToWrite_and_increment_bitIndex_to_2()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(2,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    freeOutStream(out);
}

void xtest_streamWriteBit_3time_given_input_1_0_1_should_write_1_0_1_to_byteToWrite_and_increment_bitIndex_to_3()
{
    OutStream *out = initOutStream();
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(1,out->byteToWrite);
    TEST_ASSERT_EQUAL(1,out->bitIndex);
    
    streamWriteBit(out,0);
    
    TEST_ASSERT_EQUAL(2,out->byteToWrite);
    TEST_ASSERT_EQUAL(2,out->bitIndex);
    
    streamWriteBit(out,1);
    
    TEST_ASSERT_EQUAL(5,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
       
    freeOutStream(out);
}

void xtest_streamWriteBits_given_value_8_bitSize_3_should_write_0_to_byteToWrite_return_bitIndex_3()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,3);

    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(3,out->bitIndex);
    
    freeOutStream(out);
    
}

void xtest_streamWriteBits_given_value_8_bitSize_4_should_write_8_to_byteToWrite_return_bitIndex_4()
{
    OutStream *out = initOutStream();
    
    streamWriteBits(out,8,4);

    TEST_ASSERT_EQUAL(8,out->byteToWrite);
    TEST_ASSERT_EQUAL(4,out->bitIndex);
    
    freeOutStream(out);
}

void xtest_streamWriteBits_given_A_bitSize_8_should_flush_A_during_closeOutStream()
{
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits.txt", "wb" , out);
    
    streamWriteBits(out,'A',8);
    
    TEST_ASSERT_EQUAL('A',out->byteToWrite);
    TEST_ASSERT_EQUAL(8,out->bitIndex);
    
    closeOutStream(out);
   
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(out);
}


void xtest_streamWriteBits_given_ABCDEFGH_bitSize_64_should_flush_ABCDEFGH()
{
    char *string = "ABCDEFGH" ;
    
    int i ;
    OutStream *out = initOutStream();
    
    out = openOutStream("test/support/test_streamWriteBits_1.txt", "wb" , out);

    for( i = 0 ; i < strlen(string) ; i ++ )
        streamWriteBits(out,string[i],8);

    closeOutStream(out);
    
    TEST_ASSERT_EQUAL(0,out->byteToWrite);
    TEST_ASSERT_EQUAL(0,out->bitIndex);
    
    freeOutStream(out);
}


