# Tetrisino
A tetris on Arduino

## Hardware used
* 1 8x32 led matrix

## Design considerations

### Screen

The screen is composed by 4 8x8 segments.
We will position the screen with the connector downwards, so that the first transmitted
SPI command will be transmitted to the upper segment.
Initial tests show that a "digit" on the MAX7219 will represent a column on the segment,
and that digit 0 is the right column.
Thus we can represent a segment with an array of 8 bytes representing the 8 columns from
right to left, and then represent the screen with an array of 4 segments.

### Piece workspace

All pieces fit inside a 4x4 square.
We will represent this space with an array of 4 bytes.
We will also need the position of one corner of the piece space.
This position could have negative values, as one column of the space may be empty and out
of the screen.