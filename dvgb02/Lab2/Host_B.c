#include "Sim_Engine.h"
#include "Host_B.h"
#include "lib.h"
#include <string.h>
#define TIMEOUT 20.0
#define true 1
#define false 0

int expected_seqnum = 1;

struct pkt last_packet;

/* Called from layer 5, passed the data to be sent to other side */
void B_output(struct msg message)
{
	/* DON'T IMPLEMENT */
}

/* Called from layer 3, when a packet arrives for layer 4 */
void B_input(struct pkt packet)
{
	if (verify_checksum(packet))
	{
		if (packet.seqnum == expected_seqnum)
		{
			printf("B_input: Packet received correctly\n");
			tolayer5(B, packet.payload);
			struct pkt ack_packet;
			ack_packet.seqnum = expected_seqnum;
			ack_packet.acknum = packet.seqnum;
			strcpy(ack_packet.payload, "");
			ack_packet.checksum = make_checksum(ack_packet);
			tolayer3(B, ack_packet);
			expected_seqnum = !expected_seqnum;
		}
		else
		{
			printf("B_input: Packet out of order, resending ack\n");
			send_ack(packet);
		}
	}
	else
	{
		printf("B_input: Packet corrupted, resending ack\n");
		send_ack(packet);
	}
}

/* Called when B's timer goes off */
void B_timerinterrupt()
{
	printf("A_timerinterrupt: Timeout, resending packet\n");
	tolayer3(B, last_packet);
	starttimer(B, TIMEOUT);
}

/* The following routine will be called once (only) before any other */
/* Host B routines are called. You can use it to do any initialization */
void B_init()
{
	/* TODO */
}

int send_ack(struct pkt packet)
{
	struct pkt ack_packet;
	ack_packet.seqnum = 0;
	ack_packet.acknum = packet.seqnum;
	strcpy(ack_packet.payload, "");
	ack_packet.checksum = make_checksum(ack_packet);
	tolayer3(B, ack_packet);
	return 0;
}