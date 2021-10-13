//
// Created by piotr on 13/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_

#include "../Automata/wolfram_automata.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Slicer {
public:
  Slicer() = delete;
  Slicer(const Slice &rendered_slice):slice_(rendered_slice){};
  Slicer(const Slicer &other) = default;
  Slicer &operator=(const Slicer &other) = default;

  void DrawToWindow(sf::RenderWindow &window, unsigned no_frame);

protected:
  Slice slice_;

};

#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
