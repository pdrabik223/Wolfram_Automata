//
// Created by piotr on 05/11/2021.
//

#include "../Automata/wolfram_automata.h"
#include "conio.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

#define INF 100'000'000

int MainLoop(AutomataInfo rule, const Slice &seed);

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForRandom(AutomataInfo rule);

std::pair<AutomataInfo, unsigned> BenchmarkForRandom(AutomataInfo rule,
                                                     const unsigned k_in_fill);

/// \param rule rule witch will be used to generate successive values
/// \param seed the initial state
/// \return sudo random value in range <0,1>
double Wand(AutomataInfo rule, const Slice &seed) {
  static std::map<int, Slice> buffer;

  if (buffer.find(rule.rule_dec) == buffer.end()) {

    Slice slice(seed);
    for (int i = 0; i < seed.GetWidth() * 3; i++)
      slice.GenerateSuccessor(rule);

    buffer.insert({rule.rule_dec, slice});
  }

  buffer[rule.rule_dec].GenerateSuccessor(rule);

  double sum = 0;

  for (int i = 0; i < buffer[rule.rule_dec].GetWidth(); i++)
    if (buffer[rule.rule_dec][i])
      sum += 1;

  return sum / (double)buffer[rule.rule_dec].GetWidth();
}

struct TestCycles {
  int rule;
  std::vector<unsigned> cycle_lengths{};
  void Push(unsigned val) { cycle_lengths.push_back(val); };

  friend std::ostream &operator<<(std::ostream &os, const TestCycles &test) {
    os << test.rule;

    for (auto i : test.cycle_lengths)
      if (i == INF)
        os << "\tINF";
      else
        os << '\t' << i;
    return os;
  }
};
struct TestRandomness {
  int rule;
  std::vector<double> random_values{};
  void Push(double val) { random_values.push_back(val); };

  friend std::ostream &operator<<(std::ostream &os,
                                  const TestRandomness &test) {
    os << test.rule;

    for (auto i : test.random_values)
      os << ' ' << i;
    return os;
  }
};

int main() {
  srand(time(NULL));

  std::cout<<"===cycle test===\n";

  std::vector<TestCycles> data;

  std::fstream cycle_lengths("../Benchmarks/cycle_lengths.txt", std::ios::out);
  for (int i = 3; i < 255; i += 13) {

    TestCycles current;
    current.rule = i;

    current.Push(BenchmarkForRandom(i, 30).second);

    std::cout << "rule: " << current << "\n";
    cycle_lengths << current << "\n";
  }
  cycle_lengths.close();

  std::fstream random_numbers("../Benchmarks/random_values.txt", std::ios::out);


  std::cout<<"===randomness test===\n";
  for (int i = 3; i < 255; i += 13) {

    TestRandomness current;
    current.rule = i;
    std::cout << "rule: " << i << "\n";

    Slice seed(500);
    seed.FillRandom(30);

    for (int j = 0; j < 2000; j++) {
      current.Push(Wand(i, seed));
    }

    random_numbers << current << "\n";
  }
  random_numbers.close();
  return 0;
}

int MainLoop(AutomataInfo rule, const Slice &seed) {

  const unsigned kHeight = seed.GetWidth() - 1;
  const unsigned kIgnored = seed.GetWidth() * 4;

  Slice slice(seed);

  for (int i = 0; i < kIgnored; i++)
    slice.GenerateSuccessor(rule);

  Slice comparator(slice);
  for (int i = 0; i < kHeight; i++) {
    slice.GenerateSuccessor(rule);
    if (comparator == slice)
      return i + 1;
  }

  return INF;
}
std::pair<AutomataInfo, unsigned> BenchmarkForRandom(AutomataInfo rule,
                                                     const unsigned k_in_fill) {
  std::vector<unsigned> cycle_lengths;

  const unsigned kSampleWidth = 1000;

  Slice seed(kSampleWidth);
  seed.FillRandom(k_in_fill);

  return {rule, MainLoop(rule, seed)};
}

std::pair<AutomataInfo, std::vector<unsigned>>
BenchmarkForPermutations(AutomataInfo rule) {
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
    }
  }

  return {rule, cycle_lengths};
}