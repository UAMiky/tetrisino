/**
 * A melody player for Arduino
 * by Miguel Company (UAMike)
 */

#ifndef UAMIKE_MELODY_PLAYER_NOTE_HPP
#define UAMIKE_MELODY_PLAYER_NOTE_HPP

namespace uamike {
namespace melody_player {

/**
 * Represents a note in a melody.
 */
struct Note
{
  unsigned int hz;        ///< Note frequency in hertz (should be greater than 31)
  unsigned int duration;  ///< Duration in musical notation x 100 (400 = quarter note, 800 = eighth note, ...)
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_NOTE_HPP
