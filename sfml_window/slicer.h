//
// Created by piotr on 13/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_

#include "../Automata/wolfram_automata.h"
#include <SFML/Graphics/RenderWindow.hpp>
template <int WIDTH> class Slicer {
public:
  Slicer() = delete;
  Slicer(const Slice &rendered_slice);
  Slicer(const Slicer<WIDTH> &other) = default;
  Slicer &operator=(const Slicer<WIDTH> &other) = default;


public:
  void DrawToWindow(sf::RenderWindow &window, unsigned no_frame);
};

#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
