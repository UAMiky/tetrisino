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

void MelodyPlayer::play(const Note* melody, unsigned int n_elements)
{
  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < n_elements; thisNote++) {

    const Note& note = melody[thisNote];
    
    // to calculate the note duration, take the tempo divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = tempo_ / note.duration;

    // to distinguish the notes, play them for 90% of the duration.
    
    tone(pin_, note.hz, noteDuration * 0.9);

    delay(noteDuration);

    // stop the tone playing:

    noTone(pin_);

  }
}

}  // namespace melody_player
}  // namespace uamike
