#ifndef UAMIKE_TETRISINO_GAMECONTROL_HPP
#define UAMIKE_TETRISINO_GAMECONTROL_HPP

#include "IButton.hpp"
#include "IUpdatable.hpp"
#include "melody.hpp"
#include "Piece.hpp"
#include "screen.hpp"

namespace uamike {
namespace tetrisino {

struct GameControl : public IUpdatable
{
  using Player = melody_player::MelodyPlayer<8>;

  GameControl(IButton& left, IButton& right, IButton& rotate, IButton& place, Player& player)
    : left_(left), right_(right), rotate_(rotate), place_(place), player_(player)
  {
  }
  
  inline void update(unsigned long ms) override
  {
    bool left = left_.was_pressed_this_frame();
    bool right = right_.was_pressed_this_frame();
    bool rotate = rotate_.was_pressed_this_frame();
    bool place = rotate_.was_pressed_this_frame();
  
    place_was_pressed_ |= place;
    bool should_go_down = place_was_pressed_;
  
    static unsigned long down_ms = 0;
    down_ms += ms;
    if (down_ms >= 1500)
    {
      down_ms -= 1500;
      should_go_down = true;
    }
  
    if (should_go_down)
    {
      screen_.remove_piece(*piece_, x_, y_);
      --y_;
      if (screen_.check_piece(*piece_, x_, y_))
      {
        screen_.add_piece(*piece_, x_, y_);
        return;
      }
  
      ++y_;
      screen_.add_piece(*piece_, x_, y_);
  
      // TODO: check lines
  
      piece_ = Piece::random_piece();
      x_ = 2;
      y_ = 31;
      place_was_pressed_ = false;
    }
  
    if (left || right || rotate)
    {
      screen_.remove_piece(*piece_, x_, y_);
      
      char save_x = x_;
      char save_y = y_;
      const Piece* save_piece = piece_;
      
      if (left) x_--;
      if (right) x_++;
      if (rotate) piece_ = Piece::rotate(piece_);
  
      if (!screen_.check_piece(*piece_, x_, y_))
      {
        x_ = save_x;
        y_ = save_y;
        piece_ = save_piece;
      }
      
      screen_.add_piece(*piece_, x_, y_);
    }
  }

private:
  IButton& left_;
  IButton& right_;
  IButton& rotate_;
  IButton& place_;
  Player& player_;
  
  Screen screen_;
  const Piece* piece_ = Piece::random_piece();
  char x_ = 2;
  char y_ = 31;

  bool place_was_pressed_ = false;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_PIECE_HPP
