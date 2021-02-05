#include "melody.hpp"

#include <arduino.h>

namespace uamike {
namespace melody_player {

MelodyPlayer::MelodyPlayer(int pin, unsigned int qpm)
  : pin_(pin)
{
  tempo(qpm);
}

void MelodyPlayer::tempo (unsigned int quarters_per_min)
{
  auto wholes_per_min = quarters_per_min / 4;
  tempo_ = (60 * 1000) / wholes_per_min;
}

void MelodyPlayer::play(const Note* melody, unsigned int n_elements, bool loop)
{
  melody_ = melody;
  num_notes_ = n_elements;
  note_index_ = 0;
  loop_ = loop;

  play_current_note();
}

void MelodyPlayer::update(unsigned long delta_ms)
{
  if (remaining_ms_ > delta_ms)
  {
    remaining_ms_ -= delta_ms;
    return;
  }

  remaining_ms_ = 0;
  play_current_note();
}

void MelodyPlayer::play_current_note()
{
  if (loop_ && note_index_ >= num_notes_)
  {
    note_index_ = 0;
  }
  
  if (note_index_ < num_notes_)
  {
    const Note& note = melody_[note_index_];
    note_index_++;
    
    // to calculate the note duration, take the tempo divided by the note type.

    //e.g. quarter note = tempo_ / 4, eighth note = tempo_ / 8, etc.

    auto duration = tempo_ / note.duration;

    // to distinguish the notes, play them for 90% of the duration.
    
    tone(pin_, note.hz, duration * 0.9);

    remaining_ms_ += duration;
  }
}

}  // namespace melody_player
}  // namespace uamike
