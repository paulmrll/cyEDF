#include "include/outfile.h"

void putInFile(tree* head) {
        printf("%d:%lu:%lu:%lu:%lu:%lu:%lu:%lu:%lu\n",
               head->a.id, head->a.Powerplant, head->a.hv_b, head->a.hv_a, head->a.lv,
               head->a.company, head->a.consumer, head->a.production, head->a.consumption);

}
