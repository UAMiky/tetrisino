#include "screen.hpp"

#include <arduino.h>
#include <SPI.h>

#include "piece.hpp"

namespace uamike {
namespace tetrisino {

//static

/*
 * Coordinate system.
 * (0, 0) is bottom left.
 * (7, 31) is top right.
 */

bool Screen::check_piece(const Piece& piece, char x, char y)
{
  char segment_idx = y >> 3;
  
  for (char idx = 0; idx < 4; ++idx)
  {
    byte v = piece.data[idx];

    // Piece column is empty. Go to next column.
    if (0 == v) continue;
    
    char off = idx + x;

    // Non-empty column out of field. Piece cannot be here.
    if (off < 0 || off >= 8) return false;

    char segment_off = y & 7;
    byte sv = (y < 0) ? 0xFF : screen[segment_idx][off];

    // Align piece with segment and check overlap
    if (0 != (sv & (v << segment_off))) return false;

    if (segment_off >= 5)
    {
      // check on next segment (or the sky)
      sv = (segment_idx == 3) ? 0x00 : screen[segment_idx + 1][off];
      if (0 != (sv & (v << (8 - segment_off)))) return false;
    }
  }
  return true;
}

void set_piece(Screen::ScreenState& screen, const Piece& piece, char x, char y, void (*f)(byte& v, byte mask))
{
  char segment_idx = y >> 3;
  
  for (char idx = 0; idx < 4; ++idx)
  {
    char off = idx + x;

    // Out of field. Go to next column.
    if (off < 0 || off >= 8) continue;

    byte v = piece.data[idx];

    // Piece column is empty. Go to next column.
    if (0 == v) continue;
    
    char segment_off = y & 7;
    if (y >= 0)
    {
      f(screen[segment_idx][off], v << segment_off);
    }
    
    if ((segment_off >= 5) && (segment_idx < 3))
    {
      f(screen[segment_idx + 1][off], v << (8 - segment_off));
    }
  }
}

static void add_value(byte& v, byte mask)
{
  v |= mask;
}

void Screen::add_piece(const Piece& piece, char x, char y)
{
  set_piece(screen, piece, x, y, add_value);
}

static void clear_value(byte& v, byte mask)
{
  v &= ~mask;
}

void Screen::remove_piece(const Piece& piece, char x, char y)
{
  set_piece(screen, piece, x, y, clear_value);
}

}
}
