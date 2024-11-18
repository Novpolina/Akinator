#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "akinator.h"

int main(){
    // node_t* node1 = CreateNode("Чел учится на 2 курсе");
    // node_t* node2 = CreateNode("Он похож на Поднебесного");
    // node_t* node3 = CreateNode("Это девочка");
    // node_t* node4 = CreateNode("Ясин");
    // node_t* node5 = CreateNode("Богдан");
    // node_t* node6 = CreateNode("Миша");
    // node_t* node7 = CreateNode("Вика");
    // node1->left = node2;
    // node1->right = node3;
    // node2->left = node4;
    // node2->right = node5;
    // node3->left = node6;
    // node3->right = node7;
    node_t* node1 = {};
    ReadTreeFromFile(&node1, "./res/akinator.txt");
    game(node1);


    //DestructNode(node1);
    //Akinator(node1);
    // FindPathToWord(node1, "Петрович");
    // CompareWords(node1, "Петрович", "Женечка");
    // //Print(node1);
    export_tree_to_dot(node1, "./res/tree.dot");
    WriteTreeToFile(node1, "./res/akinator.txt");
    DestructNode(node1);


    


                                                                                                                                                                                                                                                                                                                                            printf("Люблю Полину\nОна солнышко\n");

}