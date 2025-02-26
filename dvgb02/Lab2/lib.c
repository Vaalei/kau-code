#include "Sim_Engine.h"

int make_checksum(struct pkt packet)
{
	int sum = 0;
	for (int i = 0; packet.payload[i] != '\0'; i++)
		sum += packet.payload[i];
	sum += packet.acknum;
	sum += packet.seqnum;
	return sum;
}

/* Returns the checksum of a packet */
int verify_checksum(struct pkt packet)
{
	return make_checksum(packet) == packet.checksum;
}
