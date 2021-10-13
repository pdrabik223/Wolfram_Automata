//
// Created by piotr on 07/10/2021.
//

#include "Automata/wolfram_automata.h"
#include <iostream>
#include "sfml_window/window.h"
int main() {
  AutomataInfo first(90);
  Slice slice(60);
//  slice.FillRandom(50);
  slice[60/2] = ON;

  Window screen(1920 ,1080);

  for (int i = 0; i < 40; i++) {
    screen.PushFrame(Slicer(slice));
    slice.GenerateSuccessor(first);
  }

  system("pause");
  return 0;
}
