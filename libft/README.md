*This project has been created as part of the 42 curriculum by jsingh.*

## Description
 
Libft is my own version of a bunch of standard C library functions, plus some extra utility functions for strings, memory and linked lists. Every project after this one in the common core uses this library, so it's basically my toolbox from here on.
 
- Part 1: 23 reimplemented libc functions
- Part 2: 11 extra utility functions
- Bonus: 9 linked list functions
## Instructions
 
Compile with:
 
```
make
```
 
This builds `libft.a`.
 
- `make` / `make all` - builds the mandatory part
- `make clean` - removes .o files
- `make fclean` - removes .o files and libft.a
- `make re` - fclean then rebuild
To use it in another project:
 
```c
#include "libft.h"
```
 
```
cc -Wall -Wextra -Werror your_program.c -L. -lft
```
 
## Resources
 
### References
 
- man pages for every libc function I reimplemented
- 42 Libft subject pdf - the actual requirements and norm rules
- Beej's Guide to C Programming - used these when I got stuck on pointers and memory stuff
- GeeksforGeeks linked list articles
 
## Library
 
Libft reimplements 23 standard C library functions, adds 11 extra utility functions that don't exist in libc but are useful for later projects, and (bonus) implements a singly linked list with 9 functions to create, add to, iterate, map and free lists.
 
**Part 1 - libc functions (23)**
 
- Character checks: isalpha, isdigit, isalnum, isascii, isprint
- String functions: strlen, strlcpy, strlcat, strchr, strrchr, strncmp, strnstr, strdup
- Memory functions: memset, bzero, memcpy, memmove, memchr, memcmp, calloc
- Conversion: atoi, toupper, tolower
**Part 2 - extra functions (11)**
 
- substr, strjoin, strtrim, split - for cutting up and rebuilding strings
- itoa - int to string
- strmapi, striteri - apply a function over a string
- putchar_fd, putstr_fd, putendl_fd, putnbr_fd - output helpers that write straight to a file descriptor instead of going through stdio
**Part 3 - linked list (9)**
 
- lstnew, lstadd_front, lstadd_back - build the list
- lstsize, lstlast - read/inspect the list
- lstdelone, lstclear - free the list
- lstiter, lstmap - apply a function over the list, with lstmap building a new list
A full breakdown of every function - prototype, what the man page says, what it returns, and a test case I checked against the real function - is in the Function notes section below.
 
## Function notes
 
### Part 1 - libc functions
 
- `ft_isalpha` — Returns true if the character is a letter (a–z or A–Z).
- `ft_isdigit` — Returns true if the character is a digit (0–9).
- `ft_isalnum` — Returns true if the character is a letter or digit (built on isalpha/isdigit).
- `ft_isascii` — Returns true if the character's value fits in standard ASCII (0–127).
- `ft_isprint` — Returns true if the character is printable (space through `~`, 32–126).
- `ft_strlen` — Counts characters in a string up to (not including) the null terminator.
- `ft_strlcpy` — Copies src into dst up to size-1 bytes, always null-terminates; returns the length it would have needed.
- `ft_strlcat` — Appends src onto dst up to size total bytes; returns the combined length it would have needed.
- `ft_strchr` — Finds the first occurrence of a character in a string, including the terminating `\0`.
- `ft_strrchr` — Finds the last occurrence of a character in a string, including the terminating `\0`.
- `ft_strncmp` — Compares up to `n` bytes of two strings, byte by byte, as unsigned char.
- `ft_strnstr` — Finds the first occurrence of a substring within a bounded length of the string.
- `ft_strdup` — Allocates and returns a copy of a string.
- `ft_memset` — Fills a block of memory with a given byte value, `n` times.
- `ft_bzero` — Zeroes out a block of memory; a thin wrapper around `ft_memset`.
- `ft_memcpy` — Copies `n` bytes from src to dst; undefined if the regions overlap.
- `ft_memmove` — Same as memcpy but safe for overlapping regions, by copying in the right direction.
- `ft_memchr` — Finds the first occurrence of a byte within the first `n` bytes of a memory block.
- `ft_memcmp` — Compares the first `n` bytes of two memory blocks as unsigned char.
- `ft_calloc` — Allocates zeroed memory for `count` elements of `size`, guarding against overflow.
- `ft_atoi` — Parses leading whitespace, an optional sign, then digits into an int.
- `ft_toupper` — Converts a lowercase letter to uppercase; other characters pass through unchanged.
- `ft_tolower` — Converts an uppercase letter to lowercase; other characters pass through unchanged.
### Part 2 - extra functions
 
- `ft_substr` — Allocates and returns a substring of `s`, starting at `start`, up to `len` characters.
- `ft_strjoin` — Allocates and returns a new string that is s1 followed by s2.
- `ft_strtrim` — Allocates and returns a copy of s1 with characters in `set` stripped from both ends.
- `ft_split` — Allocates and returns a NULL-terminated array of substrings, split on a delimiter character.
- `ft_itoa` — Converts an int (including INT_MIN) into a newly allocated string.
- `ft_strmapi` — Builds and returns a new string by applying a function to each index/char pair of s.
- `ft_striteri` — Applies a function to each index/char pair of s, modifying s in place.
- `ft_putchar_fd` — Writes a single character to the given file descriptor.
- `ft_putstr_fd` — Writes a string to the given file descriptor (NULL-safe).
- `ft_putendl_fd` — Writes a string followed by a newline to the given file descriptor.
- `ft_putnbr_fd` — Writes an int (including INT_MIN) as text to the given file descriptor.
### Part 3 - linked list
 
- `ft_lstnew` — Allocates a new list node holding the given content, with `next` set to NULL.
- `ft_lstadd_front` — Inserts a node at the front of the list, updating the list head.
- `ft_lstsize` — Counts the number of nodes in a list by walking it.
- `ft_lstlast` — Returns a pointer to the last node in a list.
- `ft_lstadd_back` — Inserts a node at the end of the list, walking to the last node first.
- `ft_lstdelone` — Frees a single node after calling a delete function on its content.
- `ft_lstclear` — Frees every node in a list (and their content), setting the list head to NULL.
- `ft_lstiter` — Applies a function to the content of every node in a list, without modifying structure.
- `ft_lstmap` — Builds and returns a new list by applying a function to each node's content, cleaning up on allocation failure.
## Author
 
jsingh - 42 Warsaw
