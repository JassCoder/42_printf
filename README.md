*This project has been created as part of the 42 curriculum by jsingh*

## Description

**ft_printf** is a 42 school project that involves recoding the standard C library function `printf()`. The goal is to understand variadic functions and implement a function that mimics the behavior of the original `printf()`.

This implementation handles the following conversions:
- `%c` - Prints a single character
- `%s` - Prints a string (NULL prints "(null)")
- `%p` - Prints a pointer address in hexadecimal (NULL prints "(nil)")
- `%d` - Prints a decimal (base 10) number
- `%i` - Prints an integer in base 10
- `%u` - Prints an unsigned decimal (base 10) number
- `%x` - Prints a number in hexadecimal (base 16) lowercase
- `%X` - Prints a number in hexadecimal (base 16) uppercase
- `%%` - Prints a percent sign

The function returns the total number of characters printed, matching the behavior of the original `printf()`.

## Instructions

### Compilation

To compile the library, run:

```bash
make
```

This will create `libftprintf.a` at the root of the repository.

### Cleaning

| Command | Action |
|---------|--------|
| `make clean` | Remove object files (*.o) |
| `make fclean` | Remove object files and library |
| `make re` | Clean and rebuild everything |

### Usage

Include the header in your C file:

```c
#include "ft_printf.h"
```

Compile with the library:

```bash
cc your_program.c -L. -lftprintf -o your_program
```

### Example

```c
#include "ft_printf.h"

int main(void)
{
    ft_printf("Hello, %s!\n", "World");      // Output: Hello, World!
    ft_printf("Number: %d\n", 42);            // Output: Number: 42
    ft_printf("Hex: %x\n", 255);              // Output: Hex: ff
    ft_printf("Pointer: %p\n", &main);        // Output: Pointer: 0x...
    return (0);
}
```

## Implementation Details

### Architecture

The project follows a modular, layered architecture:

```
ft_printf()         → Main entry point, parses format string
    ↓
print_format()      → Dispatches to specific handlers based on specifier
    ↓
print_char()        → Handles %c
print_str()         → Handles %s
print_digit()       → Handles %d, %i, %x (lowercase)
print_digit_upper() → Handles %X (uppercase)
print_unsigned()    → Handles %u
print_pointer()     → Handles %p
```

### Algorithm Explanation

**1. Format String Parsing (`ft_printf()`)**

The main function iterates through the format string character by character:
- When a `%` is encountered, it advances to the next character (the specifier)
- If there is a valid specifier, it calls `print_format()` with the specifier and argument list
- If it's regular text, it prints it directly using `write()`
- The character count is accumulated and returned at the end

**Why this approach?**
- **Efficiency**: Direct iteration without intermediate buffer allocation
- **Simplicity**: No complex parsing logic - just character-by-character processing
- **Accuracy**: Matches the behavior of real printf for basic conversions

**2. Number Printing (`print_digit()`)**

This function uses **recursion** to print numbers in any base (2-16):

```c
if (n < base)
    print the digit directly
else
    print_digit(n / base)  // Recursively print higher digits
    print_digit(n % base)  // Print the last digit
```

**Why recursion?**
- **Elegance**: The recursive approach naturally handles the right-to-left digit order
- **Simplicity**: No need for arrays or string buffers to reverse digits
- **Base flexibility**: Works for any base from 2 to 16
- **Negative handling**: Prints '-' sign then recursively calls with positive value

**Example: `print_digit(42, 10)`**
```
print_digit(42, 10)
  → print_digit(4, 10)
    → print_digit(4 < 10) → prints '4'
  → print_digit(42 % 10 = 2, 10)
    → prints '2'
Result: "42"
```

**3. Pointer Printing (`print_pointer()`)**

Handles `%p` conversion:
- If pointer is NULL → prints `"(nil)"` (matching real printf)
- Otherwise → prints `"0x"` followed by the address in lowercase hex
- Uses `print_hex_long()` to recursively print the hex digits

**Why this approach?**
- **Portability**: Casts pointer to `unsigned long` for consistent printing
- **Compatibility**: Matches the exact format of real printf for NULL and valid pointers
- **Reusability**: Uses the same hex printing logic as `%x` specifier

**4. Data Structures**

This implementation uses **no complex data structures** intentionally:
- **Arrays**: String literals for digit mapping (`"0123456789abcdef"`)
- **No heap allocation**: No `malloc()` used, eliminating memory leak risks
- **Stack-only**: All data is stored on the stack (local variables)
- **Direct output**: Uses `write()` system call for immediate output

