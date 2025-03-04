#ifndef HOST_A_H
#define HOST_A_H

void A_output(struct msg message);
void A_input(struct pkt packet);
void A_timerinterrupt();
void A_init();
void send_packet(struct pkt packet);
void append_packet(struct pkt packet);
struct pkt *get_next_packet();
#define A 0
#define B 1

#endif
