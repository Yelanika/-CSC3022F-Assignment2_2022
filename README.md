# Yelanika Gunasekara
# -CSC3022F-Assignment2_2023

FrameSequence.h:
  - This is the header file for the FrameSequence Class.
  - The FrameSequence class is used to implement all the methods for this assignment.

FrameSequence.cpp:
  - This is the source file where in which the methods for the FrameSequence Class is implemented.
  - The imageSequence vector is implemented in this file.

extractor.cpp:
- This is the driver source file which extracts the data from the command line.
- It also calls the methods of the FrameSequence Class here.

How to run the program:
- running 'make' will compile the project 
- 'extractor' is the is the executable file
- There are two formats for running the program:
  1. ./extractor imageName.pmg -t xStart yStart xEnd yEnd -s width height -w operationName fileName
  2. ./extractor imageName.pmg -p n x1 y1 x2 y3 .... xn yn -s width height -w operationName fileName

imageName.pgm:
 This is where you would enter the name of the image that you want manipulate. The image has to be of type 'pgm'.

-t flag:
  xStart and yStart will be the coordinates of the starting position of the frame 
  xEnd and yEnd will be the coordinates of the ending position of the frame

-s flag:
 This is the frame size you want for the images you are capturing, in terms of width and height

-w flag:
 OperationName - There are four operation that you can apply to the frames you will be extracting:
 1. none - nothing will be done to the frames.
 2. invert - each pixel value 'v'in a frame becomes 255-v.
 3. reverse - frames will be output from the last to the first.
 4. revinvert - the invert and reverse operations will be applied to the frames.

 fileName - This is name that will be given to each frame outputted. It will have the format: fileName0000.pgm, fileName0001.pmg, fileName0002.pmg.... and so on.

 Note: the -w flag can be written more than once, so you can run multiple operations, each will its own file name. For example:

  ./extractor imageName.pgm -t 0 0 500 1000 -s 200 400 -w none noneFrames -w invert invertFrames -w reverse reverseFrames -w revinvert revinvertFrames -w reverse reverseSet

-p flag:
 The 'n' represents the no. of x and y coordinates you will place.
 The frames will be outputted as moving from each coordinate to another.
 i.e., moving from point (x1,y1) to (x2,y2) to (x3,y3).... to (xn,yn).

 Note: n >= 2 

Program Constraints:
  1. The width and height for the frame that are entered have to be greater than zero, else an error is thrown and the program won't run. i.e., a width or height value that is <= 0, will throw an error.
  2. If the width and height of the frame entered are larger than the actual width and height of the image, black pixels will be placed after the boundary of the images width and height has been reached.
  3. If x and y coordinates are negative or go beyond the width and height of the actual image, i.e., the coordinates are out of bound, black pixels will be placed there.