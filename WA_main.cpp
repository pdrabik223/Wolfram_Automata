//
// Created by piotr on 07/10/2021.
//
#include "Automata/wolfram_automata.h"
#include "conio.h"

#include "sfml_window/window.h"
#include <array>
#include <fstream>
#include <iostream>

/// the width of automata
#define WIDTH 900
/// the height of automata
#define HEIGHT 900
void WolframSlice();
void SaveToRoot();
using Frame = std::vector<Slice>;
void SaveFrame(const Frame &data, const std::string &path);

/// deadline 7 listopada 23:59

int main() {
  srand(time(NULL));

  // piotr: 3
  // mateusz: 7

  // rule %13 = out  number
  // so every rule that %13 == 3 is mine
  // exercise 1

//  WolframSlice();

  //  SaveToRoot();
  return 0;
}
void SaveToRoot() {

  AutomataInfo first(90);

  Slice slice(WIDTH);

  //  slice.FillRandom(50);
  slice.Set(WIDTH / 2, ON);

  DisplayRule(first);

  Frame frame;
  frame.reserve(HEIGHT);
  for (int h = 0; h < HEIGHT; h++) {
    frame.push_back(slice);
    slice.GenerateSuccessor(first);
  }

  std::ofstream f("C:\\Users\\piotr\\Documents\\Wolfram_Automata\\picture.txt",
                  std::ios::out);
  f << frame.size() << ' ';
  f << frame.begin()->GetWidth() << ' ';

  for (auto &s : frame) {
    for (int i = 0; i < s.GetWidth(); i++) {
      f << s.Get(i) << ' ';
    }
  }
  f.close();
}
void WolframSlice() {
  //    Window screen(WIDTH, HEIGHT);

  AutomataInfo first(90);
  Slice slice(WIDTH);

  //  slice.FillRandom(50);
  slice.Set(WIDTH / 2, ON);

  //  DisplayRule(first);
  ConsoleDisplay(slice);
  Frame frame;

  std::ofstream f("C:\\Users\\piotr\\Documents\\Wolfram_Automata\\data1.txt",
                  std::ios::out);
  for (int h = 1; h <= HEIGHT; h++) {
    //        screen.PushFrame(Slicer(slice));
    //    ConsoleDisplay(slice);
    unsigned average = 0;

    for (int i = 0; i < slice.GetWidth(); ++i)
      if (slice.Get(i))
        average++;

    f << average;
    if (h < HEIGHT)
      f << " ";
    slice.GenerateSuccessor(first);
  }
  f.close();

  //  SaveFrame(frame,
  //  "C:\\Users\\piotr\\Documents\\Wolfram_Automata\\data1.txt");
}



void SaveFrame(const Frame &data, const std::string &path) {

  std::ofstream f(path, std::ios::out);

  f << data.size() << ' ' << data[0].GetWidth() << "\n";

  for (int i = 0; i < data.size(); i++) {
    for (int j = 0; j < data[i].GetWidth(); j++) {
      f << (int)data[i][j];
      if (i < data.size() - 2)
        f << " ";
    }
  }
  f.close();
}