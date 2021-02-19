/*

  Tetrisino - A tetris on Arduino
  by Miguel Company (UAMike)
*/

#include "include/arduino/button.hpp"
#include "include/melody_player/melody.hpp"

#include "FourButtonsInputController.hpp"
#include "game_control.hpp"
#include "pitches.h"

namespace mp = uamike::melody_player;
namespace ua = uamike::arduino;
namespace tet = uamike::tetrisino;

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

// Hardware inputs
ua::Button buttons[] {ua::Button(2), ua::Button(3), ua::Button(5), ua::Button(6)};
tet::FourButtonsInputController input(buttons[2], buttons[3], buttons[1], buttons[0]);

// Hardware outputs
mp::MelodyPlayer<8> player(140);

// Game logic
tet::GameControl game(input, player, 8);

// Updatables (in call order)
uamike::IUpdatable* updatables[] =
{
  &buttons[0], &buttons[1], &buttons[2], &buttons[3], &player, &game
};

void setup()
{
  // Initialize system
  game.begin();

  // Initialize inputs
  for (auto& button : buttons)
  {
    button.begin();
  }

  // Let the music begin!
  player.play(tetris_melody, num_melody_notes, true);
}

void loop()
{
  static unsigned long last_ms = 0;
  unsigned long current_ms = millis();
  unsigned long delta_ms = current_ms - last_ms;
  last_ms = current_ms;

  for (uamike::IUpdatable* updatable : updatables)
  {
    updatable->update(delta_ms);
  }
}
