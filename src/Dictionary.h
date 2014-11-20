#ifndef Dictionary_H
#define Dictionary_H

typedef struct Dictionary Dictionary;
typedef struct DictionaryEntry DictionaryEntry;



struct DictionaryEntry
{
    char *data;         
    int entrySize;      // the size of the data string
};



struct Dictionary
{
    DictionaryEntry **Entry;    // pointer to pointer which point to the DictionaryEntry
    int dictionarySize;         // the size of the dictionary
    int currentIndex;           // the index which the dictionary is pointing to
};


Dictionary *initDictionary(int dictSize);
char *addEntry(Dictionary *dict, char *EntryToAdd);



#endif // Dictionary_H
