#include "melody.hpp"

#include <arduino.h>

namespace uamike {
namespace melody_player {

MelodyPlayer::MelodyPlayer(int pin)
  : pin_(pin)
{  
}

void MelodyPlayer::play(const Note* melody, unsigned int n_elements)
{
  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < n_elements; thisNote++) {

    const Note& note = melody[thisNote];
    
    // to calculate the note duration, take one second divided by the note type.

    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.

    int noteDuration = 1000 / note.duration;

    tone(pin_, note.hz, noteDuration);

    // to distinguish the notes, set a minimum time between them.

    // the note's duration + 30% seems to work well:

    int pauseBetweenNotes = noteDuration * 1.30;

    delay(pauseBetweenNotes);

    // stop the tone playing:

    noTone(pin_);

  }
}

}  // namespace melody_player
}  // namespace uamike
