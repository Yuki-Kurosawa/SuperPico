// This is a Processing sketch, see https://processing.org/ to download the IDE

// Select the font, size and character ranges in the user configuration section
// of this sketch, which starts at line 120. Instructions start at line 50.


/*
Software License Agreement (FreeBSD License)
 
 Copyright (c) 2018 Bodmer (https://github.com/Bodmer)
 
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 The views and conclusions contained in the software and documentation are those
 of the authors and should not be interpreted as representing official policies,
 either expressed or implied, of the FreeBSD Project.
 */

////////////////////////////////////////////////////////////////////////////////////////////////

// This is a processing sketch to create font files for the TFT_eSPI library:

// https://github.com/Bodmer/TFT_eSPI

// Coded by Bodmer January 2018, updated 10/2/19
// Version 0.8

// >>>>>>>>>>>>>>>>>>>>             INSTRUCTIONS             <<<<<<<<<<<<<<<<<<<<

// See comments below in code for specifying the font parameters (point size,
// unicode blocks to include etc). Ranges of characters (glyphs) and specific
// individual glyphs can be included in the created "*.vlw" font file.

// Created fonts are saved in the sketches "FontFiles" folder. Press Ctrl+K to
// see that folder location.

// 16 bit Unicode point codes in the range 0x0000 - 0xFFFF are supported.
// Codes 0-31 are control codes such as "tab" and "carraige return" etc.
// and 32 is a "space", these should NOT be included.

// The sketch will convert True Type (a .ttf or .otf file) file stored in the
// sketches "Data" folder as well as your computers' system fonts.

// To maximise rendering performance and the memory consumed only include the characters
// you will use. Characters at the start of the file will render faster than those at
// the end due to the buffering and file seeking overhead.

// The inclusion of "non-existant" characters in a font may give unpredicatable results
// when rendering with the TFT_eSPI library. The Processing sketch window that pops up
// to show the font characters will print "boxes" (also known as Tofu!) for non existant
// characters.

// Once created the files must be loaded into the ESP32 or ESP8266 SPIFFS memory
// using the Arduino IDE plugin detailed here:
// https://github.com/esp8266/arduino-esp8266fs-plugin
// https://github.com/me-no-dev/arduino-esp32fs-plugin

// When the sketch is run it will generate a file called "System_Font_List.txt" in the
// sketch "FontFiles" folder, press Ctrl+K to see it. Open the file in a text editor to
// view it. This list provides the font reference number needed below to locate that
// font on your system.

// The sketch also lists all the available system fonts to the console, you can increase
// the console line count (in preferences.txt) to stop some fonts scrolling out of view.
// See link in File>Preferences to locate "preferences.txt" file. You must close
// Processing then edit the file lines. If Processing is not closed first then the
// edits will be overwritten by defaults! Edit "preferences.txt" as follows for
// 3000 lines, then save, then run Processing again:

//     console.length=3000;             // Line 4 in file
//     console.scrollback.lines=3000;   // Line 7 in file


// Useful links:
/*

 https://en.wikipedia.org/wiki/Unicode_font
 
 https://www.gnu.org/software/freefont/
 https://www.gnu.org/software/freefont/sources/
 https://www.gnu.org/software/freefont/ranges/
 http://savannah.gnu.org/projects/freefont/
 
 http://www.google.com/get/noto/
 
 https://github.com/Bodmer/TFT_eSPI
 https://github.com/esp8266/arduino-esp8266fs-plugin
 https://github.com/me-no-dev/arduino-esp32fs-plugin
 
   >>>>>>>>>>>>>>>>>>>>         END OF INSTRUCTIONS         <<<<<<<<<<<<<<<<<<<< */


import java.awt.Desktop; // Required to allow sketch to open file windows


////////////////////////////////////////////////////////////////////////////////////////////////

//                       >>>>>>>>>> USER CONFIGURED PARAMETERS START HERE <<<<<<<<<<

// Use font number or name, -1 for fontNumber means use fontName below, a value >=0 means use system font number from list.
// When the sketch is run it will generate a file called "systemFontList.txt" in the sketch folder, press Ctrl+K to see it.
// Open the "systemFontList.txt" in a text editor to view the font files and reference numbers for your system.

