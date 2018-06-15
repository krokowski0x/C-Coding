# C Image Processing

Few projects made for an university course back in 2016.

## Brief description

Here are 3 out of many projects that were one of the first lines of code that I've ever written.
I've chosen these three, because they're a bit longer and they consist of some more **advanced pointers** and **memory allocation** parts.

### Image Processing 1

App lets you load .pgm image and perform number of image processing operations such as **negative, thresholding, half-thresholding, contouring and histogram equalization**. It also displays two images at the end - old one and the one that was just processed - for easier comparison.

* Read() and show() functions has been implemented from
function 'odczyt.c' which is [dr.inz.Muszynski](sequoia.ict.pwr.wroc.pl/~mucha/PProg/) intellectual property.

### Image Processing 2

Similar, but has some more advanced memory allocation + has (limited) color images support. It is also run not through a menu, but using flag parsing.

* Flag parsing utility is [dr.inz.Muszynski](sequoia.ict.pwr.wroc.pl/~mucha/PProg/) intellectual property.

### Stack-Based Normal Polish Notation Calculator

Stack implementation with simple **push, pop, empty and print** methods.
Additionally it has a **read_options** method which gets user input from the stream and calculates the output as if it was a
[Polish Notation Calculator](https://en.wikipedia.org/wiki/Polish_notation) in which operators precede their operands.
