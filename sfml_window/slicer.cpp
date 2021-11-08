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

sf::Color &Dark(sf::Color &color) {
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
    if (PROFESSIONAL_LOOK)
      cell.setFillColor(slice_.Get(i) ? CYAN : GRAY);
    else
      cell.setFillColor(slice_.Get(i) ? Rainbow(placement.y, window.getSize().y)
                                      : GRAY);

    window.draw(cell);
  }
}



/// saves frame a.k.a. std::vector<Slice> to file
/// using sfml Image
/// and this is funktor coz Idk I guess yes

 void SaveToFile(const std::string &path, std::vector<Slice> frame,
                unsigned width, unsigned height, bool use_rainbow) {

  float cell_size = width / frame.begin()->GetWidth();

  sf::Image image;

  int x_border = 5;
  int y_border = 5;

  image.create(width + x_border*2, height + y_border*2, sf::Color::Black);

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; ++x) {

      if (frame[y / cell_size].Get(x / cell_size))
        if (use_rainbow)
          image.setPixel(x + x_border, y + y_border,  Rainbow(y,height));
        else
          image.setPixel(x + x_border, y + y_border, sf::Color::White);
      else {
        image.setPixel(x + x_border, y + y_border, sf::Color(195,195,195));
      }
    }
  }
  image.saveToFile(path);
}