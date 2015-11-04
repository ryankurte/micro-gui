# Micro-GUI (ugui)

Micro-GUI (ugui) is a minimal GUI framework for embedded systems, because there seems to be a lack of open source embedded gui tools, and we should share more.

Heavily inspired by the [Pebble](https://getpebble.com) User Interface API (which is seriously great, and you can check out [here](https://developer.getpebble.com/docs/c/User_Interface/)).

It provides a simple window stack, layers for composition of windows, graphics functions for rendering primitives and text, and widgets to simplify commonly used functions.

If you have any issues or feature requests, feel free to open an issue or a pull request. And, if you find yourself using this in a project, I would love to know about it!

## Goals
 - Simple to embed
   - No (or minor) external dependencies
   - Permissive licensing (MIT)
   - C compliant, doesn't force the use of c++
 - Simple to use
   - Minimal API
   - Widgets for common functions
   - Examples for all components
   - API documentation?
 - Simple to develop
   - Object Oriented C
   - Clearly defined modules
 - Simple to test
   - Compiles for any platform (bmp export requires file.h)

## Status

 - Window stack / top level interface working
 - Layers mostly working
 - Graphics module 
   - mostly ignores layers, rendering should be aware of layer context
   - text rendering not implemented
 - Widgets
   - working on menu, needs text really
   - todo: progress bar, alert/message box
 - Testing, needs to be implemented (w/ CI)
 - Example, would be cool to have a real time window, needs to be simple, though.

## Getting Started

TODO

## Examples

For an example application see the `example/` folder. This application will update a bmp file each rendering call, and can be interacted with using the command line.

## Credits

 - Pebble 
 - Line and Ellipse functions adapted from: 
 - Fonts from: https://github.com/dhepper/font8x8

## License

This project is licensed under the terms of the MIT license.
See LICENSE.TXT for more information
