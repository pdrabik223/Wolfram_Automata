//
// Created by piotr on 07/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#define WOLFRAM_AUTOMATA_WOLFRAMS_AUTOMATA_H
#include <array>
#include <ciso646>
#include <vector>

enum State { OFF, ON };

struct AutomataInfo {
  AutomataInfo(int rule);
  void SetRule(int rule);

  enum class BoundaryConditions { INHERITANCE, LOOP_AROUND };
  int rule_dec;
  std::array<std::array<std::array<State, 2>, 2>, 2> rule_matrix;
  BoundaryConditions boundary_conditions = BoundaryConditions::LOOP_AROUND;

  State ApplyRule(State a, State x, State b) const {
    return rule_matrix[(int)a][(int)x][(int)b];
  };
  bool ApplyRule(bool a, bool x, bool b) const {
    return rule_matrix[Int(a)][Int(x)][Int(b)];
  };

  void DecimalToBinary(int n);
  static unsigned Int(bool val) { return val ? 1 : 0; }
};
static void DisplayRule(const AutomataInfo &info) {
  printf("rule: %d\n", info.rule_dec);
  printf("000 -> %d \n", (int)info.rule_matrix[0][0][0]);
  printf("001 -> %d \n", (int)info.rule_matrix[0][0][1]);
  printf("010 -> %d \n", (int)info.rule_matrix[0][1][0]);
  printf("011 -> %d \n", (int)info.rule_matrix[0][1][1]);
  printf("100 -> %d \n", (int)info.rule_matrix[1][0][0]);
  printf("101 -> %d \n", (int)info.rule_matrix[1][0][1]);
  printf("110 -> %d \n", (int)info.rule_matrix[1][1][0]);
  printf("111 -> %d \n", (int)info.rule_matrix[1][1][1]);
}

#define CHUNK 32
class Slice {
public:
  Slice() : width_(0){};
  Slice(unsigned width) : width_(width) {
    if (width < 3)
      throw "your size is to small";
    width = width / CHUNK;
    if (width_ % CHUNK != 0)
      width++;

    data_.reserve(width);
    for (int i = 0; i < width; i++)
      data_.push_back(0);
  };

  bool operator==(const Slice &rhs) const;
  bool operator!=(const Slice &rhs) const;
  void SetWidth(unsigned int width);
  Slice(const Slice &other) = default;
  Slice &operator=(const Slice &other) = default;
  Slice GenerateSuccessor(const AutomataInfo &rule);
  unsigned int GetWidth() const { return width_; }
  //  State &operator[](unsigned position) { return data_[position]; }
  State operator[](unsigned position) const {
    if (Get(position))
      return ON;
    else
      return OFF;
  }

  void FillRandom(const float &random_infill);
  void Fill(State filler);
  void Fill(int filler);

  void Set(unsigned position, bool state) {

    if (state)
      data_[position / CHUNK] = data_[position / CHUNK] bitor 1 << position % CHUNK;
    else
      data_[position / CHUNK] =
          data_[position / CHUNK] bitand INT64_MAX - (1 << position % CHUNK);
  }

  void Set(unsigned position, State state) { Set(position, state == ON); }

  bool Get(unsigned position) const {
    return data_[position / CHUNK] bitand 1 << position % CHUNK;
  }

protected:
  unsigned width_;
  std::vector<uint32_t> data_;
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
