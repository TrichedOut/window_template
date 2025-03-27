#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "window.h"
#include "packets/packetMgr.h"
#include "displays/text.h"

// window constants or one-offs
const int WIDTH = 1080;
const int HEIGHT = 720;
const char* TITLE = "AlphaRW";
int windowActive = 1;
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
 * code to run before each render frame
 */
void preRender() {
  // read incoming packets
  readPackets();

  // create fps and tps string
  sprintf(FPS_BUF, "fps: %d", GetFPS());
  sprintf(TPS_BUF, "tps: %d", packetState.tps);

  // perform only draw calls unil EndDrawing
  BeginDrawing();
}

/**
 * code to run after each render frame
 */
void postRender() {
  // stop drawing, may perform non-draw calls afterwards
  EndDrawing();

  // if raylib detects window should close, such as clicking the `x` button, close the window
  if (WindowShouldClose()) {
    CloseWindow();
    windowActive = 0;
  }
}

/**
 * initialize anything needed before rendering. if initialization fails, returns
 * false to be handled
 *
 * @return 0 if fails to initialize. 1 otherwise
 */
int initWindow() {
  // initialize raylib for rendering
  setupRaylib();
  if (!IsWindowReady()) {
    return 0;
  }

  setDefaultFont();

  return 1;
}

/**
 * returns 1 if the window is active, 0 otherwise.
 */
int windowIsActive() {
  return windowActive;
}

/**
  * all client side rendering done in or from this function.
  * when this function returns, perform cleanup then exit the program.
  */
void render() {
  preRender();

  // set the background each frame
  ClearBackground(BLACK);

  // draw fps and tps
  drawText(FPS_BUF, 4, 4, 20, WHITE);
  drawText(TPS_BUF, 4, 24, 20, WHITE);

  postRender();
}

