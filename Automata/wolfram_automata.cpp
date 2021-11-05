//
// Created by piotr on 07/10/2021.
//

#include "wolfram_automata.h"
#include <iostream>

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

void Slice::Fill(int filler) {

  for (int i = 0; i < width_; i++)
    Set(i, filler bitand 1 << i);

}
