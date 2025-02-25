#include "settingterminal.h"
#include "inputkeyboard.h"
#include "outputscreen.h"
#include "initialize.h"
#include "fileIO.h"
#include <stdio.h>

/*** terminal ***/
void enableRawMode();

/***  initialize ***/
void initWindowSize();

/*** keyboard ***/
void processingKeypress();

/*** screen ***/
void refreshScreen();
int main(int argc, char *argv[]) {
  enableRawMode();
  initWindowSize();
  if(argc >= 2)
    openEditor(argv[1]);
  while(1) {
    refreshScreen();
    processingKeypress();
  }
  return 0;
}
