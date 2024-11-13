#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
//#include "work_with_file.h"

#include "akinator.h"

int YES = 10;
int NO = -10;


struct string{
    char* str_pointer;
    size_t str_length;
};

static string read_str_from_buff(char* buff);
void ReadTree(node_t** node, char** bufer);


node_t* CreateNode(char* value){

    node_t* node = (node_t*)calloc(1, sizeof(node_t));
    node->data = (char*)calloc(100, sizeof(char));
    strcpy(node->data, value);
    node->left = NULL;
    node->right = NULL;
    return node;
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
    printf("Enter your word \n");
    read_string(new_elem);
    printf("Enter question \n");
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

        if(strcasecmp("yes", answer) == 0){
            res = YES;
        }
        else if(strcasecmp("no", answer) == 0){
            res = NO;
        }
        else{
            printf("In english normalno otvet napishi");
            read_string(answer);

        }

    }
    return res;


}

void Akinator(node_t* node){
    char answer[100] = {};//(char*)calloc(100, sizeof(char));

    if(node->left == NULL || node->right == NULL){
        printf("Your word is %s?", node->data);
        read_string(answer);
        int res = CheckAnswer(answer);

        if( res == YES){
            printf("Zayebis");
        }
        else if(res == NO){
            InsertNewQuestion(node);
        }
        else{
            printf("Error with answer");

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
            printf("Error with answer");
            

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

// void GraphDump(node_t* node){

//     FILE* f_dot = fopen("tree.dot", "w");

//     assert(f_dot);
//     assert(node);
//     if(ferror(f_dot)) fprintf(stderr, "FILE OPEN ERROR!!!\n");

//     fprintf(f_dot, "diagraf T{ \n node[fontsize = 9]; ");



    

//     fclose(f_dot);
// }

// void PrintRangForNode(node_t* node, FILE* f_dot, int i, int j){
//     if(node == NULL) return;

//     i++;
//     j++;

//     fprintf(f_dot, "{ rank = same; \"node_%d\"; \"rank_%d\"; \"a\"; } \n", j, i);

//     fprintf(f_dot, "\tnode%zu -> node%d;\n", i, list -> node[i].next);


//     fprintf(f_dot, "\tnode%zu [shape=record, color=blue,"
//                        "label=\" index=%zu | data=%d | next=%d | prev=%d \" ];\n",
//                        i, i, list -> node[i].data, list -> node[i].next, list -> node[i].prev);





// }
void write_dot(node_t* node, FILE* file) {
    if (node == NULL) {
        return;
    }

    if(node->left == 0 || node->right == 0){
        fprintf(file, "\tnode_%d [shape = record, color = white, label=\"{%s}\"];\n", node, node->data);

    }
    else{
        fprintf(file, "\tnode_%d [shape = record, color = white, label=\"{{%s} | {<f1> Нет | <f2> Да}}\"];\n", node, node->data);

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
    system("dot -Tpng tree.dot > tree.png");
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

    
    for (int i = 0; i < number_of_symbols; i++)
    {
        fprintf(stderr, "%c", buffer[i]);
    }
    putchar('\n');

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
        printf("Error");
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


