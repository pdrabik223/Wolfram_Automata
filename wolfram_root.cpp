//
// Created by piotr on 30/10/2021.
//

#include "Automata/wolfram_automata.h"
#include "conio.h"

#include <array>
#include <fstream>

/// the width of automata
#define WIDTH 800
/// the height of automata
#define HEIGHT 1000
using Frame = std::vector<Slice>;

void SaveToRoot();

int main() {
  srand(time(NULL));
  SaveToRoot();
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