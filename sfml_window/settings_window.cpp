//
// Created by piotr on 13/10/2021.
//

#include "settings_window.h"
SettingsWindow::SettingsWindow(int width, int height)
    : width_(width), height_(height) {
  window_thread_ = new std::thread(&SettingsWindow::MainLoop, this);
}
void SettingsWindow::MainLoop() {
  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(width_, height_), "Automata Settings",
                          sf::Style::Default, settings);
  window.setPosition({0, 0});
  window.clear(sf::Color(95, 95, 95));
  window.display();
  while (window.isOpen()) {

    // check all the window's events that were triggered since the last
    // iteration of the loop
    while (window.waitEvent(event_)) {
      if (event_.type == sf::Event::Closed)
        window.close();

      window.display();
    }
  }
}
