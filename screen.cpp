#include "screen.hpp"

#include <arduino.h>
#include <SPI.h>

#include "piece.hpp"

namespace uamike {
namespace tetrisino {

/*
 * Coordinate system.
 * (0, 0) is bottom right.
 * (7, 31) is top left.
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

void add_piece(const Piece& piece, char x, char y)
{
}

}
}
