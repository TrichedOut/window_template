#include "packetMgr.h"
#include "../../../communication/pipeMgr.h"
#include "../../client.h"
#include <stdio.h>
#include <stdlib.h>

/**
  * given packet data, write the tps into packetState
  *
  * @params packetData the data read from a packet
  */
void getTps(char* packetData) {
  sscanf(packetData, "%d", &packetState.tps);
}

/**
  * process all present packets sent by the server
  */
void readPackets() {
  char* packetData;

  // read the first packet
  PacketType type = recievePacket(clientPipe, &packetData);

  // repeat while packets are present
  while (1) {
    // based on the read packet, process.
    switch (type) {
      // if there are no packets left or server has stopped, return or exit
      case NO_PACKETS:
        return;
      case HALT_PACKET:
        exit(EXIT_SUCCESS);

      // otherwise process the data
      case TPS_PACKET:
        getTps(packetData);
        break;
    }

    // free the packet gathered, then get the next packet
    free(packetData);
    type = recievePacket(clientPipe, &packetData);
  }
}
