/*

  Tetrisino - A tetris on Arduino
  by Miguel Company (UAMike)
*/

#include "pitches.h"
#include "melody.hpp"

namespace mp = uamike::melody_player;

const mp::Note tetris_melody[] = {  
  {NOTE_E5, 4}, {NOTE_B4, 8}, {NOTE_C5, 8}, {NOTE_D5, 4}, {NOTE_C5, 8}, {NOTE_B4, 8}, 
  {NOTE_A4, 4}, {NOTE_A4, 8}, {NOTE_C5, 8}, {NOTE_E5, 4}, {NOTE_D5, 8}, {NOTE_C5, 8},
  {NOTE_B4, 4}, {NOTE_B4, 8}, {NOTE_C5, 8}, {NOTE_D5, 4}, {NOTE_E5, 4},
  {NOTE_C5, 4}, {NOTE_A4, 4},               {NOTE_A4, 4}, {0, 4},
  {0, 8}, {NOTE_D5, 4}, {NOTE_F5, 8}, {NOTE_A5, 4}, {NOTE_G5, 8}, {NOTE_F5, 8},
  {NOTE_E5, 4}, {NOTE_E5, 8}, {NOTE_C5, 8}, {NOTE_E5, 4}, {NOTE_D5, 8}, {NOTE_C5, 8},
  {NOTE_B4, 4}, {NOTE_B4, 8}, {NOTE_C5, 8}, {NOTE_D5, 4}, {NOTE_E5, 4},
  {NOTE_C5, 4}, {NOTE_A4, 4},               {NOTE_A4, 4}, {0, 4}
};
constexpr unsigned int num_melody_notes = sizeof(tetris_melody) / sizeof(mp::Note);

mp::MelodyPlayer player(8, 140);
unsigned long last_ms = 0;

void setup() {

  player.play(tetris_melody, num_melody_notes);
}

void loop() {
  unsigned long current_ms = millis();
  unsigned long delta_ms = current_ms - last_ms;
  last_ms = current_ms;

  player.update(delta_ms);
}
