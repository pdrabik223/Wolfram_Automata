//
// Created by piotr on 05/11/2021.
//

#include "../Automata/wolfram_automata.h"
#include "conio.h"

#include <array>
#include <fstream>
#include <string>

#define INF 100'000'000

int MainLoop(AutomataInfo rule, const Slice &seed);

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForRandom(AutomataInfo rule);

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForPermutations(AutomataInfo rule);
/// the width of automata
int main() {
  srand(time(NULL));
  int k = 0;

  // WW for 1 and 2
  for (int i = 3; i < 255; i += 13) {
    std::string file_path =
        "../Benchmarks/BenchmarkForRandom/rule_" + std::to_string(i) + ".txt";

    std::vector<unsigned> cycle_lengths(BenchmarkForRandom(i).second);

    std::fstream file(file_path, std::ios::out);

    for (auto u : cycle_lengths)
      file << u << ' ';

    file.close();

    printf("benchmark nr:%d / %d \n", ++k, 252 / 13);
  }

  for (int i = 3; i < 255; i += 13) {
    std::string file_path = "../Benchmarks/BenchmarkForPermutations/rule_" +
                            std::to_string(i) + ".txt";

    std::vector<unsigned> cycle_lengths(BenchmarkForPermutations(i).second);

    std::fstream file(file_path, std::ios::out);

    for (auto u : cycle_lengths)
      file << u << ' ';

    file.close();

    printf("benchmark nr:%d / %d \n", ++k, 252 / 13);
  }

  return 0;
}

int MainLoop(AutomataInfo rule, const Slice &seed) {

  const unsigned kHeight = seed.GetWidth() * 1 << 2;
  const unsigned kIgnored = seed.GetWidth();

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
std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForRandom(AutomataInfo rule) {
  std::vector<unsigned> cycle_lengths;

  const unsigned kSampleSize = 1;
  const unsigned kSampleWidth = 1000;
  const unsigned kInfill = 10;

  cycle_lengths.reserve(kSampleSize);

  for (int i = 0; i < kSampleSize; i++) {
    Slice seed(kSampleWidth);
    seed.FillRandom(kInfill);
    cycle_lengths.push_back(MainLoop(rule, seed));
  }

  return {rule, cycle_lengths};
}

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForPermutations(AutomataInfo rule) {
  std::vector<unsigned> cycle_lengths;

  const unsigned kSampleRange = 16;

  cycle_lengths.reserve(kSampleRange);

  for (int i = 0; i < kSampleRange; i++) {

    for (int j = 0; j < pow(2, kSampleRange); j++) {
      Slice seed(kSampleRange);
      seed.Fill(j);

      unsigned length = MainLoop(rule, seed);

      if (std::find(cycle_lengths.begin(), cycle_lengths.end(), length) ==
          cycle_lengths.end())
        cycle_lengths.push_back(length);
    }
  }

  return {rule, cycle_lengths};
}