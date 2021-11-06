//
// Created by piotr on 05/11/2021.
//

#include "../Automata/wolfram_automata.h"
#include "conio.h"

#include <array>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#define INF 100'000'000

int MainLoop(AutomataInfo rule, const Slice &seed);

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForRandom(AutomataInfo rule);

std::pair<AutomataInfo, unsigned> BenchmarkForRandom(AutomataInfo rule,
                                                     const unsigned kInFill);
/// the width of automata
struct Test {
  int rule;
  std::vector<unsigned> cycle_lengths{};
  void Push(unsigned val) { cycle_lengths.push_back(val); };

  friend std::ostream &operator<<(std::ostream &os, const Test &test) {
    os << test.rule;

    for (auto i : test.cycle_lengths)
      os << ' ' << i;
    return os;
  }
};

int main() {
  srand(time(NULL));
  int k = 0;

  // WW for 1 and 2

  std::vector<Test> data;

  for (int i = 3; i < 255; i += 13) {

    Test current;
    current.rule = i;
    for (int j = 10; j < 80; j += 5)
      current.Push(BenchmarkForRandom(i, j).second);

    std::cout << "rule: " << current << "\n";
  }

  std::string file_path = "../Benchmarks/BenchmarkForRandom/console_output.txt";
  std::fstream file(file_path, std::ios::out);

  for (const auto& t : data) {
    file << t << '\n';
  }

  file.close();
  //  k = 0;
  //  for (int i = 0; i < 255; i += 1) {
  //    std::string file_path =
  //    "../Benchmarks/BenchmarkForPermutations/all/rule_" +
  //                            std::to_string(i) + ".txt";
  //
  //    std::vector<unsigned> cycle_lengths(BenchmarkForPermutations(i).second);
  //
  //    std::fstream file(file_path, std::ios::out);
  //
  //    for (auto u : cycle_lengths)
  //      file << u << ' ';
  //
  //    file.close();
  //
  //    printf("benchmark nr:%d / %d \n", ++k, 20);
  //  }
  system("pause");
  return 0;
}

int MainLoop(AutomataInfo rule, const Slice &seed) {

  const unsigned kHeight = seed.GetWidth() * 1 << 2;
  const unsigned kIgnored = seed.GetWidth() * 4;

  Slice slice(seed);

  for (int i = 0; i < kIgnored; i++)
    slice.GenerateSuccessor(rule);

  Slice comparator(slice);
  for (int i = 0; i < kHeight; i++) {
    slice.GenerateSuccessor(rule);
    if (comparator == slice)
      return i;
  }

  return INF;
}
std::pair<AutomataInfo, unsigned> BenchmarkForRandom(AutomataInfo rule,
                                                     const unsigned kInFill) {
  std::vector<unsigned> cycle_lengths;

  const unsigned kSampleWidth = 1000;

    Slice seed(kSampleWidth);
    seed.FillRandom(kInFill);

    return {rule, MainLoop(rule, seed)};
  }

  std::pair<AutomataInfo, std::vector<unsigned>> BenchmarkForPermutations(
      AutomataInfo rule) {
    std::vector<unsigned> cycle_lengths;

    const unsigned kSampleRange = 16;

    cycle_lengths.reserve(kSampleRange);

    for (int j = 3; j < pow(2, kSampleRange); j++) {
      Slice seed(kSampleRange);
      seed.Fill(j);

      unsigned length = MainLoop(rule, seed);

      if (std::find(cycle_lengths.begin(), cycle_lengths.end(), length) ==
          cycle_lengths.end()) {

        cycle_lengths.push_back(length);
        //      printf("new cycle length for rule %d discovered! seed : %d cycle
        //      length: %d\n",
        //             rule.rule_dec, j,length);
      }
    }

    return {rule, cycle_lengths};
  }