//
// Created by piotr on 13/10/2021.
//

#include "slicer.h"


sf::Color Rainbow(float value, float max_value) {

  int witch_third = value / (max_value / 3.0);

  double height_in_radians;
  switch (witch_third) {
  case 0:
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;

    return sf::Color(cos(height_in_radians) * 255, sin(height_in_radians) * 255,
                     0);
  case 1:
    value -= max_value / 3;
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;
    return sf::Color(0, cos(height_in_radians) * 255,
                     sin(height_in_radians) * 255);

  case 2:
    value -= 2 * max_value / 3;
    height_in_radians = value * 3.1415 / (max_value / 3) / 2;
    return sf::Color(sin(height_in_radians) * 255, 0,
                     cos(height_in_radians) * 255);
  }

  return {255, 0, 0};
}

sf::Color& Dark(sf::Color& color){
  color.r -= 40;
  color.g -= 40;
  color.b -= 40;
  return color;

}
void Slicer::DrawToWindow(sf::RenderWindow &window, unsigned int no_frame) {
  float cell_size = window.getSize().x / slice_.GetWidth();
  sf::Vector2<float> placement(0, no_frame * cell_size);

  sf::RectangleShape cell;
  cell.setSize({cell_size, cell_size});
  cell.setOutlineThickness(0);

  for (int i = 0; i < slice_.GetWidth(); i++) {
    cell.setPosition(i * cell_size, placement.y);

    cell.setFillColor(slice_.Get(i) ? Rainbow(placement.y, window.getSize().y)
                                      : sf::Color(40,40,40));
    window.draw(cell);
  }
}
