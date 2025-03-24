#ifndef PACKETMGR
#define PACKETMGR


typedef struct {
  int tps;
} PacketState;
PacketState packetState;

void readPackets();


#endif
