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
const tet::Piece* piece = tet::Piece::random_piece();
char x = 2;
char y = 31;

void setup()
{
  // Initialize inputs
  for (auto& button : buttons)
  {
    button.begin();
  }

  // Initialize outputs
  mx.begin();

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

  bool left = buttons[2].was_pressed_this_frame();
  bool right = buttons[3].was_pressed_this_frame();
  bool rotate = buttons[1].was_pressed_this_frame();
  bool place = buttons[0].was_pressed_this_frame();

  static bool place_was_pressed = false;
  place_was_pressed |= place;
  bool should_go_down = place_was_pressed;

  static unsigned long down_ms = 0;
  down_ms += delta_ms;
  if (down_ms >= 1500)
  {
    down_ms -= 1500;
    should_go_down = true;
  }

  if (should_go_down)
  {
    screen.remove_piece(*piece, x, y);
    --y;
    if (screen.check_piece(*piece, x, y))
    {
      screen.add_piece(*piece, x, y);
      return;
    }

    ++y;
    screen.add_piece(*piece, x, y);

    // TODO: check lines

    piece = tet::Piece::random_piece();
    x = 2;
    y = 31;
    place_was_pressed = false;
  }

  if (left || right || rotate)
  {
    screen.remove_piece(*piece, x, y);
    
    char save_x = x;
    char save_y = y;
    const tet::Piece* save_piece = piece;
    
    if (left) x--;
    if (right) x++;
    if (rotate) piece = tet::Piece::rotate(piece);

    if (!screen.check_piece(*piece, x, y))
    {
      x = save_x;
      y = save_y;
      piece = save_piece;
    }
    
    screen.add_piece(*piece, x, y);
  }
}
