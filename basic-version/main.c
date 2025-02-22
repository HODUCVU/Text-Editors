#include "settingterminal.h"
#include "inputkeyboard.h"
#include "outputscreen.h"
#include "initialize.h"
#include <stdio.h>


/*** terminal ***/
void enableRawMode();

/***  initialize ***/
void initWindowSize();

/*** keyboard ***/
void processingKeypress();

/*** screen ***/
void refreshScreen();

int main() {
  enableRawMode();
  initWindowSize();
  while(1) {
    refreshScreen();
    processingKeypress();
  }
  return 0;
}
