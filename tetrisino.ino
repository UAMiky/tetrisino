/*

  Tetrisino - A tetris on Arduino
  by Miguel Company (UAMike)
*/

#include "pitches.h"
#include "melody.hpp"

namespace mp = uamike::melody_player;

const mp::Note tetris_melody[] = {  
  {NOTE_E5, 400}, {NOTE_B4, 800}, {NOTE_C5, 800}, {NOTE_D5, 400}, {NOTE_C5, 800}, {NOTE_B4, 800}, 
  {NOTE_A4, 400}, {NOTE_A4, 800}, {NOTE_C5, 800}, {NOTE_E5, 400}, {NOTE_D5, 800}, {NOTE_C5, 800},
  {NOTE_B4, 400}, {NOTE_B4, 800}, {NOTE_C5, 800}, {NOTE_D5, 400}, {NOTE_E5, 400},
  {NOTE_C5, 400}, {NOTE_A4, 400}, {NOTE_A4, 400}, {0, 400},
  {0, 800}, {NOTE_D5, 400}, {NOTE_F5, 800}, {NOTE_A5, 400}, {NOTE_G5, 800}, {NOTE_F5, 800},
  {NOTE_E5, 266}, {NOTE_C5, 800}, {NOTE_E5, 400}, {NOTE_D5, 800}, {NOTE_C5, 800},
  {NOTE_B4, 400}, {NOTE_B4, 800}, {NOTE_C5, 800}, {NOTE_D5, 400}, {NOTE_E5, 400},
  {NOTE_C5, 400}, {NOTE_A4, 400}, {NOTE_A4, 400}, {0, 400}
};
constexpr unsigned int num_melody_notes = sizeof(tetris_melody) / sizeof(mp::Note);

mp::MelodyPlayer<8> player(140);
unsigned long last_ms = 0;

void setup() {

  player.play(tetris_melody, num_melody_notes, false);
}

void loop() {
  unsigned long current_ms = millis();
  unsigned long delta_ms = current_ms - last_ms;
  last_ms = current_ms;

  player.update(delta_ms);
}