**Justification:**
- **Performance**: No heap allocation overhead
- **Simplicity**: No need for memory management
- **Reliability**: No risk of memory leaks or allocation failures
- **Mandatory compliance**: The subject explicitly allows only `write()`, `malloc()`, `free()`, and `va_*` functions

## Technical Choices

### 1. No Buffer Management
Unlike the original printf, this implementation does not use a buffer. Each character is written directly using `write()`.

**Why?**
- The subject explicitly requires: "Do not implement the buffer management of the original printf()"
- Simpler implementation
- Avoids the complexity of buffer flushing

### 2. Recursive Printing
The `print_digit()` function uses recursion instead of iterative string building.

**Advantages:**
- Clean, readable code
- No need for dynamic string allocation
- Automatically handles digit order

**Trade-offs:**
- Slight performance overhead for large numbers (limited recursion depth)
- Acceptable given the simplicity and readability benefits

### 3. Static Helper Functions
The `handle_str()` function in `print_format.c` is declared `static`.

**Why?**
- Limits scope to the file (encapsulation)
- Prevents accidental external use
- Cleaner separation of concerns

### 4. Modular File Organization
```
ft_printf.c          → Main function
print_format.c       → Format dispatcher + static helpers
ft_printf_utils.c    → Core utilities (char, str, digit, unsigned)
ft_printf_pointer.c  → Pointer-specific utilities
```

**Benefits:**
- Each file has a single responsibility
- Easy to locate and modify specific functionality
- Maintains 5-function-per-file norm limit
- Allows for future extensibility

## Resources

### Documentation

- [printf - C++ Reference](https://en.cppreference.com/w/c/io/fprintf)
- [Variadic functions in C](https://en.cppreference.com/w/c/variadic)
- [42 Network Norm Documentation](https://norminette.42.fr/)
- [GCC Makefile Tutorial](https://www.gnu.org/software/make/manual/)
- [youtube](https://www.youtube.com/)

### Articles & Tutorials

- [How printf works](https://www.geeksforgeeks.org/printf-in-c/)
- [Understanding variadic functions](https://www.tutorialspoint.com/cprogramming/c_variable_arguments.htm)
- [Recursive functions in C](https://www.geeksforgeeks.org/recursion-in-c/)

### AI Usage

**AI was used for the following tasks in this project:**

1. **Debugging Assistance**
   - Identifying segmentation faults in NULL string handling
   - Fixing buffer over-read when format string ends with `%`
   - Resolving variadic argument type mismatches

2. **Code Review and Optimization**
   - Reviewing code for 42 Norm compliance
   - Suggesting improvements for code organization
   - Identifying duplicate functions and suggesting file splitting

3. **Makefile Creation**
   - Structuring a proper Makefile with all required rules
   - Ensuring proper compilation flags and dependencies
   - Fixing tab vs space indentation issues

4. **Conceptual Understanding**
   - Explaining variadic function mechanics
   - Describing recursive number printing algorithms
   - Clarifying pointer printing requirements

**Areas where AI was NOT used:**
- Core logic implementation
- Algorithm design and architecture decisions
- Test case development and testing methodology
- Final code implementation decisions

## Testing

### Test Coverage

The project has been tested against the original `printf()` with comprehensive test cases covering:

| Test Category | Specifiers Tested | Status |
|---------------|-------------------|--------|
| Basic output | Text, strings, characters |  PASS |
| Numbers | `%d`, `%i`, `%u`, INT_MIN, INT_MAX |  PASS |
| Hex | `%x` (lowercase), `%X` (uppercase) |  PASS |
| Pointers | Valid pointers, NULL pointers |  PASS |
| Edge cases | Empty string, NULL string, `%` at end |  PASS |
| Mixed | Multiple specifiers in one call |  PASS |

### Running Tests

```bash
# Build the library
make

# Compile the test program (you will get from my private git repo)
cc test_main.c -L. -lftprintf -o test

# Run the tests
./test
```

All 20 test cases pass successfully, with return values matching the original `printf()`.

## Acknowledgments

This project was completed as part of the 42 curriculum. Special thanks to:
- 42 Network for providing the project and learning environment
- Peers who participated in code reviews and discussions
- The open-source community for documentation and reference materials

## License

This project is part of the 42 school curriculum. All rights reserved.