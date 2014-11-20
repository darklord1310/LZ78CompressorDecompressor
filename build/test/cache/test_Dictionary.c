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



    if ((((dict)) != ((void *)0))) {} else {UnityFail( (" Expected Non-NULL"), (_U_UINT)(_U_UINT)(_U_UINT)16);;};

    UnityAssertEqualNumber((_U_SINT)((3)), (_U_SINT)((dict->dictionarySize)), (((void *)0)), (_U_UINT)17, UNITY_DISPLAY_STYLE_INT);

    UnityAssertEqualNumber((_U_SINT)((0)), (_U_SINT)((dict->currentIndex)), (((void *)0)), (_U_UINT)18, UNITY_DISPLAY_STYLE_INT);

}
