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
int timer = 0;

struct node {
	struct pkt packet;
	struct node* next;
};

struct node* head = NULL;
struct node* tail = NULL;

void print_linkedlist() {
	struct node* current = head;
	while (current != NULL) {
		// printf("Packet: seqnum=%d, acknum=%d, checksum=%d, payload=%s\n",
		//   	current->packet.seqnum, current->packet.acknum,
		//   	current->packet.checksum, current->packet.payload);
		current = current->next;
	}
}

void append_packet(struct pkt packet) {
	struct node* new_node = (struct node*)malloc(sizeof(struct node));
	new_node->packet = packet;
	new_node->next = NULL;
	if (tail == NULL) {
		head = new_node;
		tail = new_node;
	} else {
		tail->next = new_node;
		tail = new_node;
	}
}

struct pkt* get_next_packet() {
	if (head == NULL) {
		return NULL;
	}
	struct pkt* packet = &head->packet;
	struct node* temp = head;
	head = head->next;
	if (head == NULL) {
		tail = NULL;
	}
	free(temp);
	return packet;
}

struct pkt* get_current_packet() {
	if (head == NULL) {
		return NULL;
	}
	return &head->packet;
}

/* Called from layer 5, passed the data to be sent to other side */
void A_output(struct msg message)
{
	// printf("A_output: Sending packet first time +++++++++++++++++++++++++++++++++++\n");
    seqNum = !seqNum;
	struct pkt packet;
	packet.seqnum = seqNum;
	packet.acknum = 0;
	strcpy(packet.payload, message.data);
	packet.checksum = make_checksum(packet);
	
	append_packet(packet);
	if(timer == 0) {
		send_packet(*get_current_packet());
	}
}

/* Called from layer 3, when a packet arrives for layer 4 */
void A_input(struct pkt packet)
{
	if(head != NULL) {
		last_packet = *get_current_packet();
	}
	
	timer = 0;
	stoptimer(A);
	if (!verify_checksum(packet) || packet.acknum != last_packet.seqnum)
	{
		// printf("A_input: Packet corrupted or wrong acknum (%d, wanted %d), resending\n", packet.acknum, last_packet.seqnum);
	}
	if (packet.acknum == last_packet.seqnum)
	{
		// printf("A_input: Ack received correctly\n");
		// printf("+\n");
		// printf("A_input: Sending next packet\n");
		get_next_packet();
	}
	else
	{
		// printf("A_input: Packet out of order, resending\n");
		
	}
	print_linkedlist();
	if(head != NULL) {
		send_packet(*get_current_packet());
	}
	
}

/* Called when A's timer goes off */
void A_timerinterrupt()
{
	// printf("A_timerinterrupt: Timeout, resending packet\n");
	if(get_current_packet() != NULL) 
	{
		send_packet(*get_current_packet());
	}
}

/* The following routine will be called once (only) before any other */
/* Host A routines are called. You can use it to do any initialization */
void A_init()
{
	waiting_for_ack = 0;
    seqNum = 0;
}

void send_packet(struct pkt packet)
{
	// printf("A_input: Sent packet\n");
	tolayer3(A, packet);
	starttimer(A, TIMEOUT);
	timer = 1;
}