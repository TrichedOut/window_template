#include "client.h"
#include <stdio.h>
#include "window/window.h"


/**
  * run client-side code
  */
void client() {
  runWindow();
  
  // tell the server to stop
  sendPacket(clientPipe, HALT_PACKET, "");
}

