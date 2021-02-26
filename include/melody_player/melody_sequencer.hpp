/**
 * A melody player for Arduino
 * by Miguel Company (UAMike)
 */

#ifndef UAMIKE_MELODY_PLAYER_SEQUENCER_HPP
#define UAMIKE_MELODY_PLAYER_SEQUENCER_HPP

#include <arduino.h>

#include "IMelodyPlayer.hpp"
#include "note.hpp"
#include "../interfaces/IUpdatable.hpp"

namespace uamike {
namespace melody_player {

struct MelodyEntry
{
  const Note* melody;
  unsigned int num_notes;
  unsigned int num_times;
};

struct MelodySequencer : public IMelodyPlayer, public IUpdatable
{
  MelodySequencer(IMelodyPlayer& player, const MelodyEntry* melodies, unsigned int num_melodies, bool loop)
    : player_(player), melodies_(melodies), num_melodies_(num_melodies), loop_(loop)
  {
  }

  /**
   * Set a new tempo.
   * 
   * @param qpm  New tempo in quarter notes per minute.
   *
   * @note If a melody is currently playing, the new tempo will be applied on the next note played.
   */
  inline void tempo(unsigned int qpm) override
  {
    player_.tempo(qpm);
  }

  /**
   * Stop playing current melody and play a new one.
   * 
   * @param melody     Pointer to the beginning of the note array representing the melody.
   * @param num_notes  Number of notes in the melody.
   * @param loop       Whether the melody should be repeated or not.
   */
  inline void play(const Note* /*melody*/, unsigned int /*num_notes*/, bool loop) override
  {
    stop();
	melody_times_ = 0;
	loop_ = loop;
  }
  
  inline void stop() override
  {
    player_.stop();
    
    melody_index_ = num_melodies_;
	melody_times_ = 0;
    loop_ = false;
  }
  
  inline bool is_playing() const override
  {
    return player_.is_playing();
  }

  /**
   * Update object state. Should be called periodically.
   * 
   * @param delta_ms  Milliseconds elapsed since last time this method was called.
   */
  inline void update(unsigned long delta_ms) override
  {
    if (!player_.is_playing())
    {
      play_current_melody();
    }
  }
  
private:

  void play_current_melody()
  {
    if (loop_ && melody_index_ >= num_melodies_)
    {
      melody_index_ = 0;
      melody_times_ = 0;
    }
    
    if (melody_index_ < num_melodies_)
    {
      const MelodyEntry& melody = melodies_[melody_index_];
      if (melody_times_ < melody.num_times)
      {
        player_.play(melody.melody, melody.num_notes, false);
        ++melody_times_;
      }
      else
      {
        ++melody_index_;
        melody_times_ = 0;
      }
    }  
  }

  IMelodyPlayer& player_;
  const MelodyEntry* melodies_ = nullptr;
  unsigned int num_melodies_ = 0;
  bool loop_ = false;
  
  unsigned int melody_index_ = 0;
  unsigned int melody_times_ = 0;  
};

} // namespace melody_player
} // namespace uamike

#endif  // UAMIKE_MELODY_PLAYER_SEQUENCER_HPP
