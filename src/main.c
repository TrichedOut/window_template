#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include "client/client.h"
#include "server/server.h"
#include "communication/pipeMgr.h"


int main() {
  // create a pair of pipes for two way communication
  PipeMgr* pipes = makePipePair();
  serverPipe = &pipes[0];
  clientPipe = &pipes[1];

  // run in two groups, rendering client and running server
  int cpid = fork();
  if (cpid == -1) {
    err(EXIT_FAILURE, "failed to create child process.");
  }

  // run either client or server. order doesnt matter
  if (cpid) {
    client();
  } else {
    server();
  }

  free(pipes);
  return EXIT_SUCCESS;
}
