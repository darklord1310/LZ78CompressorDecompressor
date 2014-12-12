#ifndef Utility_H
#define Utility_H

typedef enum { Fixed,
               Variable    
             } Mode;
             
int determineNumberOfBitsRequired(int index) ;
void renameCompressedFile(char *InfileName,char *CompressedName,int mode);
#endif // Utility_H
