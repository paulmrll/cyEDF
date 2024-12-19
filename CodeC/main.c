#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


#include "include/create_avl.h"
#include "include/parcours.h"
#include "include/type_avl.h"
#include "include/createData.h"
#include "include/fonction_utile.h"


int main(int argc, char* argv[]){
    //Check if the number of argument is correct
    if (argc != 4){
        printf("\033[31mERROR : not enough argument\033[0m\n");
        exit(10);
    }
    //Check if argv[2] is correct
    if (strcmp(argv[2], "hva") != 0 && strcmp(argv[2], "hvb") != 0 && strcmp(argv[2], "lv") != 0){
        exit(20);
    }

    //Define the type of the station
    char* type = argv[2];

    //Initialize the parameters for the height anf the stability of an avl
    int hStation = 0;
    int hConso = 0;

    //Initialize the tree of the station
    tree* stationTree = NULL;
    tree* consoTree = NULL;


    //Open the file which contains the data and check if all is right
    FILE* fichier = fopen(argv[1], "r");
    if (fichier == NULL){
        printf("\033[31mERROR : argument 1 file is empty\033[0m\n");
        exit(30);
    }


    //Take data of a file and add it to a tree
    ensembleDonne(fichier, &hStation, &hConso, &stationTree, &consoTree, type);
    parcours1(consoTree, &stationTree);
    parcours(stationTree);
    //Initialize tree
    freeAvl(stationTree);
    return 0;
}