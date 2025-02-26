#include "Sim_Engine.h"
#include "Host_A.h"
#include "lib.h"
#include <string.h>

#define TIMEOUT 20.0
#define true 1
#define false 0

int waiting_for_ack = 0;

struct pkt last_packet;
static int seqNum = 0, ackNum = 0;



/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
	ackNum = !ackNum;
    seqNum = !seqNum;
	struct pkt packet;
	packet.seqnum = ackNum;
	packet.acknum = seqNum;
	strcpy(packet.payload, message.data);
	packet.checksum = make_checksum(packet);

	last_packet = packet;

	waiting_for_ack = 1;
	tolayer3(A, packet);
	starttimer(A, TIMEOUT);
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
	if (!verify_checksum(packet) || packet.acknum != last_packet.seqnum)
	{
		printf("A_input: Packet corrupted or wrong acknum (%d, wanted %d), resending\n", packet.acknum, last_packet.seqnum);
		tolayer3(A, last_packet);
		
	}
	else
	{
		waiting_for_ack = 0;
		stoptimer(A);
		printf("A_input: Packet received correctly\n");
	}
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
	printf("A_timerinterrupt: Timeout, resending packet\n");
	tolayer3(A, last_packet);
	starttimer(A, TIMEOUT);
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
	/* TODO */
}
