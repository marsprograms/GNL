*This project has been created as part of the 42 curriculum by mariade-.*

# Get_Next_Line

## Description

`get_next_line` is a 42 School project that recreates a function which does not exist in the standard C library: a function able to read a text file (or any file descriptor, including standard input) **one line at a time**, regardless of how the file is structured or how large it is.

The function reads from a given file descriptor using small, fixed-size chunks (`BUFFER_SIZE` bytes per `read()` call), buffers what it has read so far between calls, and hands back exactly one line — including the trailing `\n` if present — every time it is called. State between calls (what has already been read but not yet returned) is preserved using a `static` variable, since the function has no other way of remembering where it left off between separate calls.

The goal of the project is to understand:
- how the `static` storage class works in C, and how it differs from local/global variables
- how to read from a file descriptor in fixed-size chunks instead of all at once
- how to manage and grow a buffer dynamically with `malloc`/`free`
- how to avoid memory leaks across an arbitrary number of calls

# Instructions

### Compilation

The project must be compiled with a `BUFFER_SIZE` defined at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

If `-D BUFFER_SIZE` is omitted, the project still compiles, falling back to a default value of `42` (defined in `get_next_line.h`):

### Usage

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int fd = open("file.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[BUFFER]%s", line);
		free(line);
	}
	close(fd);
}
```

`get_next_line` must be called repeatedly (typically in a loop) until it returns `NULL`, which signals either end-of-file or an error. Each non-`NULL` call returns a newly heap-allocated line that the caller is responsible for freeing.

## Algorithm

The function relies on a single `static char buffer[BUFFER_SIZE + 1]`, declared inside `get_next_line` itself, that persists across calls. Unlike a design with a separate "stash", this buffer does double duty: it's both the target that `read()` writes fresh bytes into, and the storage that holds whatever was read but not yet handed back to the caller, since it keeps its contents between one call and the next.
 
Each call to `get_next_line` follows these steps:
 
1. **Validate input.** If `fd` is negative or `BUFFER_SIZE` is invalid, return `NULL` immediately.

2. **Refill the buffer only when it's empty.** At the start of each loop iteration, if `buffer` is currently empty (`!*buffer`), a `read()` of up to `BUFFER_SIZE` bytes is performed directly into it, and the result is null-terminated at `bytes_read`. If `buffer` already holds leftover data from a previous call, this step is skipped — nothing is read until that leftover is used up. This is what keeps the function from reading more than it needs to: with a tiny `BUFFER_SIZE` it just takes more `read()` calls; with a huge one, a single `read()` can capture several lines at once, and they get consumed one at a time across subsequent calls without any extra reading.

3. **Handle read errors or EOF.** If `read()` returns `-1`, the line built up so far is freed and `NULL` is returned. If `read()` returns `0` (EOF), whatever has been assembled in `line` so far is returned as-is (a partial final line, or `NULL` if nothing was left to read).

4. **Append up to the next newline.** `gnl_strjoin(line, buffer)` allocates a new string, copies the existing `line` into it, then appends `buffer` — but only up to and including the first `\n` it finds (or the whole buffer, if no `\n` is present yet), since the amount to copy is measured by `gnl_strlen`, which stops at the first `\n` (inclusive) or at the terminating `\0`. The old `line` is freed inside `gnl_strjoin`, and the new, longer string becomes the current `line`.

5. **Shift the buffer.** `update_buffer` removes the portion that was just appended to `line` (using that same `gnl_strlen` measurement) and moves whatever bytes remain after it to the front of `buffer`, null-terminating the result. If nothing was consumed, the whole buffer is emptied. This is what lets any leftover data survive into the next call.

6. **Check for completion.** `find_new_line(line, '\n')` checks whether `line` now contains a `\n`. If it does, the loop breaks and the line is complete. If not, the loop repeats — either consuming leftover data still sitting in `buffer`, or triggering a fresh `read()` once `buffer` is empty again.
This approach satisfies the constraint of reading as little as possible from the file descriptor on each call, while still correctly assembling lines that may span multiple `read()` calls or, conversely, multiple lines that arrive within a single `read()`. Folding the stash and the read buffer into one `static` array is what lets the function "remember its place" between otherwise independent calls without resorting to a global variable, which would go against the Norm/subject.


### Helper functions

| Function | Purpose |
|---|---|
| `gnl_strlen` | Computes the length of the line (string) including 1 extra for the '\n'|
| `find_new_line` | Searches the line (string) for a given character ('\n'), used to check whether the buffer already contains a full line and also returns it counting with the '\n'|
| `gnl_strjoin` | Concatenates the line and buffer into a new heap allocated string, freeing the old line |
| `ft_memcpy` | has the same behavior as the Libft version and is used to save lines and clean up my code in the `gnl_strjoin` function |
| `update_buffer` | Updates the buffer so it contains everything after the joined line and NULL terminates it|

## Resources

- 42 peer to peer communication
- `man read` — manual page for the `read()` system call
- C documentation on the `static` variable (videos, GeeksforGeeks, etc..)

### AI usage disclosure

- AI was used to help write this README and to debug different previous versions.