int fontNumber = -1; // << Use [Number] in brackets from the fonts listed.

// OR use font name for ttf files placed in the "Data" folder or the font number seen in IDE Console for system fonts
//                                                  the font numbers are listed when the sketch is run.
//                |         1         2     |       Maximum filename size for SPIFFS is 31 including leading /
//                 1234567890123456789012345        and added point size and .vlw extension, so max is 25
String fontName = "unifont-jp";  // Manually crop the filename length later after creation if needed
                                     // Note: SPIFFS does NOT accept underscore in a filename!
String fontType = ".ttf";
//String fontType = ".otf";


// Define the font size in points for the TFT_eSPI font file
int  fontSize = 16;

// Font size to use in the Processing sketch display window that pops up (can be different to above)
int displayFontSize = 16;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Next we specify which unicode blocks from the the Basic Multilingual Plane (BMP) are included in the final font file. //
// Note: The ttf/otf font file MAY NOT contain all possible Unicode characters, refer to the fonts online documentation. //
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static final int[] unicodeBlocks = {
  // The list below has been created from the table here: https://en.wikipedia.org/wiki/Unicode_block
  // Remove // at start of lines below to include that unicode block, different code ranges can also be specified by
  // editing the start and end-of-range values. Multiple lines from the list below can be included, limited only by
  // the final font file size!

  // Block range,   //Block name, Code points, Assigned characters, Scripts
  // First, last,   //Range is inclusive of first and last codes
  0x0021, 0x007E, //Basic Latin, 128, 128, Latin (52 characters), Common (76 characters)
  0x3400, 0x4DBF, //CJK Unified Ideographs Extension A, 6,592, 6,582, Han
  0x4E00, 0x9FFF, //CJK Unified Ideographs, 20,992, 20,971, Han
};

// Here we specify particular individual Unicodes to be included (appended at end of selected range)
static final int[] specificUnicodes = {

  // Commonly used codes, add or remove // in next line
  // 0x00A3, 0x00B0, 0x00B5, 0x03A9, 0x20AC, // £ ° µ Ω €

  // Numbers and characters for showing time, change next line to //* to use
/*
    0x002B, 0x002D, 0x002E, 0x0030, 0x0031, 0x0032, 0x0033, 0x0034, // - + . 0 1 2 3 4
    0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x0061, 0x006D, // 5 6 7 8 9 : a m
    0x0070,                                                         // p
 //*/

  // More characters for TFT_eSPI test sketches, change next line to //* to use
  /*
    0x0102, 0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x010C, 0x010D,
    0x010E, 0x010F, 0x0110, 0x0111, 0x0118, 0x0119, 0x011A, 0x011B,
 
    0x0131, 0x0139, 0x013A, 0x013D, 0x013E, 0x0141, 0x0142, 0x0143,
    0x0144, 0x0147, 0x0148, 0x0150, 0x0151, 0x0152, 0x0153, 0x0154,
    0x0155, 0x0158, 0x0159, 0x015A, 0x015B, 0x015E, 0x015F, 0x0160,
    0x0161, 0x0162, 0x0163, 0x0164, 0x0165, 0x016E, 0x016F, 0x0170,
    0x0171, 0x0178, 0x0179, 0x017A, 0x017B, 0x017C, 0x017D, 0x017E,
    0x0192,
 
    0x02C6, 0x02C7, 0x02D8, 0x02D9, 0x02DA, 0x02DB, 0x02DC, 0x02DD,
    0x03A9, 0x03C0, 0x2013, 0x2014, 0x2018, 0x2019, 0x201A, 0x201C,
    0x201D, 0x201E, 0x2020, 0x2021, 0x2022, 0x2026, 0x2030, 0x2039,
    0x203A, 0x2044, 0x20AC,
 
    0x2122, 0x2202, 0x2206, 0x220F,
 
    0x2211, 0x221A, 0x221E, 0x222B, 0x2248, 0x2260, 0x2264, 0x2265,
    0x25CA,
 
    0xF8FF, 0xFB01, 0xFB02,
  //*/
};

//                       >>>>>>>>>> USER CONFIGURED PARAMETERS END HERE <<<<<<<<<<

////////////////////////////////////////////////////////////////////////////////////////////////

