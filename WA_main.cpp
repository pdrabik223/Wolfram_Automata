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
void SaveChangesInWeight(int rule, const int frame_height,
                         const int frame_width);
/// deadline 7 listopada 23:59

int main() {
  srand(time(NULL));

  // piotr: 3
  // mateusz: 7

  // rule %13 = out  number
  // so every rule that %13 == 3 is mine
  // exercise 1

//  SaveChangesInWeight(90,1000,1000);
  return 0;
}
void SaveWeightsToFile() {

  AutomataInfo first(90);
  Slice slice(WIDTH);

  //  slice.FillRandom(50);
  slice.Set(WIDTH / 2, ON);

  DisplayRule(first);
  ConsoleDisplay(slice);
  Frame frame;

  std::ofstream f("C:\\Users\\piotr\\Documents\\Wolfram_Automata\\weights.txt",
                  std::ios::out);
  for (int h = 1; h <= HEIGHT; h++) {
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
}
void SaveChangesInWeight(int rule, const int frame_height,
                         const int frame_width) {
  AutomataInfo first(rule);
  Slice slice(frame_width);

  //  slice.FillRandom(50);
  slice.Set(frame_width / 2, ON);

  DisplayRule(first);
  ConsoleDisplay(slice);
  Frame frame;

  std::ofstream f("C:\\Users\\piotr\\Documents\\Wolfram_Automata\\changes_in_weights_" +
                      std::to_string(rule) + "_middle_on" + ".txt",
                  std::ios::out);
  int prev_average = 0;

  for (int h = 1; h <= frame_height; h++) {
    int average = 0;
    for (int i = 0; i < slice.GetWidth(); ++i)

      if (slice.Get(i))
        average++;

    f << prev_average - average;
    if (h < frame_height)
      f << " ";
    prev_average = average;

    slice.GenerateSuccessor(first);
  }
  f.close();
}
