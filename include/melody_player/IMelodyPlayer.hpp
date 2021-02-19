/**
 * A melody player for Arduino
 * by Miguel Company (UAMike)
 */

#ifndef UAMIKE_MELODY_PLAYER_IMELODYPLAYER_HPP
#define UAMIKE_MELODY_PLAYER_IMELODYPLAYER_HPP

#include "../interfaces/IStoppable.hpp"

namespace uamike {
namespace melody_player {

// Forward declaration of Note
struct Note;

/// An interface for a melody player
struct IMelodyPlayer : public IStoppable
{
  /**
   * Set a new tempo.
   * 
   * @param qpm  New tempo in quarter notes per minute.
   *
   * @note If a melody is currently playing, the new tempo will be applied on the next note played.
   */
  inline virtual void tempo(unsigned int qpm) = 0;

  /**
   * Stop playing current melody and play a new one.
   * 
   * @param melody     Pointer to the beginning of the note array representing the melody.
   * @param num_notes  Number of notes in the melody.
   * @param loop       Whether the melody should be repeated or not.
   */
  inline virtual void play(const Note* melody, unsigned int num_notes, bool loop) = 0;
  
  /**
   * @return Wheter a melody is being played or not
   */
  inline virtual bool is_playing() const = 0;
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_IMELODYPLAYER_HPP
