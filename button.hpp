#ifndef UAMIKE_BUTTON_HPP
#define UAMIKE_BUTTON_HPP

#include <arduino.h>

#include "IBeginable.hpp"
#include "IButton.hpp"
#include "IUpdatable.hpp"

namespace uamike {
namespace arduino {

struct Button : public IBeginable, public IUpdatable, public IButton
{
  explicit Button(int pin)
    : pin_(pin)
  {
  }

  inline void begin()
  {
    pinMode(pin_, INPUT_PULLUP);
  }

  inline void update(unsigned long ms)
  {
    bool pressed = digitalRead(pin_) == LOW;
    pressed_this_frame_ = pressed && !is_pressed_;
    is_pressed_ = pressed;
  }
  
  inline bool was_pressed_this_frame()
  {
    return pressed_this_frame_;
  }

  inline bool is_pressed()
  {
    return is_pressed_;
  }

private:

  int pin_;
  bool is_pressed_ = false;
  bool pressed_this_frame_ = false;
};

}  // namespace arduino
}  // namespace uamike

#endif  // UAMIKE_BUTTON_HPP
