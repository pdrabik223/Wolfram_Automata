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
  // edges
  switch (rule.boundary_conditions) {
  case AutomataInfo::BoundaryConditions::INHERITANCE:
    copy_data[0] = data_[0];
    copy_data.back() = data_.back();
    break;
  case AutomataInfo::BoundaryConditions::LOOP_AROUND:
    copy_data[0] = rule.ApplyRule(data_.back(), data_[0], data_[1]);
    copy_data.back() =
        rule.ApplyRule(data_[width_ - 2], data_.back(), data_[0]);
    break;
  }

  for (int i = 1; i < width_ - 1; i++)
    copy_data[i] = rule.ApplyRule(data_[i - 1], data_[i], data_[i + 1]);

  data_ = copy_data;
  return *this;
}
void Slice::FillRandom(const float &random_infill) {
  for (auto &d : data_)
    if (rand() % 100 < random_infill)
      d = ON;
    else
      d = OFF;
}
void Slice::Fill(State filler) {
  for (auto &d : data_) {
    d = filler;
  }
}
void Slice::SetWidth(unsigned int width) {
  width_ = width;
  data_.resize(width);
}
