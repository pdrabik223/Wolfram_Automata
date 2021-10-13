//
// Created by piotr on 07/10/2021.
//

#include "Automata/wolfram_automata.h"
#include "sfml_window/settings_window.h"
#include "sfml_window/window.h"
#include <iostream>
int main() {
  AutomataInfo first(90);
  Slice slice(1920);
  slice.FillRandom(50);
//  slice[1920/2] = ON;

  Window screen(1920 ,1080);


  for (int i = 0; i < 1080; i++) {
    screen.PushFrame(Slicer(slice));
    slice.GenerateSuccessor(first);
  }
//  SettingsWindow test(600,600);

//  system("pause");
  return 0;
}


void MainLoop(){
    // Set screen width
    // Set screen height

    // set slice width
    // fill random %procenteage
    // fill On
    // fill Off
    // set %position

    // Run Automata

    // Help

    // display settings

    // display info

};