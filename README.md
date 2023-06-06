# Who I am

- Name: Mohammed Omar Khan
- Student ID: H00358011
- Student username: mk2008

# Program design
The program takes in  command line arguments, a flag to check whether to encode(e) or decode(d) and the
location of the file on which the encode/decode is to be performed. The file locations are passed as a
char array to the loadPPMfromfile function which opens the file and ensures that the file has
successfully opened before passing the opened file to getPPM to parse the values from the file to the
correct variables in the PPM structure.

The encoding and decoding take a seed from the user to encode and decode the message. After the 
user inputs the seed, the srand function is called on the seed. While encoding, the length of the string is stored
in a random pixel's green value. After that, each character of the text separately replaces the value stored in the red
part of the pixel. While decoding, the length of the string is taken by calling the random function
using the same seed, which is then used to assign the correct memory for the text variable. Then,using
the same set of randomized pixel locations, it extracts the ASCII values of the encoded message. 

After the encoding is complete, the showPPM function is called to print the values to the standard output, which can be redirected to any file.. 

# Choice of data structures and algorithms

The data structures used here are the structures (for pixels and ppm),arrays(to store the pixels) and a linked list(to store
comments). The linked list is preferred for storing values dynamically. Since the length of the comment is unknown beforehand,
the linked list can store the values as they are taken from the file,without needing to allocate unneccesary memory. The structures 
are capable of storing variables of different data types so it's easier to store variables of multiple data types
and grouping them. This makes it preferable to store all the values from the PPM file in one
variable. A two-dimensional matrix is used to store the values of each pixel element. The matrix is of
dimensions width and height given in the ppm file. This ensures that all pixel values are correctly
stored at the correct position without affecting the image itself.
