#ifndef UAMIKE_ISTOPPABLE_HPP
#define UAMIKE_ISTOPPABLE_HPP

namespace uamike {

struct IStoppable
{
  inline virtual void stop() = 0;
};

}  // namespace uamike

#endif  // UAMIKE_ISTOPPABLE_HPP
