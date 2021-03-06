#include "screen.hpp"

#include <arduino.h>
#include <SPI.h>

#include "piece.hpp"

namespace uamike {
namespace tetrisino {

/*
 * Coordinate system.
 * (0, 0) is bottom left.
 * (7, 31) is top right.
 */

#define SCREEN_SKY_SEGMENT 3
#define SCREEN_TOTAL_SEGMENTS 4

static void print_column(const Screen::State& screen, char col)
{
  byte idx = 8 - col;
  SPI.beginTransaction (SPISettings (8000000, MSBFIRST, SPI_MODE0));  // 8 MHz clock, MSB first, mode 0
  digitalWrite(10, LOW);
  for (char i = SCREEN_TOTAL_SEGMENTS - 1; i >= 0; --i)
  {
    SPI.transfer(idx);
    SPI.transfer(screen[i][col]);
  }
  digitalWrite(10, HIGH);
  SPI.endTransaction();
}

void control(byte cmd, byte operand)
{
  SPI.beginTransaction (SPISettings (8000000, MSBFIRST, SPI_MODE0));  // 8 MHz clock, MSB first, mode 0
  digitalWrite(10, LOW);
  for (byte i = 0; i < SCREEN_TOTAL_SEGMENTS; ++i)
  {
    SPI.transfer(cmd);
    SPI.transfer(operand);
  }
  digitalWrite(10, HIGH);
  SPI.endTransaction();
}

void Screen::begin()
{
  SPI.begin();
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  control(0xF, 0);              // no test
  control(0xB, 7);              // scan limit is set to max on startup
  control(0xA, 7);              // set intensity to a reasonable value
  control(0x9, 0);              // ensure no decoding (warm boot potential issue)
  clear();
  control(0xC, 1);              // take the modules out of shutdown mode
}

void Screen::clear()
{
  memset(screen, 0, sizeof(screen));
  for (byte c = 0; c < 8; ++c)
    print_column(screen, c);
}

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
      sv = (segment_idx == (SCREEN_SKY_SEGMENT - 1)) ? 0x00 : screen[segment_idx + 1][off];
      if (0 != (sv & (v >> (8 - segment_off)))) return false;
    }
  }
  return true;
}

void set_piece(Screen::State& screen, const Piece& piece, char x, char y, void (*f)(byte& v, byte mask))
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
    if (segment_idx >= 0)
    {
      f(screen[segment_idx][off], v << segment_off);
    }
    
    if ((segment_off >= 5) && (segment_idx < (SCREEN_SKY_SEGMENT - 1)))
    {
      f(screen[segment_idx + 1][off], v >> (8 - segment_off));
    }

    print_column(screen, off);
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

bool Screen::move_piece(const Piece*& piece, const InputState& input, char& x, char& y)
{
  bool ret_val = true;

  if (input.left || input.right || input.rotate)
  {
    remove_piece(*piece, x, y);
    
    char save_x = x;
    char save_y = y;
    const Piece* save_piece = piece;
    
    if (input.left) x--;
    if (input.right) x++;
    if (input.rotate) piece = Piece::rotate(piece);

    if (!check_piece(*piece, x, y))
    {
      x = save_x;
      y = save_y;
      piece = save_piece;
    }
    
    add_piece(*piece, x, y);
  }

  if (input.down)
  {
    remove_piece(*piece, x, y);
    --y;
    ret_val = check_piece(*piece, x, y);
    if (!ret_val)
    {
      ++y;
    }
    add_piece(*piece, x, y);
  }
  
  return ret_val;
}
  
bool check_and_remove_line(Screen::State& screen, char y, int audio_pin)
{
  // Underground lines are never removed
  if (y < 0) return false;

  // Point to segment
  char segment_idx = y >> 3;
  // Bit corresponding to row
  char segment_off = y & 7;
  byte mask = 1 << (segment_off);

  // Stop checking if bit is not set in one of the columns
  for (char c = 0; c < 8; ++c)
  {
    if ((screen[segment_idx][c] & mask) == 0) return false;
  }

  // All columns have the bit. User made a line!

  // Make line disappear
  for (char c = 0; c < 8; ++c)
  {
    screen[segment_idx][c] &= ~mask;
    print_column(screen, c);
  }

  // Sound and wait
  tone(audio_pin, 4*440, 200);
  delay(250);

  // Shift columns
  for (char c = 0; c < 8; ++c)
  {
    char seg = segment_idx;
    byte v = screen[seg][c];
    mask = 0xFF << segment_off;
    v = (v & ~mask) | ((v & mask) >> 1);
    while (seg < (SCREEN_SKY_SEGMENT - 1))
    {
      byte next_v = screen[seg + 1][c];
      v |= (next_v << 7);
      screen[seg][c] = v;
      v = next_v >> 1;
      ++seg;
    }
    screen[seg][c] = v;
    print_column(screen, c);
  }

  return true;
}

unsigned int Screen::check_and_remove_lines(char y, int audio_pin)
{
  unsigned int ret_val = 0;
  for (byte i = 0; i < 4; ++i)
  {
    if (check_and_remove_line(screen, y, audio_pin)) ret_val++;
    else y++;
  }
  return ret_val;
}

void Screen::game_over(byte score, int audio_pin)
{
  int freq = 440;
  for (byte i = 0; i <= score && i <= 32; ++i)
  {
    unsigned long v = 0xFFFFFFFF >> (32 - i);
    for (byte c = 1; c < 9; ++c)
    {
      SPI.beginTransaction (SPISettings (8000000, MSBFIRST, SPI_MODE0));  // 8 MHz clock, MSB first, mode 0
      digitalWrite(10, LOW);
      SPI.transfer(c);
      SPI.transfer(static_cast<byte>((v >> 24) & 0xFF));
      SPI.transfer(c);
      SPI.transfer(static_cast<byte>((v >> 16) & 0xFF));
      SPI.transfer(c);
      SPI.transfer(static_cast<byte>((v >> 8) & 0xFF));
      SPI.transfer(c);
      SPI.transfer(static_cast<byte>(v & 0xFF));
      digitalWrite(10, HIGH);
      SPI.endTransaction();
    }
    tone(audio_pin, freq, 250);
    freq = (freq * 1100) / 1000;
    delay(100);
  }
}

}  // namespace tetrisino
}  // namespace uamike
