#ifndef UAMIKE_TETRISINO_FOURBUTTONSINPUTCONTROLLER_HPP
#define UAMIKE_TETRISINO_FOURBUTTONSINPUTCONTROLLER_HPP

#include "IInputController.hpp"
#include "InputState.hpp"
#include "include/interfaces/IButton.hpp"

namespace uamike {
namespace tetrisino {

/// An input controller for a four buttons implementation
struct FourButtonsInputController : public IInputController
{
  FourButtonsInputController(IButton& left, IButton& right, IButton& rotate, IButton& place)
    : left_(left), right_(right), rotate_(rotate), place_(place)
  {
  }
  
  void get_input_state(InputState& input) override
  {
    input.left = left_.was_pressed_this_frame();
    input.right = right_.was_pressed_this_frame();
    input.rotate = rotate_.was_pressed_this_frame();
    input.place = place_.was_pressed_this_frame();
  }

private:

  IButton& left_;
  IButton& right_;
  IButton& rotate_;
  IButton& place_;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_FOURBUTTONSINPUTCONTROLLER_HPP
