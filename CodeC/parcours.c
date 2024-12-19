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
void parcours2(Data a, tree** stationTree){
    if (*stationTree != NULL){
        if (a.id == (*stationTree)->a.id) {
            (*stationTree)->a.consumption += a.consumption;
        } else {
            if (a.id < (*stationTree)->a.id){
                parcours2(a, &(*stationTree)->fg);
            } else {
                parcours2(a, &(*stationTree)->fd);
            }
        }
    }
}
void parcours1(tree* consoTree, tree** stationTree){
    if (consoTree != NULL && stationTree != NULL){
        parcours2(consoTree->a, stationTree);
        parcours1(consoTree->fg, stationTree);
        parcours1(consoTree->fd, stationTree);
    }
}
void parcours(tree* head){
    if (head != NULL){
        putInFile(head);
        parcours(head->fg);
        parcours(head->fd);
    }
}
