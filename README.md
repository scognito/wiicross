# Piero's Wiicross

Piero's Wiicross is a picture logic puzzles in which cells in a grid have to be colored or left blank according to numbers given at the side of the grid to reveal a hidden picture. 

Developed using [libogc library](https://github.com/devkitPro/libogc) and other opensource libraries, it was released in 2008 for Nintendo Wii and GameCube home consoles.

More info on [my blog](http://scognito.wordpress.com/2008/12/02/pieros-wiicross-for-wii-and-gamecube-is-out/) and on [wiibrew](https://wiibrew.org/wiki/Piero%27s_Wiicross).

![Game cover wii](https://github.com/scognito/wiicross/blob/master/gfx%20work/cover-wii.jpg)

## How to play

The numbers measure how many unbroken lines of filled-in squares there are in any given row or column. For example, a clue of "4 8 3" would mean there are sets of four, eight, and three filled squares, in that order, with at least one blank square between successive groups. It's easier playing with game directly than understand the rules at first :)

## Game Modes
### Normal mode

If you try to colour a cell that can't be coloured, an error penalty is shown. Puzzle is solved when the image is correctly drawn.
### Free mode

There is no error reporting when you colour a wrong cell. Puzzle is solved when you hit the check button and the image is correctly drawn, otherwise an error penalty is shown.

Every error make the timer increase of a certain amout of time. 

## Controls
Wiimote controller is supported (pointing on screen or in NES position) as well as the Gamecube Controller.

## Customizations
#### Music

Put your favourite songs in the "res/music" directory (for example if you use the homebrew channel it is "apps/wiicross/res/music"), then select "Custom" from the options menu.

Note: Music must be in ogg format becayse sndlib does not support MP3, and libogc support for them is screwed. Also res directory on GameCube must be put on the root of the SD.

#### Themes

A theme is composed by the following images

* background.png (640 x 480 pixels)
* filled.png (image to show when a cell is drawn)
* marked.png (image to show when a cell is marked)
* title.png (the title to show in the option screen for selecting your theme)

All themes must be put in a directory called with the name of your theme, and this directory must be put in "res/themes". If you follow these rules, you’ll find you theme in the options screen.

For helping in drawing a theme, I'll post a template on the project page. It also contains a psd (Photoshop) and a xcf (Gimp) containing layers, helpful for drawing the background, since some part of it are used for painting the timer and the preview. 

## Screenshots

![Titlescreen](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/titlescreen.jpg)

![Level sample](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/default.jpg)

![Level select](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/levelselect.jpg)

![Level sample 2](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/blue.jpg)

![Options screen](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/options.jpg)

![Level sample 3](https://github.com/scognito/wiicross/blob/master/gfx%20work/screenshots/spooky.jpg)

#### Video gameplay
[![Video](https://img.youtube.com/vi/B66shhGebuY/0.jpg)](https://youtu.be/B66shhGebuY)

### Downloads

The game is available in the [Homebrew browser](https://wiibrew.org/wiki/Homebrew_Browser).

It is possible to download from [here](https://github.com/scognito/wiicross/blob/master/Pieros-Wiicross.rar).

### Thanks

* Spriteattack for stunning graphics (and for patience to work with me)
* Cyan & Liz from gbatemp.net: for impressive work on bug testing, fixing bugged levels and sorting by difficulty: the game couldn't be here without them
* MrNick for massive testing on the Gamecube version
* Aaron Williams for the nice "level cleared" jingle
* All the users who sent their level (using the online level editor)

### Online Editor

The online level editor is available on [drunkencoders](http://scognito.drunkencoders.com/projects/wiicross-editor.php) but not used anymore.

![Level editor](https://github.com/scognito/wiicross/blob/master/gfx%20work/editor.png)
