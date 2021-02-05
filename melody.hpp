#ifndef UAMIKE_MELODY_PLAYER_HPP
#define UAMIKE_MELODY_PLAYER_HPP

namespace uamike {
namespace melody_player {

/**
 * Represents a note in a melody.
 */
struct Note
{
  unsigned int hz;        ///< Note frequency in hertz (should be greater than 31)
  unsigned int duration;  ///< Duration in musical notation (4 = quarter note, 8 = eighth note, ...)
};

struct MelodyPlayer
{
  MelodyPlayer(int pin, unsigned int tempo = 120);

  void tempo (unsigned int quarters_per_min);
  void play(const Note* melody, unsigned int n_elements);

private:
  int pin_ = 0;
  unsigned long tempo_ = 1000;
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_HPP
