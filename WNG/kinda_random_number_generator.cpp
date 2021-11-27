//
// Created by piotr on 06/11/2021.
//
#include "../Automata/wolfram_automata.h"
#include "conio.h"

#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <string>

std::vector<double> WNG(AutomataInfo rule);
double AutoWand(AutomataInfo rule);
double Wand(AutomataInfo rule, const Slice &seed);
double PokerTest(AutomataInfo rule);
std::vector<int> DistributionTest(AutomataInfo rule);
int main() {
  srand(time(NULL));

  for (int i = 3; i < 255; i += 13) {

    std::string file_path = "../WNG/cycle/rule_" + std::to_string(i) + ".txt";
    std::fstream file(file_path, std::ios::out);
    std::vector<double> data = WNG(i);
    file << i << '\t';
    file << data.size() << '\t';
    for (auto j : data)
      file << j << ' ';
    file.close();
    std::cout << "rule: " << i << "\n";
  }

  //    for (int i = 3; i < 255; i += 13) {
  //    std::string file_path = "../WNG/dist/rule_"+ std::to_string(i)+".txt";
  //    std::fstream file(file_path, std::ios::out);
  //
  //      file << i << "\t";
  //      std::cout<<"rule: "<<i<<"\n";
  //      std::vector<int> distribution = DistributionTest(i);
  //      file << distribution.size() << "\t";
  //      for (auto j : distribution) {
  //        file << j << " ";
  //      }
  //      file << "\n";
  //
  //    file.close();
  //    }

  //  int numb = 204;
  //
  //  std::string file_path = "../WNG/dist/rule_" + std::to_string(numb) +
  //  ".txt"; std::fstream file(file_path, std::ios::out);
  //
  //  file << numb << "\t";
  //  std::cout << "rule: " << numb << "\n";
  //  std::vector<int> distribution = DistributionTest(numb);
  //  file << distribution.size() << "\t";
  //  for (auto j : distribution) {
  //    file << j << " ";
  //  }
  //  file << "\n";
  //
  //  file.close();

  return 0;
}

std::vector<double> WNG(AutomataInfo rule) {

  std::vector<double> generated_numbers;

  generated_numbers.reserve(10000);
  for (int i = 0; i < 10000; i++) {
    generated_numbers.push_back(AutoWand(rule));
  }
  return generated_numbers;
}

double AutoWand(AutomataInfo rule) {

  Slice seed(500);
  seed.FillRandom(25);
  return Wand(rule, seed);
}

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
std::vector<int> DistributionTest(AutomataInfo rule) {

  std::vector<int> output;

  Slice seed(500);
  seed.FillRandom(20);

  for (int j = 0; j < 10000; j++) {
    int number = 0;

    for (int i = 0; i < 50; i++) {
      number += Wand(rule, seed) < 0.5 ? -1 : 1;
    }
    output.push_back(number);
  }
  return output;
}

double PokerTest(AutomataInfo rule) {

  const unsigned kN = 10'000;

  std::vector<double> r_values(kN);

  // mam 5 typów kart -> A B C D E
  // mam kN / 5 graczy
  std::array<std::array<int, 5>, kN> hands{};

  for (int i = 0; i < kN; i++)

    for (int j = 0; j < 5; j++) {

      double rand = AutoWand(rule);

      hands[i][j] = (int)(rand * 4.9999999);
    }
  std::array<int, kN> skalar_hands{};

  for (int i = 0; i < kN; i++) {

    std::array<int, 5> cards{0, 0, 0, 0, 0};

    for (int j = 0; j < 5; j++)
      cards[hands[i][j]]++;

    for (int j = 0; j < 5; j++) {

      if (cards[j] >= 1)
        cards[j]--;

      skalar_hands[i] += cards[j];
    }
  }

  double k = 5;
  std::vector<double> expected = {
      ((k - 1.) * (k - 2.) * (k - 3.) * (k - 4.)) / pow(k, 4),
      (10. * (k - 1.) * (k - 2.) * (k - 3.)) / pow(k, 4),
      (15. * (k - 1.) * (k - 2.)) / pow(k, 4),
      (10. * (k - 1.) * (k - 2.)) / pow(k, 4),
      (10. * (k - 1.)) / pow(k, 4),
      (5. * (k - 1.)) / pow(k, 4),
      1. / pow(k, 5)};

  std::vector<double> received = {0, 0, 0, 0, 0, 0, 0};

  for (int i = 0; i < kN; i++) {
    received[skalar_hands[i]]++;
  }
  for (auto &i : received)
    i /= kN;

  double cum_mistake = 0;

  for (int i = 0; i < 7; i++) {
    std::cout << "expected:    \t" << expected[i];
    std::cout << " received:\t" << received[i] << std::endl;

    double abs_2 = abs(expected[i] - received[i]);
    cum_mistake += (abs_2 / expected[i]) * 100;
  }
  return abs(expected[3] - received[3]) / expected[3];
}