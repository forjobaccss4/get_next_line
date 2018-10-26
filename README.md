<h2><b>Get Next Line C project</b></h2><br>

This is the function that returns a line read from a file descriptor.<br><br>
  ```int get_next_line(const int fd, char **line)```<br><br> 
The first parameter _```const int fd```_ is the file descriptor that will be used to read.
The second parameter _```char **line```_ is the address of a pointer to a character that will be used
to save the line read from the file descriptor.
The return value can be 1, 0 or -1 depending on whether a line has been read,
when the reading has been completed, or if an error has happened respectively.
