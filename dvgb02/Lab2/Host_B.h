#ifndef HOST_B_H
#define HOST_B_H

void B_output(struct msg message);
void B_input(struct pkt packet);
void B_timerinterrupt();
void B_init();

int send_ack(struct pkt packet);
#define A 0
#define B 1

#endif
