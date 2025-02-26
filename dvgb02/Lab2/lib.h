#ifndef LIB_H
#define LIB_H

#include "Sim_Engine.h"

int make_checksum(struct pkt packet);
int verify_checksum(struct pkt packet);

#endif // LIB_H
