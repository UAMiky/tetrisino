/*

  Tetrisino - A tetris on Arduino
  by Miguel Company (UAMike)
*/

#include "button.hpp"
#include "melody.hpp"
#include "piece.hpp"
#include "pitches.h"
#include "screen.hpp"

#include <MD_MAX72xx.h>
#include <SPI.h>

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

// Hardware outputs
MD_MAX72XX mx(MD_MAX72XX::FC16_HW, 10, 4);
mp::MelodyPlayer<8> player(140);

// Updatables (in call order)
uamike::IUpdatable* updatables[] =
{
  &buttons[0], &buttons[1], &buttons[2], &buttons[3], &player
};

tet::Screen screen;
tet::Piece piece;
char x = 2;
char y = 31;

void setup()
{
  // Initialize data
  piece.data[0] = 0b0000;
  piece.data[1] = 0b0110;
  piece.data[2] = 0b0110;
  piece.data[3] = 0b0000;

  // Initialize inputs
  for (auto& button : buttons)
  {
    button.begin();
  }

  // Initialize outputs
  mx.begin();

  // Let the music begin!
  player.play(tetris_melody, num_melody_notes, false);

  /*
  SPI.beginTransaction (SPISettings (8000000, MSBFIRST, SPI_MODE0));  // 8 MHz clock, MSB first, mode 0
  for (byte i = 0; i < 8; ++i)
  {
    digitalWrite(10, LOW);
    for (byte j = 0; j < 4; ++j)
    {
      SPI.transfer(i+1);
      SPI.transfer(i+j);
    }
    digitalWrite(10, HIGH);
  }
  SPI.endTransaction();
  */
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

  bool left = buttons[2].was_pressed_this_frame();
  bool right = buttons[3].was_pressed_this_frame();
  bool down = buttons[1].was_pressed_this_frame();
  bool place = buttons[0].was_pressed_this_frame();

  if (place)
  {
    screen.add_piece(piece, x, y);
  }
  else if (left || right || down)
  {
    screen.remove_piece(piece, x, y);
    
    char save_x = x;
    char save_y = y;
    
    if (left) x++;
    if (right) x--;
    if (down) y--;

    if (!screen.check_piece(piece, x, y))
    {
      x = save_x;
      y = save_y;
    }
    
    screen.add_piece(piece, x, y);
  }
}
