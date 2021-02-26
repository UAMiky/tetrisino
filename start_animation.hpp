#ifndef UAMIKE_TETRISINO_START_ANIMATION_HPP
#define UAMIKE_TETRISINO_START_ANIMATION_HPP

#include "InputState.hpp"
#include "piece.hpp"
#include "screen.hpp"

namespace uamike {
namespace tetrisino {

struct InitialAnimationStep
{
  byte piece_id;
  InputState input;
  byte input_times;
};

constexpr InputState c_input_down {false, false, true, false, false};

const InitialAnimationStep animation[] =
{
  {4, c_input_down, 36}
};
constexpr byte c_total_actions = 1;

struct InitialAnimation
{
  void begin()
  {
    action_index_ = 0;
    step_count_ = 0;
  }

  bool is_playing()
  {
    return action_index_ < c_total_actions;
  }

  void step(Screen& screen, const Piece*& piece, char& x, char& y)
  {
    if (nullptr == piece)
    {
      piece = Piece::get_piece(animation[action_index_].piece_id);
      x = 2;
      y = 23;
    }

    bool could_move = screen.move_piece(piece, animation[action_index_].input, x, y);
    ++step_count_;
    if (!could_move || step_count_ >= animation[action_index_].input_times)
    {
      step_count_ = 0;
      ++action_index_;
      if (action_index_ < c_total_actions)
      {
        piece = Piece::get_piece(animation[action_index_].piece_id);
      }
    }
  }

private:
  byte action_index_ = 0;
  byte step_count_ = 0;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_START_ANIMATION_HPP
