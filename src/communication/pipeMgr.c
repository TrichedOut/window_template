#include "pipeMgr.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <poll.h>

/**
 * make a pair of pipes linked with eachother for two-way communication
 */
PipeMgr* makePipePair() {
  // file descriptors
  int fdsA[2];
  int fdsB[2];

  // create pipes, fail hard if error
  if (pipe(fdsA) == -1 || pipe(fdsB) == -1) {
    err(EXIT_FAILURE, "failed to create pipes");
  }

  // make the array of PipeMgrs
  PipeMgr* pipes = malloc(sizeof(PipeMgr) * 2);
  pipes[0] = (PipeMgr) {
    .readFd = fdsA[0],
    .writeFd = fdsB[1],
  };
  pipes[1] = (PipeMgr) {
    .readFd = fdsB[0],
    .writeFd = fdsA[1],
  };

  return pipes;
}

/**
 * writes data to a pipe given the type of packet.
 * cannot be longer than `PACKET_SIZE` bytes.
 * `PACKET_SIZE` is in `pipeMgr.h`
 *
 * @param pipe the `PipeMgr` that will send the packet
 * @param type the `PacketType` that is being sent
 * @param data the data being sent in the packet
 */
void sendPacket(PipeMgr* pipe, PacketType type, const char* data) {
  // ensure data fits in a packet
  int dataSize = strlen(data);
  if (dataSize >= PACKET_SIZE) {
    err(EXIT_FAILURE, "packet given too large, size: %d; max of %d.", dataSize, PACKET_SIZE - 1);
  }

  // create a new packet
  char packet[PACKET_SIZE];

  // fill the packet and write to pipe
  sprintf(packet, "%c%s", (int)type, data);
  write(pipe->writeFd, packet, PACKET_SIZE);
}

/**
  * reads data from a pipemgr pipe. the pointer in *dest needs freed.
  *
  * @param pipe the `PipeMgr` that will read the packet
  * @param dest a double pointer to place the data into. needs freed.
  * @return PacketType the type of packet
  */
PacketType recievePacket(PipeMgr* pipe, char** dest) {
  // check if the file needs read
  struct pollfd fds = {pipe->readFd, POLLIN, 0};
  if (!poll(&fds, 1, 0)) return NO_PACKETS;

  // read the data from the packet
  char* data = malloc(sizeof(char) * PACKET_SIZE);
  int readSize = read(pipe->readFd, data, PACKET_SIZE);

  // write the important data to destination
  *dest = malloc(sizeof(char) * (PACKET_SIZE) - sizeof(int));
  strcpy(*dest, data + 1);

  // get and return the packet type, after freeing data
  PacketType type = (PacketType) *data;
  free(data);
  return type;
}

