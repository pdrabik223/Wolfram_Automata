//
// Created by piotr on 29/10/2021.
//

#include "Automata/wolfram_automata.h"
#include "conio.h"

#include "sfml_window/image.h"
#include "sfml_window/window.h"
#include <array>
#include <fstream>
#include <iostream>

/// the width of automata
#define WIDTH 100
/// the height of automata
#define HEIGHT 200
#define INF 100'000'000
void WolframAnimation(unsigned screen_height, unsigned screen_width);
std::pair<int, int>
AnalyzeFrameBruteForce(const std::vector<Slice> &whole_frame);
void GenImages(std::vector<int> rules, unsigned frame_width,
               unsigned frame_height, Slice seed);
using Frame = std::vector<Slice>;
void DrawMeSlice();
int main() {
  srand(time(NULL));
  //  WolframAnimation(WIDTH, HEIGHT);
  //  DrawMeSlice();

  Slice seed(72);
  seed.FillRandom(20);



//  SaveToFile(std::string("../Praca/tape_image.png"),
//             {seed}, 500, 50, false);



  std::vector<int> rules;
  for (int i = 3; i < 255; i += 13)
    rules.push_back(i);
//
  GenImages(rules, 720, 720, seed);

  return 0;
}

void GenImages(std::vector<int> rules, unsigned frame_width,
               unsigned frame_height, Slice seed) {

  unsigned iterations = frame_height / (frame_width / seed.GetWidth());

  for (auto r : rules) {

    Slice slice(seed);

    for (int i = 0; i < seed.GetWidth() * 2; i++)
      slice.GenerateSuccessor(r);

    Frame frame;

    for (int h = 0; h < iterations; h++) {

      frame.push_back(slice);
      slice.GenerateSuccessor(r);
    }

    SaveToFile(std::string("../images/rule_"+ std::to_string(r)+"_size_" + std::to_string(seed.GetWidth())+".png"),
               frame, frame_width, frame_height, false);
  }
}

#define SCREEN true
#define FILE true
void DrawMeSlice() {

  const unsigned kSimulationWidth = 720;
  const unsigned kSimulationHeight = 720;

  const unsigned kWindowWidth = kSimulationWidth;

  const unsigned kWindowHeight = kSimulationHeight;

#if SCREEN
  Window screen(kWindowWidth, kWindowHeight);
#endif
  std::string rule;
  std::string seed;

  while (true) {

    printf("rule: ");
    std::cin >> rule;
    if (rule == "quit")
      break;

    printf("seed: ");
    std::cin >> seed;

    AutomataInfo first(std::stoi(rule));
    Slice slice(kSimulationWidth);

    if (seed.substr(0, 4) == "rand")
      slice.FillRandom(std::stoi(seed.substr(4, 2)));
    else if (seed.substr(0, 6) == "middle")
      slice.Set(kSimulationWidth / 2, ON);
    else
      slice.Fill(std::stoi(seed));

#if SCREEN
    screen.Clear();
#endif
    for (int i = 0; i < kSimulationWidth * 2; i++)
      slice.GenerateSuccessor(first);

    Frame frame;

    for (int h = 0; h < kSimulationHeight; h++) {
#if SCREEN
      screen.PushFrame(Slicer(slice));
#endif

      frame.push_back(slice);
      slice.GenerateSuccessor(first);
    }
#if FILE
    SaveToFile(std::string("../images/rule_" + rule + "_seed_" + seed + ".png"),
               frame, kWindowWidth, kWindowHeight, false);
#endif
  }
}

void WolframAnimation(unsigned screen_height, unsigned screen_width) {

  Window screen(1080, 1080);

  for (int i = 90; i < 255; i += 13) {

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
