#ifndef CustomAssertions_H
#define CustomAssertions_H
#include "Stream.h"

#define TEST_ASSERT_EQUAL_FILE(Source,Target) assertFile(Source,Target,__LINE__)

void assertFile(char *Source, char *Target,int lineNumber);

#endif // CustomAssertions_H
