#ifndef UAMIKE_TETRISINO_INPUTSTATE_HPP
#define UAMIKE_TETRISINO_INPUTSTATE_HPP

namespace uamike {
namespace tetrisino {

/// Input state
struct InputState
{
  bool left = false;    ///< Move piece left
  bool right = false;   ///< Move piece right
  bool down = false;    ///< Move piece down
  bool rotate = false;  ///< Rotate piece
  bool place = false;   ///< Drop piece
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_INPUTSTATE_HPP
