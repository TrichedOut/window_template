#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "window.h"
#include "packets/packetMgr.h"

// window constants or one-offs
const int WIDTH = 1080;
const int HEIGHT = 720;
const char* TITLE = "AlphaRW";
char FPS_BUF[20];
char TPS_BUF[20];

/**
  * run functions to config raylib properly
  */
void setupRaylib() {
  SetTraceLogLevel(LOG_NONE);       // remove logs
  InitWindow(WIDTH, HEIGHT, TITLE); // create the window
  SetExitKey(0);                    // no key causes exit
}


/**
  * all client side rendering done in or from this function.
  * when this function returns, perform cleanup then exit the program.
  */
void runWindow() {
  // initialize raylib for rendering
  setupRaylib();

  // if this call returns false, there was an error and cannot continue
  if (IsWindowReady()) {
    // window loop
    while (1) {
      // read incoming packets
      readPackets();

      // create fps and tps string
      sprintf(FPS_BUF, "fps: %d", GetFPS());
      sprintf(TPS_BUF, "tps: %d", packetState.tps);

      // perform only draw calls unil EndDrawing
      BeginDrawing();

      // set the background each frame
      ClearBackground((Color){0, 0, 0, 255});

      // draw fps and tps
      DrawText(FPS_BUF, 4, 4, 16, (Color){255, 255, 255, 255});
      DrawText(TPS_BUF, 4, 24, 16, (Color){255, 255, 255, 255});

      // stop drawing, may perform non-draw calls afterwards
      EndDrawing();

      // if raylib detects window should close, such as clicking the `x` button, close the window
      if (WindowShouldClose()) {
        CloseWindow();
        break;
      }
    }
  }
}

