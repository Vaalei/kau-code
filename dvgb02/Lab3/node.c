#include "node.h"

void rtinit(struct distance_table *table, int node) {
    // Send initial distances to neighbors
    struct rtpkt packet;
    packet.sourceid = node;


    for (int i = 0; i < 4; i++) {
        packet.mincost[i] = table->costs[node][i];
    }
    for (int i = 0; i < 4; i++) {
        if (is_neighbor(node, i)) {
            packet.destid = i;
            tolayer2(packet);
        }
    }

	//printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
    // Variable to track if the table was updated
    int i, j;
    int updated = 0;

    for (i = 0; i < 4; i++) {

        if((pkt->mincost[i] != table->costs[pkt->sourceid][i])) {
            table->costs[pkt->sourceid][i] = pkt->mincost[i];
        }

        int new_cost = table->costs[node][pkt->sourceid] + pkt->mincost[i];
        if (new_cost < table->costs[node][i]) {
            table->costs[node][i] = new_cost;
            updated = 1; 
        }
    }

    if (updated) {
        struct rtpkt packet;
        packet.sourceid = node;
        for (int i = 0; i < 4; i++) {
            packet.mincost[i] = table->costs[node][i];
        }

        for (int i = 0; i < 4; i++) {
            if (is_neighbor(node, i)) {
                packet.destid = i;
                tolayer2(packet);
            }
        }
    }
    printdt(table, node);
}

