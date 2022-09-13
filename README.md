# File-Censorship

This C++ program censors a given list of words. It reads from files for words to censor. If none are given, the input comes from standard input.

#Arguments
The arguments follow this order:
 * a possibly-empty list of words to censor
 * a mandatory dash ("-")
 * an optional list of files to read from
 * if no files are given, read from standard input. It will appear the program has stopped, but rather it is waiting to read from the keyboard. When you are done typing the input for the program, control-D indicates end of file from the keyboard.
 * sample argument after cmake . && make \
 ./hw3 Violets foo short - poem \
 This would censor foo, short and Violets from the file poem
 
* if poem was-\
Roses are red\
Violets are 177777\
This poem is too short

* after the command poem would be-
Roses are red
CENSORED are 177777
This poem is too CENSORED
 
 #Words
 This program only replaces a complete word. A word is defined as a sequence of letters, a...zA...Z bordered by non-letters or the start/end of a new line.
 
 #How to Complile
 * open the tar file in a directory
 * cmake . && make 
 * run the executable with the desired arguments


 
 
