//
// Created by piotr on 07/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#define WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#include <array>
#include <ciso646>
#include <vector>
struct AutomataInfo {
  AutomataInfo(int rule);

  enum class BoundaryConditions { INHERITANCE, LOOP_AROUND };
  int rule_dec;
  std::array<std::array<std::array<uint8_t, 2>, 2>, 2> rule_matrix;
  BoundaryConditions boundary_conditions = BoundaryConditions::LOOP_AROUND;

  uint8_t ApplyRule(uint8_t a, uint8_t x, uint8_t b) const {
    return rule_matrix[a][x][b];
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
      data_.push_back(0);
  };
  Slice(const Slice &other) = default;
  Slice &operator=(const Slice &other) = default;
  Slice GenerateSuccessor(const AutomataInfo &rule);
  unsigned int GetWidth() const { return width_; }
  uint8_t &operator[](unsigned position) { return data_[position]; }
  uint8_t operator[](unsigned position) const { return data_[position]; }

private:
protected:
  unsigned width_;
  std::vector<uint8_t> data_;
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
