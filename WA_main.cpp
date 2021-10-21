//
// Created by piotr on 07/10/2021.
//
#include "conio.h"
#include "Automata/wolfram_automata.h"
#include "settings.h"
#include "sfml_window/window.h"
#include <iostream>
#define HEIGHT 1920
#define WIDTH 1080
int main() {

  Window screen(1080, 1920);

  //  SettingsWindow test(600,600);

  //  system("pause");

  // the question:

  // piotr: 3
  // mateusz: 7

  // rule %13 = out  number
  // so every rule that %13 == 3 is mine
  // exercise 1


  // model Ising'a ?
  // i wymyśl taki co jest w kategori inne

  for (int i = 0; i < 255; i++) {

    if (i % 13 == 7) {
      std::cout << "rule " << i;
      AutomataInfo first(i);
      DisplayRule(first);
      Slice slice(WIDTH);

      slice.FillRandom(10);
        screen.Clear();

        for (int h = 0; h < HEIGHT; h++) {
        screen.PushFrame(Slicer(slice));
        slice.GenerateSuccessor(first);
      }
      char key;
      key = getch();
        if(key == 'j' and i>= 13) i-= 13;

    }
  }

  return 0;
}
