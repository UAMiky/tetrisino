#ifndef UAMIKE_TETRISINO_GAMECONTROL_HPP
#define UAMIKE_TETRISINO_GAMECONTROL_HPP

#include "include/interfaces/IButton.hpp"
#include "include/interfaces/IUpdatable.hpp"
#include "include/melody_player/IMelodyPlayer.hpp"

#include "IInputController.hpp"
#include "InputState.hpp"

#include "piece.hpp"
#include "pitches.h"
#include "screen.hpp"

#define INITIAL_Y 23

namespace uamike {
namespace tetrisino {

struct GameControl : public IUpdatable
{
  using Player = melody_player::IMelodyPlayer;

  GameControl(IInputController& input, Player& player, int audio_pin)
    : input_(input), player_(player), audio_pin_(audio_pin)
  {
    player_.tempo(tempo_);
  }

  inline void begin()
  {
    randomSeed(analogRead(0));
    screen_.begin();

    screen_.add_piece(*next_piece_, 0, 28);
    delay(500);

    piece_ = next_piece_;
    screen_.remove_piece(*next_piece_, 0, 28);
    next_piece_ = Piece::random_piece();
    screen_.add_piece(*next_piece_, 0, 28);
  }
  
  inline void update(unsigned long ms) override
  {
    InputState input;
    input_.get_input_state(input);
  
    if (input.left || input.right || input.rotate)
    {
      screen_.remove_piece(*piece_, x_, y_);
      
      char save_x = x_;
      char save_y = y_;
      const Piece* save_piece = piece_;
      
      if (input.left) x_--;
      if (input.right) x_++;
      if (input.rotate) piece_ = Piece::rotate(piece_);
  
      if (!screen_.check_piece(*piece_, x_, y_))
      {
        x_ = save_x;
        y_ = save_y;
        piece_ = save_piece;
      }
      
      screen_.add_piece(*piece_, x_, y_);
    }

    place_was_pressed_ |= input.place;
  
    bool should_go_down = input.down;
    unsigned long down_trigger_ms = place_was_pressed_ ? 10 : delay_ms_;
    down_ms_ += ms;
    if (down_ms_ >= down_trigger_ms)
    {
      down_ms_ -= down_trigger_ms;
      should_go_down = true;
    }
  
    if (should_go_down)
    {
      screen_.remove_piece(*piece_, x_, y_);
      --y_;
      if (screen_.check_piece(*piece_, x_, y_))
      {
        screen_.add_piece(*piece_, x_, y_);
        return;
      }
  
      ++y_;
      screen_.add_piece(*piece_, x_, y_);

      // check for game over
      if (y_ == INITIAL_Y)
      {
        // Stop music
        player_.stop();

        // Play game-over tones
        tone(audio_pin_, NOTE_C4, 200);
        delay(250);
        tone(audio_pin_, NOTE_B3, 200);
        delay(250);
        tone(audio_pin_, NOTE_AS3, 200);
        delay(250);
        tone(audio_pin_, NOTE_A3, 700);
        delay(750);

        // Show game score
        unsigned long score = (32 * (1510 - delay_ms_)) / 1500;
        screen_.game_over(score + 1, audio_pin_);

        while(true) delay(50000);
      }

      // check lines
      unsigned int lines = screen_.check_and_remove_lines(y_, audio_pin_);
      if (lines > 0)
      {
        tempo_ += lines;
        delay_ms_ -= lines * 10;
        if (delay_ms_ < 10) delay_ms_ = 10;
        if (tempo_ > 240) tempo_ = 240;
        player_.tempo(tempo_);
      }
  
      piece_ = next_piece_;
      screen_.remove_piece(*next_piece_, 0, 28);
      next_piece_ = Piece::random_piece();
      screen_.add_piece(*next_piece_, 0, 28);
      x_ = 2;
      y_ = INITIAL_Y;
      place_was_pressed_ = false;
    }
  }

private:
  IInputController& input_;
  Player& player_;
  int audio_pin_;
  
  Screen screen_;
  const Piece* next_piece_ = Piece::random_piece();
  const Piece* piece_ = nullptr;
  char x_ = 2;
  char y_ = INITIAL_Y;

  bool place_was_pressed_ = false;
  unsigned long down_ms_ = 0;
  unsigned long delay_ms_ = 1510;
  unsigned int tempo_ = 140;
};

}  // namespace tetrisino
}  // namespace uamike

#endif  // UAMIKE_TETRISINO_GAMECONTROL_HPP
