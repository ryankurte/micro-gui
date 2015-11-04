# Micro-GUI (ugui)

Micro-GUI (ugui) is a minimal GUI framework for embedded systems, inspired by the [Pebble](https://getpebble.com) User Interface API (which is seriously great, and you can check out [here](https://developer.getpebble.com/docs/c/User_Interface/).

It provides a simple window stack, layers for composition of windows, graphics functions for rendering primitives and text, and widgets to simplify commonly used functions.

If you have any issues or feature requests, feel free to open an issue or a pull request. And, if you find yourself using this in a project, I would love to know about it!

# Status
 - Window stack / top level interface working
 - Layers mostly working
 - Graphics module mostly ignores layers, rendering should be aware of layer context
 - Testing, needs to be implemented (w/ CI)

## Credits
 - Pebble 
 - Line and Ellipse functions adapted from: 
 - Fonts from: https://github.com/dhepper/font8x8
