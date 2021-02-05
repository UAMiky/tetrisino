/*

  Tetrisino - A tetris on Arduino
  by Miguel Company (UAMike)
*/

#include "pitches.h"
#include "melody.hpp"

namespace mp = uamike::melody_player;

const mp::Note melody[] = {  
  {NOTE_C4, 4}, {NOTE_G3, 8}, {NOTE_G3, 8}, {NOTE_A3, 4}, {NOTE_G3, 4}, {0, 4}, {NOTE_B3, 4}, {NOTE_C4, 4}
};

mp::MelodyPlayer player(8, 240);
unsigned long last_ms = 0;

void setup() {

  player.play(melody, 8);
}

void loop() {
  unsigned long current_ms = millis();
  unsigned long delta_ms = current_ms - last_ms;
  last_ms = current_ms;

  player.update(delta_ms);
}
