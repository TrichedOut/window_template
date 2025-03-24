#ifndef PIPEMGR
#define PIPEMGR


#define PACKET_SIZE 64

typedef struct {
  int writeFd;
  int readFd;
} PipeMgr;

typedef enum {
  NO_PACKETS,
  HALT_PACKET,
  TPS_PACKET,
} PacketType;

PipeMgr* makePipePair();
void sendPacket(PipeMgr* pipe, PacketType type, const char* data);
PacketType recievePacket(PipeMgr* pipe, char** dest);


#endif
