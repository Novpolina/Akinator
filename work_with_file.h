 #include <stdlib.h>
#include <stdio.h>

// TODO this is a string not stringS
struct strings{
    char* string_pointer;
    int string_length;

};


struct text{
    size_t number_of_symbols;
    size_t number_of_strings;
    //char** text_pointers_with_no_sort;
    //char** text_pointers;
    strings* strs_data;

    char* buffer;
};

 text ReadTextFromFile(FILE * file_with_text, text onegin);
 void PrintFile(text onegin);
 void DestructText(text* tree);
