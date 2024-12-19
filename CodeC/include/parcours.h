#ifndef PARCOURS_H
#define PARCOURS_H
#include <stdio.h>

#include "type_avl.h"
#include "fonction_utile.h"

/**
 * @param head
 * @param a
 * Sum the consumption of the data to the station which has the same id
 */
void parcoursRefresh(tree** head, Data a);

void parcours(tree* head);

#endif //PARCOURS_H