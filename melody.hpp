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

/**
 * A melody player based on tone()
 */
struct MelodyPlayer
{
  /**
   * Construct a melody player object.
   *
   * @param pin  Pin number on which the square waves will be generated.
   * @param qpm  Tempo in quarter notes per minute.
   */
  MelodyPlayer(int pin, unsigned int qpm = 120);

  /**
   * Set a new tempo.
   * 
   * @param qpm  New tempo in quarter notes per minute.
   *
   * @note If a melody is currently playing, the new tempo will be applied on the next note played.
   */
  void tempo(unsigned int qpm);

  /**
   * Stop playing current melody and play a new one.
   * 
   * @param melody     Pointer to the beginning of the note array representing the melody.
   * @param num_notes  Number of notes in the melody.
   * @param loop       Whether the melody should be repeated or not.
   */
  void play(const Note* melody, unsigned int num_notes, bool loop);

  /**
   * Update object state. Should be called periodically.
   * 
   * @param delta_ms  Milliseconds elapsed since last time this method was called.
   */
  void update(unsigned long delta_ms);

private:

  void play_current_note();
  
  int pin_ = 0;

  unsigned int num_notes_ = 0;
  const Note* melody_ = nullptr;
  
  unsigned int note_index_ = 0;
  unsigned long tempo_ = 1000;
  unsigned long remaining_ms_ = 0;
  bool loop_ = false;
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_HPP
