//
// Created by piotr on 13/10/2021.
//

#include "slicer.h"
void Slicer::DrawToWindow(sf::RenderWindow &window, unsigned int no_frame) {
  float cell_size = window.getSize().x / slice_.GetWidth();
  sf::Vector2<float> placement(0, no_frame * cell_size);

  sf::RectangleShape cell;
  cell.setSize({cell_size, cell_size});
  cell.setOutlineThickness(0);

  for (int i = 0; i < slice_.GetWidth(); i++) {
    cell.setPosition(i * cell_size, placement.y);
    if (slice_[i] == ON)
      cell.setFillColor(sf::Color(252,64,7));
    else
      cell.setFillColor(sf::Color(195,195,195));
    window.draw(cell);
  }
}
