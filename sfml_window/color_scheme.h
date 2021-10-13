//
// Created by piotr on 06/10/2021.
//

#ifndef COA_SFML_WINDOW_COLOR_SHEME_H_
#define COA_SFML_WINDOW_COLOR_SHEME_H_

#include <SFML/Graphics/Color.hpp>
struct ColorScheme {

  ColorScheme() = default;
  ColorScheme(const ColorScheme &other) = default;
  ColorScheme &operator=(const ColorScheme &other) = default;


  void LoadCyanSet();

  sf::Color background = sf::Color::Black;
  sf::Color on_cell = sf::Color::White;
  sf::Color off_cell = sf::Color::Black;
  sf::Color point_of_interest = sf::Color::Yellow;
  sf::Color text = sf::Color::White;
};

#endif // COA_SFML_WINDOW_COLOR_SHEME_H_
