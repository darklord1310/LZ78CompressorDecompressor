#ifndef Dictionary_H
#define Dictionary_H

typedef struct Dictionary Dictionary;

struct Dictionary
{
    char *entry ;
    int sizeofEntry ;
};

Dictionary *initDictionary(int dictSize);
void destroyDictionary(Dictionary *dictionary,int dictSize);
#endif // Dictionary_H
