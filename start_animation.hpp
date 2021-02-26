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
constexpr InputState c_input_down_left {true, false, true, false, false};
constexpr InputState c_input_down_right {false, true, true, false, false};
constexpr InputState c_input_rotate {false, false, false, true, false};

const InitialAnimationStep animation[] =
{
  //* S
  //   x
  // xxx
  {4, c_input_down_right, 36},
  {128, {}, 0},
  // xxx
  //   x
  {8, c_input_down_right, 36},
  {128, {}, 0},
  // x
  // xxx
  {8, c_input_down, 4},
  {255, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  // xxx
  // x
  {4, c_input_down, 4},
  {255, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  //*/

  //* I
  //  x
  // xxx
  {13, c_input_down_left, 36},
  {128, {}, 0},
  //  x
  //  x
  //  x
  //  x
  {2, c_input_down, 3},
  {255, c_input_down_left, 3},
  {255, c_input_down, 36},
  {128, {}, 0},
  // xxx
  //  x
  {13, c_input_down_left, 3},
  {255, c_input_rotate, 2},
  {255, c_input_down_left, 36},
  {128, {}, 0},
  //*/

  //* R
  //   xx
  //    x
  //    x
  {5, c_input_down_right, 36},
  {128, {}, 0},
  //    x
  //   xx
  //   x
  {18, c_input_down_right, 36},
  {128, {}, 0},
  //  x
  //  x
  //  x
  //  x
  {2, c_input_down, 4},
  {255, c_input_down_right, 1},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  x
  //  x
  // xx
  {7, c_input_down, 4},
  {255, c_input_down_right, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  x
  //  x
  // xx
  {7, c_input_down, 4},
  {255, c_input_rotate, 1},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  //*/

  //* T
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  // xxxx
  {1, c_input_down, 3},
  {255, c_input_down_left, 36},
  {128, {}, 0},
  // xxxx
  {1, c_input_down, 3},
  {255, c_input_down_left, 36},
  {128, {}, 0},
  //*/

  //* E
  // x
  // xxx
  {8, c_input_down, 1},
  {255, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  // xxx
  // x
  {4, c_input_down, 1},
  {255, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  // x
  // xxx
  {8, c_input_down, 1},
  {255, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  // xxx
  // x
  {4, c_input_rotate, 2},
  {255, c_input_down_right, 36},
  {128, {}, 0},
  //*/

  //* T
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  //  xx
  //  xx
  {0, c_input_down, 3},
  {255, c_input_down_left, 2},
  {255, c_input_down, 36},
  {128, {}, 0},
  // xxxx
  {1, c_input_down, 3},
  {255, c_input_down_left, 36},
  {128, {}, 0},
  // xxxx
  {1, c_input_down, 3},
  {255, c_input_down_left, 36},
  {128, {}, 0},
  //*/
};
constexpr byte c_total_actions = sizeof(animation)/sizeof(animation[0]);

struct InitialAnimation
{
  void begin()
  {
    action_index_ = 0;
    step_count_ = 0;
  }

  void stop()
  {
    action_index_ = c_total_actions;
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
        byte next_piece = animation[action_index_].piece_id;
        if (next_piece != 255)
        {
          piece = Piece::get_piece(next_piece);
        }
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
