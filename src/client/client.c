#include "client.h"
#include <stdio.h>
#include "window/window.h"


/**
  * run client-side code
  */
void client() {
  if (initWindow()) {
    while (windowIsActive()) {
      render();
    }
  }
  
  // tell the server to stop
  sendPacket(clientPipe, HALT_PACKET, "");
}

