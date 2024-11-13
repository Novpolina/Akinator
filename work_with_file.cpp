#include <iostream> // TODO ???
#include <stdio.h>
#include <sys/stat.h>
#include "work_with_file.h"

void PrintFile(text onegin){
    // TODO onegin.number_of_strings is size_t, incorrect specifier
    printf("\nText %i:\n", onegin.number_of_strings);

    for(size_t i = 0; i < onegin.number_of_strings; i++){
        printf("%s", onegin.strs_data[i].string_pointer);
        // TODO string_length is size_t, incorrect specifier
        printf("%i \n", onegin.strs_data[i].string_length);

    }
    printf("\nEnd of Text:\n\n\n\n");
}

int CountStrings(text onegin){
    bool is_str_new = true;
    int number_of_strings = 0;

    // TODO why using a flag here? Strang algorythm
    for(size_t i = 0; i < onegin.number_of_symbols; i++){
        if(is_str_new == true){
            number_of_strings++;
            is_str_new = false;
        }

        if (onegin.buffer[i] == '['){
            is_str_new = true;

        }
    }
    return number_of_strings;
}

void DestructText(text* tree){
    free(tree->buffer);
    free(tree->strs_data);
}

 text ReadTextFromFile (FILE * file_with_text, text onegin) {
    struct stat finfo;
    fstat(fileno(file_with_text), &finfo);

    //printf("uhbigvfuc");
    //file_with_text = fopen("Mockingbird.txt", "rb");
    // TODO why ints again?
    onegin.number_of_symbols = (int)finfo.st_size/sizeof(char);

    onegin.buffer = (char *)calloc(onegin.number_of_symbols, sizeof(char));


    fread(onegin.buffer, sizeof(char), onegin.number_of_symbols,file_with_text);

    onegin.number_of_strings = CountStrings(onegin);
    onegin.strs_data = (strings*)calloc(onegin.number_of_strings, sizeof(strings));

    int j = 0;

    bool is_str_new = true;

    printf("\n%i\n", onegin.number_of_symbols);

    for (size_t i = 0; i < onegin.number_of_symbols; i++){

        if(is_str_new == true){
            onegin.strs_data[j].string_pointer = &onegin.buffer[i];
            j++;
            is_str_new = false;
        }

        if(onegin.buffer[i] == '['){
            onegin.buffer[i] = '[';
            is_str_new = true; 
        }

        onegin.strs_data[j-1].string_length++;

    }
    //PrintFile(onegin);
    return onegin;


}