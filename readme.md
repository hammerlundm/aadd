# Album Art Display Daemon
## Description
AADD is a daemon to display the album art of the currently playing song in [mpd](https://www.musicpd.org/).
It makes the following assumptions:

* The album artist and album tags of all songs are set
* The directory ~/Music/artist/album/ exists
    * The cover art is located in the directory
    * The cover art is the only image file in the directory
* The dimensions of the screen are 3200x1800
* All cover art is at least 600x600

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

