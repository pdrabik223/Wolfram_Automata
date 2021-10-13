//
// Created by piotr on 13/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_H_
#include <SFML/Window/Event.hpp>

#include "sfml_window/coord.h"
#include "sfml_window/slicer.h"
#include <mutex>
#include <queue>
#include <vector>

class Settings {
  enum Action {
    EXIT_SETTINGS, RUN_AUTOMATA,
    REFRESH_SCREEN
  };

public:
  Settings();

private:
  void MainLoop();
  Action Decode(std::string &message);

protected:
  std::vector<std::string> commands_ = {"set screen width",
                                        "set screen height",
                                        "set slice width",
                                        "set rule",
                                        "fill random",
                                        "fill on",
                                        "fill off",
                                        "flip",
                                        "help",
                                        "settings",
                                        "info"};
  AutomataInfo automata_info_ = {90};
  Slice slice_ = {600};
  unsigned window_width_ = 600;
  unsigned window_height_ = 1080;
};

#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_H_
