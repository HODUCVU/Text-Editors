#include "settingterminal.h"
#include "inputkeyboard.h"
#include "outputscreen.h"
#include "initialize.h"
#include <stdio.h>


/*** terminal ***/
extern void enableRawMode();

/***  initialize ***/
extern void initWindowSize();

/*** keyboard ***/
extern void processingKeypress();

/*** screen ***/
extern void refreshScreen();

int main() {
  enableRawMode();
  initWindowSize();
  while(1) {
    refreshScreen();
    processingKeypress();
  }
  return 0;
}
