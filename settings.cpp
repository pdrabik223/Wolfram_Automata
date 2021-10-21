//
// Created by piotr on 13/10/2021.
//

#include "settings.h"
#include <iostream>
void Settings::MainLoop() {

  std::string message;
  while (1 < 2) {
    std::cin >> message;
    switch(Decode(message)){

    case EXIT_SETTINGS:

      return;
    case RUN_AUTOMATA:

//      for (int i = 0; i < 1080; i++) {
//        screen.PushFrame(Slicer(slice));
//        slice.GenerateSuccessor(first);
//      }
      break;
    case REFRESH_SCREEN:
      break;
    }
  }
}
Settings::Settings() {}
Settings::Action Settings::Decode(std::string &message) {

  int i;
  for (i = 0; i < commands_.size(); i++) {
    if (commands_[i].size() <= message.size())
      if (commands_[i] == message.substr(0, commands_[i].size()))
        break;
  }
//  if (i == commands_.size())
//    return;

  message = message.substr(0, commands_[i].size());

  switch (i) {
    // set screen width
  case 1:
    window_width_ = std::stoi(message);
    break;

    // set screen height
  case 2:
    window_height_ = std::stoi(message);
    break;
    // set slice width
  case 3:
    slice_.SetWidth(std::stoi(message));
    break;
    // set rule
  case 4:
    automata_info_.SetRule(std::stoi(message));
    break;
    // fill random
  case 5:
    slice_.FillRandom(std::stoi(message));
    break;
    // fill on
  case 6:
    slice_.Fill(ON);
    break;
    // fill off
  case 7:
    slice_.Fill(OFF);
    break;

    // flip
  case 8:
    slice_[std::stoi(message)] = slice_[std::stoi(message)] == ON ? OFF : ON;

    break;
    // help
  case 9:
    printf("help stuff\n");
    break;

    // settings
  case 10:
    printf("window width:\t%d\nwindow height:\t%d\nslice width:%d\n ",window_width_,window_height_,slice_.GetWidth());
    break;

    // info
  case 11:
    DisplayRule(automata_info_);
    break;
  }
return RUN_AUTOMATA;
}
