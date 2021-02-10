#ifndef UAMIKE_IUPDATABLE_HPP
#define UAMIKE_IUPDATABLE_HPP

namespace uamike {

struct IUpdatable
{
  inline virtual void update(unsigned long delta_ms) = 0;
};

}  // namespace uamike

#endif  // UAMIKE_IUPDATABLE_HPP
