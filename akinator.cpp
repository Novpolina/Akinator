#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <sys/stat.h>
//#include "work_with_file.h"

#include "akinator.h"

int YES = 10;
int NO = -10;

const char* AKINATOR = "акинатор";
const char* FIND = "признаки";
const char* COMPARE = "сравнение";


struct string{
    char* str_pointer;
    size_t str_length;
};

static string read_str_from_buff(char* buff);
void ReadTree(node_t** node, char** bufer);
bool FindPathInTree(node_t* node, char* word, int  i, int* a);
void WritePath(node_t* node, int* a, int i, int start, int end);
void read_string(char * str);
int CheckAnswer(char* answer);
void ContinueGame(node_t* node);


node_t* CreateNode(char* value){

    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node->data = (char*)calloc(100, sizeof(char));
    strcpy(node->data, value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void game (node_t * node){
    printf("утра доброго, чего хочешь поделать? \n если позагадывать слова, напиши \"акинатор\" \n если получить инфу об элементе, напиши \"признаки\" \n если сравнить два элемента, \"сравнение\"\n");

    char answer[100] ={};
    read_string(answer);
    if(!strcasecmp(answer, AKINATOR)){
        Akinator(node);
        ContinueGame(node);
    }
    else if(!strcasecmp(answer, FIND)){
        char word[100] = {};
        printf("Напиши слово \n");
        read_string(word);
        FindPathToWord(node, word);
        ContinueGame(node);
    }
    else if(!strcasecmp(answer, COMPARE)){
        char word1[100] = {};
        char word2[100] = {};
        printf("Напиши первое слово \n");
        read_string(word1);
        printf("Напиши второе слово \n");
        read_string(word2);

        CompareWords(node, word1, word2);
        ContinueGame(node);
    }
    else{
        printf("Wrong command!! \n");
        game(node);
    }
    



}
void ContinueGame(node_t* node){
    char answer[100] = {};

    printf("Хочешь продолжить? \n");

    read_string(answer);

    if(CheckAnswer(answer) == YES){
        game(node);
    }
    else if(CheckAnswer(answer) == NO){
        printf("До свидания всего доброго \n \n");
        return;
    }


}

void InsertNewElemInTree(char* elem, char* question, node_t* node){

    node_t * left_node = CreateNode(node->data);
    node_t * right_node = CreateNode(elem);
    strcpy(node->data, question);
    node->left = left_node;
    node->right = right_node;

}

void read_string(char * str) {
    // while (getc(stdin) != '\n')
    //         ;
    // Выделяем память для строки (например, 100 символов)
    size_t size = 100;
    //char *str = (char *)malloc(size * sizeof(char));
    
    if (str == NULL) {
        fprintf(stderr, "\nОшибка выделения памяти\n");
        exit(1);
    }
    
    // Считываем строку, включая пробелы
    if (fgets(str, size, stdin) != NULL) {
        // Удаляем символ новой строки, если он есть
        size_t len = strlen(str);
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    } else {
        fprintf(stderr, "\nОшибка считывания строки\n");
        free(str);
        exit(1);
    }

}

void InsertNewQuestion(node_t *node){
    char new_elem[100] = {};
    char question[100] = {};
    printf("Напиши слово, которое загадал \n");
    read_string(new_elem);
    printf("Напиши признак, который отличает это слово от моего\n");
    read_string(question);
    InsertNewElemInTree(new_elem, question, node);

    
}

// void Insert(node_t* node, char* value){

//     if(value < node->data){
//         if(node->left == NULL){
//             node->left = CreateNode(value);
//         }
//         else{
//             Insert(node->left, value);
//         }
//     }
//     else{
//         if(node->right == NULL){
//             node->right = CreateNode(value);
//         }
//         else{
//             Insert(node->right, value);
//         }
//     }
// }

void Print (node_t* node){
    if(node == NULL) return;

    printf("(");
    printf("%s", node->data);

    if(node->left) Print (node->left);
     //printf(")");
    if(node->right) Print(node->right);
    //printf("%d", node->data);

    printf(")");


}

int CheckAnswer(char* answer){
    int res = 0;
    while(res == 0){

        if(strcasecmp("да", answer) == 0){
            res = YES;
        }
        else if(strcasecmp("нет", answer) == 0){
            res = NO;
        }
        else{
            printf("На русском нормально ответ напиши \n");
            read_string(answer);

        }

    }
    return res;


}

void Akinator(node_t* node){
    char answer[100] = {};//(char*)calloc(100, sizeof(char));

    if(node->left == NULL || node->right == NULL){
        printf("Твое слово %s?\n", node->data);
        read_string(answer);
        int res = CheckAnswer(answer);

        if( res == YES){
            printf("Zayebis \n");
        }
        else if(res == NO){
            InsertNewQuestion(node);
        }
        else{
            printf("Ошибка \n");

        }
        
    }
    else{
        printf("%s?\n", node->data);
        read_string(answer);

        int res = CheckAnswer(answer);

        if(res == YES){
            Akinator(node->right);
        }


        else if(res == NO){
            Akinator(node->left);
        }
        else{
            printf("Ошибка \n");
            

        }
    
    }
    // free(answer);
}

void DestructNode(node_t* node){
    assert(node);
    if(node->left) DestructNode(node->left);
    if(node->right) DestructNode(node->right);
    free(node->data);
    free(node);
}

void write_dot(node_t* node, FILE* file) {

    if (node == NULL) {
        return;
    }

    if(node->left == 0 || node->right == 0){
        fprintf(file, "\tnode_%d [shape = Mrecord, color = white, label=\"{%s}\"];\n", node, node->data);

    }

    else{
        fprintf(file, "\tnode_%d [shape = Mrecord, color = white, label=\"{{%s} | {<f1> Нет | <f2> Да}}\"];\n", node, node->data);

    }

    // Если у узла есть левое поддерево, запишем связь
    if (node->left) {
        fprintf(file, "\tnode_%d:<f1> -> node_%d;\n", node, node->left);
        write_dot(node->left, file);
    }

    // Если у узла есть правое поддерево, запишем связь
    if (node->right) {
        fprintf(file, "\tnode_%d:<f2> -> node_%d;\n", node, node->right);
        write_dot(node->right, file);
    }
}

// Основная функция для записи дерева в формате DOT
void export_tree_to_dot(node_t* node, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Ошибка: Не удалось открыть файл для записи.\n");
        return;
    }

    // Запись заголовка DOT файла
    fprintf(file, "digraph G {\n\tbgcolor = \"white:purple\";\n");

    // Запись дерева
    write_dot(node, file);

    // Закрываем граф в DOT формате
    fprintf(file, "}\n");

    fclose(file);
    system("dot -Tpng ./res/tree.dot > ./res/tree.png");
}

void ReadTreeFromFile(node_t** node, const char* file_with_tree){
    FILE* file_tree = fopen(file_with_tree, "r");

    struct stat finfo;
    fstat(fileno(file_tree), &finfo);
    int number_of_symbols = (int)finfo.st_size/sizeof(char);
    
    // printf("%i\n",  number_of_symbols);

    char* buffer = (char *)calloc(number_of_symbols, 1);
    fread(buffer, 1, number_of_symbols, file_tree);
    
    // fprintf(stderr, "qwerty%s\n", buffer);

    
    // for (int i = 0; i < number_of_symbols; i++)
    // {
    //     fprintf(stderr, "%c", buffer[i]);
    // }
    // putchar('\n');

    char* buff = buffer;
    ReadTree(node, &buff);
    //printf("%s", buffer);
    free(buffer);

}

void ReadTree(node_t** node, char** bufer){

    *bufer += 2;
    string question = read_str_from_buff(*bufer);

    *node = CreateNode(question.str_pointer);
    *bufer += question.str_length + 1;
    free(question.str_pointer);

    if(**bufer == '('){
        ReadTree(&((*node) -> left), bufer);

    }
    if(**bufer == '('){
        ReadTree(&((*node) -> right), bufer);
    }
    if(**bufer == ')'){
        (*bufer)++;
        return;
    }
    else{
        printf("Ошибка \n");
    }

}
static string read_str_from_buff(char* buff)
{
    size_t i = 0; // TODO: rename

    while(buff[i] != '\"') // TODO: std funct
        ++i;

    char* str = (char*) calloc(i + 1, 1);

    for(size_t j = 0; j < i; j++) // TODO: std functions
    {
        str[j] = buff[j];
    }

    return {str, i};
}
void WriteTree(node_t* node, FILE* output){
    if(node == NULL) return;

    fprintf(output, "(");
    fprintf(output, "\"%s\"", node->data);

    if(node->left) WriteTree(node->left, output);
     //printf(")");
    if(node->right) WriteTree(node->right, output);
    //printf("%d", node->data);

    fprintf(output, ")");

}

void WriteTreeToFile(node_t* node, char* name_of_file){
    FILE* output = fopen(name_of_file, "w");
    WriteTree(node, output);
}

void FindPathToWord(node_t* node, char* word){
    int a[256] = {0};
    int i = 0;
    //printf("%i\n", i);
    bool is_word_in_tree = FindPathInTree(node, word, i, a);

    // for(int j = 0; a[j] != 0; j++){
    //     printf(" %i ", a[j]);
    // }

    if(is_word_in_tree != 0){
        printf("\nПризнаки элемента \"%s\":\n", word);
        WritePath(node, a, i, i, 256);
    }

    else{
        printf("Нет такого слова \n");
    }
}

bool FindPathInTree(node_t* node, char* word, int  i, int* a){
    //printf("%i\n", i);

    if(!strcasecmp(node->data, word)){
        //printf("%i\n", i);
        return true;
    }
    if(node->left){
    
        a[i] = -1;
         if(FindPathInTree(node->left, word, i + 1, a)){
            //printf("%i\n", i);
            return true ;
        }

    }

    if(node->right){
    
        a[i] = 1;
         if(FindPathInTree(node->right, word, i + 1, a)){
            //printf("%i\n", i);
            return true ;
        }

    }
    return false;

}

void WritePath(node_t* node, int* a, int i, int start, int end){

    if(a[i] == 0 || i >= end){
        return;
    }

    if(a[i] == -1){

        if(i >= start){

            printf("\tНе %s. \n", node->data);
        }
        WritePath(node->left, a, i+1, start, end);
        return;

    }

    if(a[i] == 1){
        if(i >= start){
            printf("\t%s. \n", node->data);
        }
        WritePath(node->right, a, i+1, start, end);
        return;
    }

    else{
        printf("Ошибка \n");
        return;
    }
}

void CompareWords(node_t* node, char* word1, char* word2){
    int path1[256] = {0};
    int path2[256] = {0};
    int start = 0;
    int i= 0;

    bool is_word1_in_tree = FindPathInTree(node, word1, start, path1);
    bool is_word2_in_tree = FindPathInTree(node, word2, start, path2);

    // for(int j = 0; path1[j] != 0; j++){
    //     printf(" %i ", path1[j]);
    // }
    // printf("\n");
    // for(int j = 0; path2[j] != 0; j++){
    //     printf(" %i ", path2[j]);
    // }
    // printf("\n");
    if(is_word1_in_tree == false && is_word2_in_tree == true){
        printf("ахтунг, первого слова нету в базе \n");

    }

    else if(is_word2_in_tree == false && is_word1_in_tree == true){
        printf("ахтунг, второго слова нету в базе \n");

    }

    else if(is_word1_in_tree == false && is_word2_in_tree == false){
        printf("ты чего творишь, обоих слов нет в базе \n");
    }

    else{

        while(path1[start] == path2[start] && start < 256){
            start++;
        }

        printf("\nОдинаковые признаки элементов \"%s\" и \"%s\": \n", word1, word2);

        WritePath(node, path1, i, i, start);

        printf("Отличия \"%s\": \n", word1);

        WritePath(node, path1, i, start, 256);

        printf("Отличия \"%s\": \n", word2);

        WritePath(node, path2, i, start, 256);

    }


}






