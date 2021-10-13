//
// Created by piotr on 07/10/2021.
//

#include "Automata/wolfram_automata.h"
#include <iostream>
#include "sfml_window/window.h"
int main() {
  AutomataInfo first(30);
  Slice slice(1920);
  slice[1920/2] = ON;

  Window screen(1920 ,1080);

  for (int i = 0; i < 1080; i++) {
    screen.PushFrame(Slicer(slice));
    slice.GenerateSuccessor(first);
  }

  system("pause");
  return 0;
}
