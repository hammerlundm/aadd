# Album Art Display Daemon
## Description
AADD is a daemon to display the album art of the currently playing song in [mpd](https://www.musicpd.org/).
It assumes that the album art is located in an image in the same directory as the song.
The image is displayed in the upper-left corner of the screen, with a 30 pixel vertical offset (for the status bar).

Currently, AADD only supports [BSPWM](https://github.com/baskerville/bspwm) as a window manager.

## Usage
AADD is intended to be run in the background. For example, place the line

    aadd &

in your xinitrc.

To show/hide the album art, send the signal SIGUSR1 to AADD. For example,

    pkill -SIGUSR1 aadd

## Installation
To install, run

    sudo ./install.sh

## Dependencies
For running AADD, dependencies are:

* [feh](https://feh.finalrewind.org/)
* [mpd](https://www.musicpd.org/)

For building AADD from source, dependencies are:

* [libmpdclient](https://www.musicpd.org/libs/libmpdclient/)
* Linux system headers

## Future Plans
Eventually, command line arguments (and maybe config files) specifying window size/position and image locations will be added.

Support for other window managers might happen eventually.

