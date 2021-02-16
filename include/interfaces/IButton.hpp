#ifndef UAMIKE_IBUTTON_HPP
#define UAMIKE_IBUTTON_HPP

namespace uamike {

struct IButton
{
  inline virtual bool was_pressed_this_frame() = 0;

  inline virtual bool is_pressed() = 0;
};

}  // namespace uamike

#endif  // UAMIKE_IBUTTON_HPP
