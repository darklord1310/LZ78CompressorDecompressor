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
    freeOutStream(out);

}

