Rubik's cube game like, but in 2d.

<img src="https://user-images.githubusercontent.com/49063932/150001991-a63f3bcb-f6cc-4440-83f8-23671db8cc77.png" alt="demo image"/>

## Build
1. Create build directory ( `mkdir build` )
2. Move to build directory ( `cd build` )
3. Configure build ( `cmake ..` )
4. Build ( `make` )
5. Run game ( `./alphabetloop_game` )

# Playing
See default key bindings in `config.cfg`.

By default scrolling is done by pressing `asdfg` (`ASDFG` for reverse side) for
scrolling current row by horizontal, and `zxcvb` (`ZXCVB` for reverse side) for
scrolling current column by vertical. Also pressing `w` will undo previous
scroll.

Pressing `i` will open prompt to write letters that you want to highlight
(press enter for save and continue).

Pressing `o` will show you completed map (press any key for continue playing).

And `q` and `r` respectively for close the game and restart.

## Config
`alphabetloop_game` will load `config.cfg` file from the same folder from which
game was launched.

In addition to binds described in the [Playing](#Playing) section, there
are also other settings, like:
* *hack* options (useful for debug)
* map size settings
* display settings
* ... and more

For more information go to provided [config example](./config.cfg) with
comments.

## Inspiration
Inspired by carykh's [video](https://www.youtube.com/watch?v=95rtiz-V2zM) on
youtube. I wanted to play this game on keyboard and in console, so got this.
