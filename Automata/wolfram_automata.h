//
// Created by piotr on 07/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#define WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#include <array>
#include <ciso646>
#include <vector>

enum State{
  OFF,
  ON
};
struct AutomataInfo {
  AutomataInfo(int rule);

  enum class BoundaryConditions { INHERITANCE, LOOP_AROUND };
  int rule_dec;
  std::array<std::array<std::array<State, 2>, 2>, 2> rule_matrix;
  BoundaryConditions boundary_conditions = BoundaryConditions::LOOP_AROUND;

  State ApplyRule(State a, State x, State b) const {
    return rule_matrix[(int)a][(int)x][(int)b];
  };
  void DecimalToBinary(int n);
  int ComputeClass() const {return 0;};
};
  static void DisplayRule(const AutomataInfo& info){
    printf( "rule: %d class: \n",info.rule_dec,info.ComputeClass());
    printf("000 -> %d \n", (int)info.rule_matrix[0][0][0]);
    printf("001 -> %d \n", (int)info.rule_matrix[0][0][1]);
    printf("010 -> %d \n", (int)info.rule_matrix[0][1][0]);
    printf("011 -> %d \n", (int)info.rule_matrix[0][1][1]);
    printf("100 -> %d \n", (int)info.rule_matrix[1][0][0]);
    printf("101 -> %d \n", (int)info.rule_matrix[1][0][1]);
    printf("110 -> %d \n", (int)info.rule_matrix[1][1][0]);
    printf("111 -> %d \n", (int)info.rule_matrix[1][1][1]);
  }

class Slice {
public:

  Slice(unsigned width) : width_(width) {
    if (width < 3)
      throw "your size is to small";
    data_.reserve(width);
    for(int i = 0 ;i < width;i++)
      data_.push_back(OFF);
  };
  Slice(const Slice &other) = default;
  Slice &operator=(const Slice &other) = default;
  Slice GenerateSuccessor(const AutomataInfo &rule);
  unsigned int GetWidth() const { return width_; }
  State &operator[](unsigned position) { return data_[position]; }
  State operator[](unsigned position) const { return data_[position]; }

private:
protected:
  unsigned width_;
  std::vector<State> data_;
};


// todo make iterator for slice class
static void ConsoleDisplay(const Slice &slice) {
  for (int i = 0; i < slice.GetWidth(); i++)
    if (slice[i])
      printf("#");
    else
      printf(" ");

  printf("\n");
}

#endif // WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
