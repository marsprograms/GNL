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

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

`get_next_line` must be called repeatedly (typically in a loop) until it returns `NULL`, which signals either end-of-file or an error. Each non-`NULL` call returns a newly heap-allocated line that the caller is responsible for freeing.

## Algorithm

The function relies on a single `static char *stash` that persists across calls and holds whatever has been read from the file descriptor but not yet returned to the caller.

Each call to `get_next_line` follows these steps:

1. **Validate input.** If `fd` is negative or `BUFFER_SIZE` is invalid, return `NULL` immediately. (As an internal convenience, calling `get_next_line(-1)` is also used to force-free the static stash and reset it, which is useful for cleanly terminating use of the function — for example in single-call test programs — without altering its normal looped behavior.)

2. **Read until a newline is found or EOF is reached.** As long as the stash does not already contain a `\n`, read another `BUFFER_SIZE` chunk from the file descriptor into a local buffer, and append it to the stash using `gnl_strjoin`. This loop only reads exactly as much as it needs to find at least one complete line — it never reads the whole file up front. This matters because `BUFFER_SIZE` can be arbitrarily small (e.g. `1`) or arbitrarily large (e.g. `9999999`), and the algorithm must behave correctly and efficiently in both cases: with a tiny buffer it simply takes more `read()` calls; with a huge buffer it may capture multiple lines in a single `read()`, which the stash mechanism handles transparently across calls.

3. **Handle read errors or empty stash.** If `read()` returns `-1`, or the stash ends up empty/`NULL`, the stash is freed and `NULL` is returned — this is the project's signal for "nothing left to read."

4. **Extract one line.** `extract_line` scans the stash for the first `\n` (or the end of the string, if EOF was reached without a trailing newline) and copies that portion — including the `\n` if present — into a new heap-allocated string. This is the line returned to the caller.

5. **Update the stash.** `update_stash` shifts the stash forward past the line that was just extracted, keeping only what comes after the newline. If nothing remains, the stash is freed and reset to `NULL`. This is what lets the function "remember its place" the next time it's called on the same file descriptor.

This approach was chosen because it satisfies the constraint of reading as little as possible from the file descriptor on each call, while still correctly assembling lines that may span multiple `read()` calls or, conversely, multiple lines that arrive within a single `read()`. The `static` stash is the only mechanism available in C to preserve that state between otherwise independent function calls without relying on a global variable, which goes against the Norm/subject.

### Helper functions

| Function | Purpose |
|---|---|
| `gnl_strlen` | Computes the length of a string, returns `0` on `NULL` |
| `find_new_line` | Searches a string for a given character, used to check whether the stash already contains a full line |
| `gnl_strjoin` | Concatenates the stash with a newly read buffer into a new heap allocation, freeing the old stash |
| `extract_line` | Copies the first line (up to and including `\n`, or up to the end of the string) out of the stash |
| `update_stash` | Returns a new stash containing everything after the extracted line, or `NULL` if nothing remains |

## Resources

- 42 peer to peer communication
- `man read` — manual page for the `read()` system call
- C documentation on the `static` storage class qualifier (videos, GeeksforGeeks, etc..)

### AI usage disclosure

- AI was used to help write this README and to debug and understand why there was a valgrind 'leak' when the function is called once instead of in a loop (like the subject specifies).

- It was also used to understand the difference between heap memory that is genuinely leaked versus heap memory that is still reachable through a valid pointer (the `static` stash) at program exit.