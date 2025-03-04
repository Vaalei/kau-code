#include "Sim_Engine.h"

int make_checksum(struct pkt packet)
{
    int sum = packet.acknum + packet.seqnum;
    for (int i = 0; i < sizeof(packet.payload) && packet.payload[i] != '\0'; i++)
    {
        sum += packet.payload[i];
    }
    return sum;
}

/* Returns whether the checksum of a packet is correct */
int verify_checksum(struct pkt packet)
{
    return (make_checksum(packet) == packet.checksum);
}
