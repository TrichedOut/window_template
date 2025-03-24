#include "server.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// convert clock cycles to milliseconds
double clockToMs(clock_t ticks){
    // units/(units/time) => time (seconds) * 1000 = milliseconds
    return (ticks / (double) CLOCKS_PER_SEC) * 1000.0;
}

// time tracking
clock_t deltaTime, lastTime;
unsigned int ticks = 0;
const double updateRate = 1000. / 60.;

/**
  * send a TPS packet to the client when needed
  */
void updateTPS() {
  char tpsStr[20];

  // increment ticks
  ++ticks;

  // calc time
  deltaTime += clock() - lastTime;
  lastTime = clock();


  // update tps every `updateRate` ms
  if (clockToMs(deltaTime) > updateRate) {
    sprintf(tpsStr, "%d", ticks);
    sendPacket(serverPipe, TPS_PACKET, tpsStr);

    ticks = 0;
    deltaTime = 0;
  }
}

/**
  * run server-side code
  */
void server() {
  char* packet;
  lastTime = clock();

  while(1){
    // calc and update tps
    updateTPS();

    // if a halt packet is recieved, stop
    if (recievePacket(serverPipe, &packet) == HALT_PACKET) {
      exit(EXIT_SUCCESS);
    }
  }
}
