#ifndef UAMIKE_TETRISINO_INPUTSTATE_HPP
#define UAMIKE_TETRISINO_INPUTSTATE_HPP

namespace uamike {
namespace tetrisino {

/// Input state
struct InputState
{
  bool left;    ///< Move piece left
  bool right;   ///< Move piece right
  bool down;    ///< Move piece down
  bool rotate;  ///< Rotate piece
  bool place;   ///< Drop piece
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_INPUTSTATE_HPP
