//
// Created by piotr on 13/10/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
#include <corecrt_math.h>
#include "../Automata/wolfram_automata.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#define PROFESSIONAL_LOOK true
#define GRAY sf::Color(29,29,29)
#define CYAN sf::Color(0,255,255)
#define OFF_COLOR sf::Color::Transparent


sf::Color Rainbow(float value, float max_value);
void SaveToFile(const std::string &path, std::vector<Slice> frame,
                unsigned width, unsigned height, bool use_rainbow);
class Slicer {
public:
  Slicer() = delete;
  Slicer(const Slice &rendered_slice):slice_(rendered_slice){};
  Slicer(const Slicer &other) = default;
  Slicer &operator=(const Slicer &other) = default;

  void DrawToWindow(sf::RenderWindow &window, unsigned no_frame);

  static bool professional_look_;
protected:
  Slice slice_;
};


#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_SLICER_H_
