#ifndef UAMIKE_TETRISINO_IINPUTCONTROLLER_HPP
#define UAMIKE_TETRISINO_IINPUTCONTROLLER_HPP

namespace uamike {
namespace tetrisino {

// Forward declaration of input state
struct InputState;

/// A generic interface for getting input state
struct IInputController
{
  virtual void get_input_state(InputState& input) = 0;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_IINPUTCONTROLLER_HPP
