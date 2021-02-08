/**
 * A melody player for Arduino
 * by Miguel Company (UAMike)
 */

#ifndef UAMIKE_MELODY_PLAYER_HPP
#define UAMIKE_MELODY_PLAYER_HPP

#include <arduino.h>

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

/**
 * A melody player based on tone().
 * 
 * @tparam pin_  Pin number on which the square waves will be generated.
 */
template<int pin_>
struct MelodyPlayer
{
  /**
   * Construct a melody player object.
   *
   * @param qpm  Tempo in quarter notes per minute.
   */
  MelodyPlayer(unsigned int qpm = 120)
  {
    tempo(qpm);
  }

  /**
   * Set a new tempo.
   * 
   * @param qpm  New tempo in quarter notes per minute.
   *
   * @note If a melody is currently playing, the new tempo will be applied on the next note played.
   */
  inline void tempo(unsigned int qpm)
  {
    // Use wholes per minute to avoid overflows
    auto wholes_per_min = qpm / 4;

    // Calc milliseconds per whole note.
    tempo_ = (60 * 1000) / wholes_per_min;
    tempo_ *= 100;
  }

  /**
   * Stop playing current melody and play a new one.
   * 
   * @param melody     Pointer to the beginning of the note array representing the melody.
   * @param num_notes  Number of notes in the melody.
   * @param loop       Whether the melody should be repeated or not.
   */
  inline void play(const Note* melody, unsigned int num_notes, bool loop)
  {
    melody_ = melody;
    num_notes_ = num_notes;
    note_index_ = 0;
    loop_ = loop;
  
    play_current_note();
  }

  /**
   * Update object state. Should be called periodically.
   * 
   * @param delta_ms  Milliseconds elapsed since last time this method was called.
   */
  inline void update(unsigned long delta_ms)
  {
    if (remaining_ms_ > delta_ms)
    {
      remaining_ms_ -= delta_ms;
      return;
    }
  
    remaining_ms_ = 0;
    play_current_note();
  }

private:

  void play_current_note()
  {
    if (loop_ && note_index_ >= num_notes_)
    {
      note_index_ = 0;
    }
    
    if (note_index_ < num_notes_)
    {
      pinMode(pin_, OUTPUT);
      
      const Note& note = melody_[note_index_];
      note_index_++;
      
      // to calculate the note duration, take the tempo divided by the note type.
  
      //e.g. quarter note = tempo_ / 400, eighth note = tempo_ / 800, etc.
  
      auto duration = tempo_ / note.duration;
  
      // to distinguish the notes, play them for 90% of the duration.
      
      tone(pin_, note.hz, duration * 0.9);
  
      remaining_ms_ += duration;
    }
  }
  
  unsigned int num_notes_ = 0;
  const Note* melody_ = nullptr;
  bool loop_ = false;
  
  unsigned int note_index_ = 0;
  unsigned long tempo_ = 1000;
  unsigned long remaining_ms_ = 0;
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_HPP
