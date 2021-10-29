//
// Created by piotr on 29/10/2021.
//

#include "Automata/wolfram_automata.h"
#include "conio.h"

#include "sfml_window/window.h"
#include <array>
#include <fstream>

/// the width of automata
#define WIDTH 800
/// the height of automata
#define HEIGHT 1000

void WolframAnimation(unsigned screen_height, unsigned screen_width);
std::pair<int, int>
AnalyzeFrameBruteForce(const std::vector<Slice> &whole_frame);
int main() {
  srand(time(NULL));
  WolframAnimation(WIDTH, HEIGHT);

  return 0;
}

void WolframAnimation(unsigned screen_height, unsigned screen_width) {

  Window screen(800, 1000);

  for (int i = 3; i < 255; i += 13) {

    AutomataInfo first(i);

    Slice slice(WIDTH);

    slice.FillRandom(10);
    screen.Clear();
    std::vector<Slice> whole_frame;
    whole_frame.reserve(HEIGHT);

    for (int h = 0; h < HEIGHT; h++) {
      screen.PushFrame(Slicer(slice));
      whole_frame.push_back(slice);
      slice.GenerateSuccessor(first);
    }
    DisplayRule(first);

    printf("this one is category: %d with repetition circle every %d. \n\n",
           AnalyzeFrameBruteForce(whole_frame).first,
           AnalyzeFrameBruteForce(whole_frame).second);

    while (screen.GetQueueSize() != 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    whole_frame.clear();

    //    char key;
    getch();
  }
}

/// 1st class rules that generate stable image for example 204
/// 2nd class cyclic they have repetitive pattern for example 6
/// 3rd class exploding, for example 90
/// 4 leftovers lol
/// first val -> witch class it's grouped to
/// second val -> how long is repetition circle
std::pair<int, int>
AnalyzeFrameBruteForce(const std::vector<Slice> &whole_frame) {

  if (whole_frame[whole_frame.size() - 1] ==
      whole_frame[whole_frame.size() - 2])
    return {1, 1};

  int k = 1;
  for (int i = whole_frame.size() - 2; i >= 0; --i) {
    if (whole_frame[whole_frame.size() - 1] == whole_frame[i])
      return {2, k};
    else
      ++k;
  }
  return /* idk */ {3, 0};
}