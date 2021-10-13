//
// Created by piotr on 07/10/2021.
//

#include "Automata/wolfram_automata.h"
#include <iostream>

int main() {
  AutomataInfo first(90);
  DisplayRule(first);
  Slice slice(10);
  slice[5] = 1;

  for (int i = 0; i < 40; i++) {
    ConsoleDisplay(slice);
    slice.GenerateSuccessor(first);
  }

  system("pause");
  return 0;
}
