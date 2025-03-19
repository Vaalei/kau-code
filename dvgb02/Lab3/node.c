#include "node.h"

void rtinit(struct distance_table *table, int node) {
	// Tables are already initialized
	for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            table->costs[i][j] = INF;
        }
    }
    // Set direct neighbor costs
    table->costs[node][node] = 0;
    if (node == 0) { table->costs[1][0] = 1; table->costs[2][0] = 3; table->costs[3][0] = 7; }
    if (node == 1) { table->costs[0][1] = 1; table->costs[2][1] = 1; table->costs[3][1] = INF; }
    if (node == 2) { table->costs[0][2] = 3; table->costs[1][2] = 1; table->costs[3][2] = 2; }
    if (node == 3) { table->costs[0][3] = 7; table->costs[1][3] = INF; table->costs[2][3] = 2; }
    
    // Send initial distances to neighbors
    struct rtpkt packet;
    packet.sourceid = node;
    for (int i = 0; i < 4; i++) {
        packet.mincost[i] = table->costs[i][node];
    }
    for (int i = 0; i < 4; i++) {
        if (is_neighbor(node, i)) {
            packet.destid = i;
            tolayer2(packet);
        }
    }
	printdt(table, node);
}

void rtupdate(struct distance_table *table, int node, struct rtpkt *pkt) {
	int updated = 0;
    for (int i = 0; i < 4; i++) {
        int new_cost = table->costs[pkt->sourceid][node] + pkt->mincost[i];
        if (new_cost < table->costs[i][pkt->sourceid]) {
            table->costs[i][pkt->sourceid] = new_cost;
            updated = 1;
        }
    }
    
    if (updated) {
        struct rtpkt packet;
        packet.sourceid = node;
        for (int i = 0; i < 4; i++) {
            int min_cost = INF;
            for (int j = 0; j < 4; j++) {
                if (table->costs[i][j] < min_cost) {
                    min_cost = table->costs[i][j];
                }
            }
            packet.mincost[i] = min_cost;
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

