# Lab07

All classes should be in the package `lab07`.

You will show the lab to your TA before you leave to receive a grade.

In this lab you will implement some basic file editor functionality.
It will allow you to open, type, draw, and save files.
We will use inheritance to aid us.

First you will start with a basic class to represent buffers, the place
to edit text.

Make a class `Buffer` with:

* a protected `List<String> lines` field. Do not instantiate it to anything
* a public `int getNumlines()` which returns the length of the `lines` field
* a public `String getText()` field which returns `String.join("\n", this.lines)`
* a public `void draw()` method which prints out `this.getText()`
* a public `void save()` function which throws an `UnsupportedOperationException`
* a public `void type(String toType)` method which loops through each character in `toType` and
  * if it's a newline (`'\n'`) then add an empty string to the `lines` field
  * else extend the last line in the `lines` field by appending the character to it

Now you will write a specialized version which is a buffer backed by a
file.

Make a class `FileBuffer` which extends `Buffer` with:

* a private `String` field which will hold the filename
* a constructor which takes in a filename and sets the field
  * it also needs to read the lines in the given file and set them to
    the `lines` field (inherited from the `Buffer` parent class)
    * the easiest way to do this is to use the
      `java.nio.file.Files.readAllLines` function. Look up the
      documentation and raise your hand if you have troubles using it.
	* if there is an exception while opening or reading the file then
      set the `lines` field to an empty `ArrayList`
* a `save` method which overrides `Buffer`'s which writes all the
  lines in the `lines` field to this `FileBuffer`'s filename.
  * the easiest way to do this is to use the
    `java.nio.file.Files.write` method. Look up this method and raise
    your hand if you need help using it.

Next you will create another type of buffer which isn't backed by a
file, but can still be typed in.

Make a class `ScratchBuffer` which extends `Buffer` with:

* a constructor which sets the `lines` field to an empty `ArrayList`
* a `save` method identical to `FileBuffer`'s except use `"scratch"`
  as the file to save to

Now you will write a class representing a status bar similar to the
one on the bottom of gedit.

Make a class `StatusBar` which extends `Buffer` with:

* a private `Buffer attachedTo` field
* a constructor which takes a `Buffer` and sets the `attachedTo` field to it
* a `getText` method which overrides `Buffer`'s which returns the
  number of lines in the `attachedTo` buffer. You can stylize the
  output. For example it could return
  ```
  ------
  lines: 10
  ------
  ```
  assuming there were 10 lines in the attached buffer.

Notice how in the `draw` method inside `Buffer`, `this.getText()` is
called. Does this always call the `getText` inside `Buffer`?

Putting all this together you will write the main editor class.

Make a class `Editor` with:

* a private `Buffer` field and a private `StatusBar` field
* a constructor which takes one `Buffer` argument. It sets the
  `Buffer` field to the argument and uses the argument to initialize
  the private `StatusBar` field
* a `draw` method which calls `draw` on the `Buffer` field and then the `StatusBar` field
* a `save` method which calls `save` only on the `Buffer` field
* a `type` method which takes a `String` argument and passes it along
  to the `type` method of the `Buffer` field

Now you will test you editor.

Write a `Driver` class with a main method. The main method should
check if it was passed an argument. If it was use that as the filename
to create a `FileBufer`. If there is no argument then create a
`ScratchBuffer` object. Use whichever buffer was created to create an
`Editor` object.

Play around with calling `draw` `type` and then `draw` again with
different arguments. Try calling `save` after a `type` and see that
the file was saved properly.

Show your lab to the TA before you leave to receive a grade.
