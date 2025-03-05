/************************
 * 
 * Author: Ho Duc Vu
 * Date: 26/02/2025
 * Mail: hoducvu1234@gmail.com
 * Github: https://github.com/HODUCVU
 *  
 * ************************/
#include "settingterminal.h"
#include "inputkeyboard.h"
#include "outputscreen.h"
#include "initialize.h"
#include "fileIO.h"
#include <stdio.h>

/*** terminal ***/
void enableRawMode();

/***  initialize ***/
void initEditor();

/*** keyboard ***/
void processingKeypress();

/*** screen ***/
void refreshScreen();
int main(int argc, char *argv[]) {
  enableRawMode();
  initEditor();
  if(argc >= 2)
    openEditor(argv[1]);
  while(1) {
    refreshScreen();
    processingKeypress();
  }
  return 0;
}