// Variable to hold the inclusive Unicode range (16 bit values only for this sketch)
int firstUnicode = 0;
int lastUnicode  = 0;

PFont myFont;

PrintWriter logOutput;

void setup() {
  logOutput = createWriter("FontFiles/System_Font_List.txt"); 

  size(1000, 800);

  // Print the available fonts to the console as a list:
  String[] fontList = PFont.list();
  printArray(fontList);

  // Save font list to file
  for (int x = 0; x < fontList.length; x++)
  {
    logOutput.print("[" + x + "] ");
    logOutput.println(fontList[x]);
  }
  logOutput.flush(); // Writes the remaining data to the file
  logOutput.close(); // Finishes the file

  // Set the fontName from the array number or the defined fontName
  if (fontNumber >= 0)
  {
    fontName = fontList[fontNumber];
    fontType = "";
  }

  char[]   charset;
  int  index = 0, count = 0;

  int blockCount = unicodeBlocks.length;

  for (int i = 0; i < blockCount; i+=2) {
    firstUnicode = unicodeBlocks[i];
    lastUnicode  = unicodeBlocks[i+1];
    if (lastUnicode < firstUnicode) {
      delay(100);
      System.err.println("ERROR: Bad Unicode range secified, last < first!");
      System.err.print("first in range = 0x" + hex(firstUnicode, 4));
      System.err.println(", last in range  = 0x" + hex(lastUnicode, 4));
      while (true);
    }
    // calculate the number of characters
    count += (lastUnicode - firstUnicode + 1);
  }

  count += specificUnicodes.length;

  println();
  println("=====================");
  println("Creating font file...");
  println("Unicode blocks included     = " + (blockCount/2));
  println("Specific unicodes included  = " + specificUnicodes.length);
  println("Total number of characters  = " + count);

  if (count == 0) {
    delay(100);
    System.err.println("ERROR: No Unicode range or specific codes have been defined!");
    while (true);
  }

  // allocate memory
  charset = new char[count];

  for (int i = 0; i < blockCount; i+=2) {
    firstUnicode = unicodeBlocks[i];
    lastUnicode  =  unicodeBlocks[i+1];

    // loading the range specified
    for (int code = firstUnicode; code <= lastUnicode; code++) {
      charset[index] = Character.toChars(code)[0];
      index++;
    }
  }

  // loading the specific point codes
  for (int i = 0; i < specificUnicodes.length; i++) {
    charset[index] = Character.toChars(specificUnicodes[i])[0];
    index++;
  }

  // Make font smooth (anti-aliased)
  boolean smooth = true;

  // Create the font in memory
  myFont = createFont(fontName+fontType, displayFontSize, smooth, charset);

  // Print characters to the sketch window
  fill(0, 0, 0);
  textFont(myFont);

  // Set the left and top margin
  int margin = displayFontSize;
  translate(margin/2, margin);

  int gapx = displayFontSize*10/8;
  int gapy = displayFontSize*10/8;
  index = 0;
  fill(0);

  textSize(displayFontSize);

  for (int y = 0; y < height-gapy; y += gapy) {
    int x = 0;
    while (x < width) {

      int unicode = charset[index];
      float cwidth = textWidth((char)unicode) + 2;
      if ( (x + cwidth) > (width - gapx) ) break;

      // Draw the glyph to the screen
      text(new String(Character.toChars(unicode)), x, y);

      // Move cursor
      x += cwidth;
      // Increment the counter
      index++;
      if (index >= count) break;
    }
    if (index >= count) break;
  }


  // creating font to save as a file
  PFont    font;

  font = createFont(fontName+fontType, fontSize, smooth, charset);

  println("Created font " + fontName + str(fontSize) + ".vlw");

  // creating file
  try {
    print("Saving to sketch FontFiles folder... ");

    OutputStream output = createOutput("FontFiles/" + fontName + str(fontSize) + ".vlw");
    font.save(output);
    output.close();

    println("OK!");

    delay(100);

    // Open up the FontFiles folder to access the saved file
    //String path = sketchPath();
    //Desktop.getDesktop().open(new File(path+"/FontFiles"));

    System.err.println("All done! Note: Rectangles are displayed for non-existant characters.");
  }
  catch(IOException e) {
    println("Doh! Failed to create the file");
  }
}
