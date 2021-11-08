//
// Created by piotr on 08/11/2021.
//

#include <array>
#include <ciso646>
#include <fstream>
#include <iostream>
#include <string>
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

#define CHUNK 64
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
    for (uint64_t i = 0l; i < width; i++)
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

  explicit operator uint64_t() { return data_.front(); }

  void FillRandom(const float &random_infill);
  void Fill(State filler);
  void Fill(uint64_t filler);

  void Set(unsigned position, bool state) {

    if (state) {

      data_[position / CHUNK] =
          data_[position / CHUNK] bitor (uint64_t) pow(2, position % CHUNK);
    } else
      data_[position / CHUNK] = data_[position / CHUNK] bitand
                                UINT64_MAX - (uint64_t)pow(2, position % CHUNK);
  }

  void Set(unsigned position, State state) { Set(position, state == ON); }

  bool Get(unsigned position) const {
    return data_[position / CHUNK] bitand (uint64_t) pow(2, position % CHUNK);
  }

protected:
  unsigned width_;
  std::vector<uint64_t> data_;
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

int main() {

  int rule;
  int width;
  int height;
  int sleep;
  double init;
  int output_device;

  std::cin >> rule;
  std::cin >> width;
  std::cin >> height;
  std::cin >> sleep;
  std::cin >> init;
  std::cin >> output_device;

  AutomataInfo info(rule);
  Slice slice(width);
  if (init == -1)
    slice.Set(width / 2, ON);
  else
    slice.FillRandom((init * 100));

  for (int i = 0; i < sleep; i++)
    slice.GenerateSuccessor(info);

  if (output_device == 1) {
    for (int i = 0; i < height; i++) {
      ConsoleDisplay(slice);
      slice.GenerateSuccessor(info);
    }
  } else {

    std::fstream file("../output_rule_" + std::to_string(rule) + ".txt");

    for (int i = 0; i < height; i++) {
      slice.GenerateSuccessor(info);
      for (int i = 0; i < slice.GetWidth(); i++)
        file << slice[i] << " ";
      file << "\n";
    }
  }

  return 0;
}

AutomataInfo::AutomataInfo(int rule) { SetRule(rule); }
void AutomataInfo::SetRule(int rule) {
  if (rule > 255)
    throw "invalid rule";

  DecimalToBinary(rule);
  rule_dec = rule;
}
void AutomataInfo::DecimalToBinary(int n) {

  rule_matrix[0][0][0] = (State)(bool)(n bitand 1);
  rule_matrix[0][0][1] = (State)(bool)(n bitand 2);
  rule_matrix[0][1][0] = (State)(bool)(n bitand 4);
  rule_matrix[0][1][1] = (State)(bool)(n bitand 8);
  rule_matrix[1][0][0] = (State)(bool)(n bitand 16);
  rule_matrix[1][0][1] = (State)(bool)(n bitand 32);
  rule_matrix[1][1][0] = (State)(bool)(n bitand 64);
  rule_matrix[1][1][1] = (State)(bool)(n bitand 128);
}

Slice Slice::GenerateSuccessor(const AutomataInfo &rule) {
  std::vector<State> copy_data(width_);
  Slice buffer(width_);

  // edges
  switch (rule.boundary_conditions) {
  case AutomataInfo::BoundaryConditions::INHERITANCE:
    buffer.Set(0, Get(0));
    buffer.Set(width_ - 1, Get(width_ - 1));
    break;

  case AutomataInfo::BoundaryConditions::LOOP_AROUND:
    buffer.Set(0, rule.ApplyRule(Get(width_ - 1), Get(0), Get(1)));
    buffer.Set(width_ - 1,
               rule.ApplyRule(Get(width_ - 2), Get(width_ - 1), Get(0)));
    break;
  }

  for (int i = 1; i < width_ - 1; i++)
    buffer.Set(i, rule.ApplyRule(Get(i - 1), Get(i), Get(i + 1)));

  *this = buffer;

  return *this;
}

void Slice::FillRandom(const float &random_infill) {
  for (int i = 0; i < width_; i++)
    if (rand() % 100 < random_infill)
      Set(i, true);
    else
      Set(i, false);
}
void Slice::Fill(State filler) {
  for (auto &d : data_) {
    d = filler;
  }
}
void Slice::SetWidth(unsigned int width) {
  width_ = width;
  data_.resize(width / CHUNK);
}
bool Slice::operator==(const Slice &rhs) const {
  return width_ == rhs.width_ && data_ == rhs.data_;
}
bool Slice::operator!=(const Slice &rhs) const { return !(rhs == *this); }

void Slice::Fill(uint64_t filler) { data_.front() = filler; }
