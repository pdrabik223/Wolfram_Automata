//
// Created by piotr on 06/11/2021.
//

#ifndef WOLFRAM_AUTOMATA_SFML_WINDOW_IMAGE_H_
#define WOLFRAM_AUTOMATA_SFML_WINDOW_IMAGE_H_

#include "../Automata/wolfram_automata.h"
#include <string>
#include <vector>
#include <SFML/Graphics/Image.hpp>


#define ON_COLOR {0,255,255}
#define OFF_COLOR sf::Color::Transparent


/// saves frame a.k.a. std::vector<Slice> to file
/// using sfml Image
/// and this is funktor coz Idk I guess yes

static void SaveToFile(const std::string& path, std::vector<Slice> frame, unsigned width,
      unsigned height){

  float cell_size = width / frame.begin()->GetWidth();

  sf::Image image;
  image.create(width, height, sf::Color::Black);

  for(int y = 0 ;y < height ;y++){
    for (int x = 0; x < width; ++x) {

      if (frame[y / cell_size].Get(x / cell_size))
        image.setPixel(x, y, ON_COLOR);
      else {
        image.setPixel(x, y, OFF_COLOR);
      }
    }
  }
  image.saveToFile(path);

}
#endif // WOLFRAM_AUTOMATA_SFML_WINDOW_IMAGE_H_
