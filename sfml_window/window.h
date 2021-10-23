//
// Created by piotr on 05/10/2021.
//

#ifndef COA_SFML_WINDOW_WINDOW_H_
#define COA_SFML_WINDOW_WINDOW_H_

#include <SFML/Window/Event.hpp>

#include "coord.h"
#include "slicer.h"
#include <mutex>
#include <queue>
#include <vector>
class Window {
public:
  Window() = delete;
  Window(int width, int height);
  ///
  /// \param position
  /// \param width
  /// \param height
  Window(const Coord &position, int width, int height);
  Window(const Window &other);
  Window &operator=(const Window &other);
  Slicer PopFrame();
  void PushFrame(const Slicer &new_frame);

  int GetQueueSize();

  /// main window loop
  void MainLoop();

  ~Window() {
    window_thread_->join();
    delete window_thread_;
  }

void Clear();

protected:
  std::thread *window_thread_;
  int width_;
  int height_;
  unsigned no_frame_ = 0;

  std::string current_window_title_ = "Wolfram's Automata";

  std::mutex event_queue_mutex_;
  std::queue<Slicer> frame_queue_;
  sf::Event event_;

  /// position of window on the screen
  Coord position_;
};

#endif // COA_SFML_WINDOW_WINDOW_H_
