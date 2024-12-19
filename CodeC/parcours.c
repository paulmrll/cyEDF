#include "include/parcours.h"
#include "include/outfile.h"

/**
 * @param head
 * @param a
 * Sum the consumption of the data to the station which has the same id
 */
void parcoursRefresh(tree** head, Data a) {
    if (*head != NULL) {
        if ((*head)->a.id < a.id){
            parcoursRefresh(&((*head)->fd), a);
        } else if ((*head)->a.id > a.id){
            parcoursRefresh(&((*head)->fg), a);
        } else {
            (*head)->a.consumption += a.consumption;

        }

    }
}

void parcours(tree* head){
    if (head != NULL){
        putInFile(head);
        parcours(head->fg);
        parcours(head->fd);
    }
}
