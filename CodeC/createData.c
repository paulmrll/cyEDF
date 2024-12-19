#include "include/createData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Transform the "-" in the file to "0".
 * @param fichier Input file pointer
 * @return A temporary file pointer with the transformed content.
 */
FILE* transformerFichier(FILE* fichier) {
    if (fichier == NULL) {
        fprintf(stderr, "Erreur : fichier NULL.\n");
        exit(30);
    }

    // Crée un fichier temporaire pour stocker le contenu transformé
    FILE* new_file = fopen("../tmp/tmp.txt", "w");
    if (new_file == NULL) {
        perror("Erreur lors de la création d'un fichier temporaire");
        fclose(fichier);
        exit(30);
    }

    char line[256];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        // Remplacer chaque '-' par '0'
        for (size_t i = 0; i < strlen(line); i++) {
            if (line[i] == '-') {
                line[i] = '0';
            }
        }
        // Écrire la ligne transformée dans le fichier temporaire
        fputs(line, new_file);
    }
    fclose(new_file);
    new_file = fopen("../tmp/tmp.txt", "r");
    return new_file;
}

/**
 * @brief Take data from a file and add it to a tree.
 * @param fichier Input file pointer
 * @param hStation Pointer to station height
 * @param stationTree Pointer to the tree structure
 * @param type Data type
 */
void ensembleDonne(FILE* fichier, int* hStation, int* hConso, tree** stationTree, tree** consoTree, char* type) {
    if (fichier == NULL || hStation == NULL || stationTree == NULL || type == NULL) {
        fprintf(stderr, "Erreur : arguments invalides.\n");
        exit(30);
    }
    // Transformer le fichier pour remplacer les '-' par '0'
    FILE* new_file = transformerFichier(fichier);

    char line[256];
    Data* tmp = init();
    if (tmp == NULL) {
        fprintf(stderr, "Erreur : échec de l'initialisation des données.\n");
        fclose(new_file);
        exit(30);
    }

    int i = 0;

    // Lire la première ligne pour initialiser tmp
    if (fgets(line, sizeof(line), new_file) != NULL) {
        sscanf(line, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu;",
               &tmp->Powerplant, &tmp->hv_b, &tmp->hv_a, &tmp->lv,
               &tmp->company, &tmp->consumer, &tmp->production, &tmp->consumption);

        // Ajouter les données à l'arbre
        addTree(stationTree, consoTree, *tmp, hStation, hStation, type, tmp, &i);
    }

    Data b;

    // Lire les autres lignes
    while (fgets(line, sizeof(line), new_file) != NULL) {
        sscanf(line, "%lu;%lu;%lu;%lu;%lu;%lu;%lu;%lu;",
               &b.Powerplant, &b.hv_b, &b.hv_a, &b.lv,
               &b.company, &b.consumer, &b.production, &b.consumption);

        // Ajouter les données à l'arbre
        addTree(stationTree, consoTree, b, hStation, hConso, type, tmp, &i);

    }

    // Libérer les ressources
    free(tmp);
    fclose(new_file);
}
