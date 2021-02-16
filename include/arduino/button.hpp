#ifndef UAMIKE_BUTTON_HPP
#define UAMIKE_BUTTON_HPP

#include <arduino.h>

#include "../interfaces/IBeginable.hpp"
#include "../interfaces/IButton.hpp"
#include "../interfaces/IUpdatable.hpp"

#define BUTTON_DEBOUNCE_TIME 100

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
    button_debounce_time_ += ms;
    bool pressed = digitalRead(pin_) == LOW;
    pressed_this_frame_ = pressed && !is_pressed_ && button_debounce_time_ >= BUTTON_DEBOUNCE_TIME;
    if (pressed_this_frame_) button_debounce_time_ = 0;
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
  unsigned long button_debounce_time_ = 0xFFFF;
};

}  // namespace arduino
}  // namespace uamike

#endif  // UAMIKE_BUTTON_HPP
