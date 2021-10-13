//
// Created by piotr on 13/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_WINDOW_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_WINDOW_H_
#include <SFML/Window/Event.hpp>

#include "coord.h"
#include "slicer.h"
#include <mutex>
#include <queue>
#include <vector>

class SettingsWindow {
  enum class Buttons{
    RUN_AUTOMATA,


  };
  enum class TextFields{


  };
public:
  SettingsWindow() = delete;
  SettingsWindow(int width, int height);
  SettingsWindow(const SettingsWindow& other) = delete;
  SettingsWindow& operator=(const SettingsWindow& other) = delete;
  void MainLoop();

  ~SettingsWindow(){
    window_thread_->join();
    delete window_thread_;

  }
protected:

  std::thread *window_thread_;
  int width_;
  int height_;
  sf::Event event_;

};

#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_SETTINGS_WINDOW_H_
