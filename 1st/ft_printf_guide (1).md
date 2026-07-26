# ft_printf — Pair-Programming Build Guide

> Style note: this follows your usual format — small incremental steps, test
> against real `printf` after each one, Norm checkpoints, git commits along the
> way. It is **not** a finished library to paste in. The subject explicitly
> bans using AI for direct answers, and during defense you have no internet —
> so treat this as a session where I explain the reasoning and you write/adapt
> the code, not as a solved project.

---

## 0. Before you touch code: understand the shape of the problem

`printf` is really just: **walk the format string, and every time you see
`%`, look at the next character and decide which "print this type" helper to
call.** Everything else (the va_list machinery, the dispatch, the Makefile)
exists to serve that one loop.

Subject constraints to keep in your head the whole time:
- No buffer management required (unlike real libc) — just `write()` as you go, or build a small buffer and flush once. Either is fine; the return value must equal the number of characters printed.
- Conversions required: `c s p d i u x X %`
- Return type: `int` — number of characters printed, or -1 on error (real printf does this; graders will check it).
- Allowed: `malloc`, `free`, `write`, `va_start`, `va_arg`, `va_copy`, `va_end`. Nothing else (no `vsnprintf`, no libc printf itself).
- libft is authorized — copy it into a `libft/` folder if you want `ft_strlen` etc.

---

## 1. Project skeleton

```
.
├── Makefile
├── ft_printf.h
├── ft_printf.c
├── srcs/
│   ├── ft_print_char.c
│   ├── ft_print_str.c
│   ├── ft_print_ptr.c
│   ├── ft_print_int.c
│   ├── ft_print_uint.c
│   └── ft_print_hex.c
└── libft/          (optional, only if you use it)
```

**ft_printf.h**
```c
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

// one helper per conversion, each returns the number of chars written
int	ft_print_char(char c);
int	ft_print_str(char *s);
int	ft_print_ptr(void *ptr);
int	ft_print_int(int n);
int	ft_print_uint(unsigned int n);
int	ft_print_hex(unsigned int n, char format);

#endif
```

**Checkpoint:** `git add ft_printf.h && git commit -m "printf: header + prototypes"`

---

## 2. Step 1 — the loop and the simplest conversion (`%%` and `%c`)

Get the *shape* right before worrying about every conversion:

```c
int ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	count = 0;
	i = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 'c')
				count += ft_print_char(va_arg(args, int)); // char is promoted to int in varargs
			else if (format[i] == '%')
				count += ft_print_char('%');
			// ... other conversions go here as you add them
		}
		else
			count += ft_print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
```

`ft_print_char`:
```c
int ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}
```

**Test it now, before adding anything else:**
```c
int main(void)
{
	int a = printf("%c%%%c\n", 'x', 'y');
	int b = ft_printf("%c%%%c\n", 'x', 'y');
	printf("libc=%d ft=%d\n", a, b);
}
```
Both lines must print identically and both return values must match. Don't move on until this passes — this is your regression baseline for every conversion you add.

**Checkpoint:** commit here. `git commit -am "printf: loop skeleton + %c %%"`

---

## 3. Step 2 — `%s`

The trap here isn't the happy path, it's `NULL`:
```
printf("%s", NULL) -> prints "(null)" on most libcs (glibc does; behavior is
technically implementation-defined, but the 42 grader compares against your
system's printf, so match what your system does — check with a quick test).
```

Write `ft_print_str` to handle `NULL` explicitly, then loop over the string
with `write` (or accumulate length then one `write`, your choice).

```c
int ft_print_str(char *s)
{
	int i;

	if (!s)
		return (ft_print_str("(null)"));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
```

Wire `%s` into the dispatch, then test:
```c
printf("[%s][%s][%s]\n", "hello", "", NULL);
ft_printf("[%s][%s][%s]\n", "hello", "", NULL);
```
Compare return values too, not just output — that's the part people forget and lose points on.

**Checkpoint:** commit.

---

## 4. Step 3 — `%d` / `%i`

These are identical in behavior (both print a signed decimal int) — same
helper, two entries in the dispatch.

The classic evaluator trap: **`INT_MIN` (-2147483648) cannot be negated** —
`-INT_MIN` overflows a 32-bit int (undefined behavior). Two common fixes:
1. Cast to `long` before negating: `long ln = n; if (ln < 0) ln = -ln;`
2. Or special-case it and print the digits of `2147483648` directly.

Think through *why* this happens before copying either fix — it's the #1
question evaluators ask on this project. (Hint: two's complement range is
asymmetric: -2147483648 to 2147483647.)

```c
static int	ft_putnbr_recursive(long n)
{
	int count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= 10)
		count += ft_putnbr_recursive(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	return (count + 1);
}

int ft_print_int(int n)
{
	return (ft_putnbr_recursive((long)n));
}
```

**Test against real printf with these exact cases** — don't skip any:
```c
int tests[] = {0, -1, 42, -42, 2147483647, -2147483648};
```
For each, run both `printf("%d\n", tests[i])` and `ft_printf("%d\n", tests[i])`
and diff the output + return value.

**Checkpoint:** commit. This is a good moment for a Norm pass on what you have so far too.

---

## 5. Step 4 — `%u`

Same recursive idea, but the argument comes off `va_arg` as `unsigned int` —
no sign to handle, so it's simpler, but resist copy-pasting `ft_print_int` and
just deleting the sign check without re-testing. `va_arg(args, unsigned int)`
matters: pulling it as `int` and casting later can bite you if you're not
careful with how you're storing it before printing.

```c
int ft_print_uint(unsigned int n)
{
	int count;

	count = 0;
	if (n >= 10)
		count += ft_print_uint(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	return (count + 1);
}
```

Test with `0`, `4294967295` (UINT_MAX), and a negative int passed in (e.g.
`ft_printf("%u", -1)` should print `4294967295` — that's the whole point of
unsigned wraparound, verify you get it for free from the type of the parameter).

**Checkpoint:** commit.

---

## 6. Step 5 — `%x` / `%X`

Base 16, lower/upper case digit table, no `0x` prefix (that's only for `%p`
and the bonus `#` flag). Reuse the recursive pattern with a digit string of
`"0123456789abcdef"` or `"0123456789ABCDEF"` depending on the `format`
character.

```c
int ft_print_hex(unsigned int n, char format)
{
	char *base;
	int count;

	base = (format == 'x') ? "0123456789abcdef" : "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		count += ft_print_hex(n / 16, format);
	write(1, &base[n % 16], 1);
	return (count + 1);
}
```

Test `0`, `255`, `UINT_MAX` for both `x` and `X`.

**Checkpoint:** commit.

---

## 7. Step 6 — `%p`

This is where people lose points carelessly. Real `printf("%p", ptr)`:
- Prints `0x` followed by the hex address, lowercase.
- `NULL` prints as `(nil)` (glibc) or `0x0` depending on system — check what
  *your* system's printf actually does and match it, same as `%s`/NULL.
- The argument is a `void *`, not an int — you need to convert an address to
  a number you can do division/modulo on. `unsigned long` is the usual
  choice since pointers on x86_64 are 64-bit.

```c
int ft_print_ptr(void *ptr)
{
	unsigned long addr;
	int count;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	count = write(1, "0x", 2);
	if (addr >= 16)
		count += ft_print_ptr_recursive(addr / 16); // write a small recursive helper, same pattern as %x
	write(1, &"0123456789abcdef"[addr % 16], 1);
	return (count + 1);
}
```
(Left the recursive helper as a one-liner exercise — it's the exact same
shape as `ft_print_hex`, just on `unsigned long` instead of `unsigned int`.)

Test with a real address (`&some_variable`), `NULL`, and `(void *)0x1`.

**Checkpoint:** commit.

---

## 8. Wiring the full dispatch + return value

Now go back to `ft_printf` and route every conversion character to its
helper, accumulating `count`. Also decide your error behavior: what should
`ft_printf("%")` (percent at end of string, nothing after it) do? What about
an unknown conversion like `%z`? Real printf's behavior here is a good thing
to test *before* deciding — don't guess.

Run a broader regression once all six conversions are wired:
```c
printf ("[%d][%i][%u][%x][%X][%c][%s][%p][%%]\n", -5, 5, 5, 255, 255, 'a', "hi", &count, );
ft_printf("[%d][%i][%u][%x][%X][%c][%s][%p][%%]\n", -5, 5, 5, 255, 255, 'a', "hi", &count, );
```
Compare byte-for-byte and compare return values.

**Checkpoint:** commit — this is your "mandatory part functionally done" commit.

---

## 9. Makefile (ar-based, no libtool)

```makefile
NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= ft_printf.c srcs/ft_print_char.c srcs/ft_print_str.c \
			  srcs/ft_print_ptr.c srcs/ft_print_int.c srcs/ft_print_uint.c \
			  srcs/ft_print_hex.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
```
Subject requires `ar` specifically (not `libtool`), and `libftprintf.a` must
land at the repo root — the `$(NAME) = libftprintf.a` with no path prefix
handles that as long as your Makefile itself lives at the root.

**Checkpoint:** commit, then do a clean `make re` and re-run your whole test suite once more from a fresh build — this catches missing-header / relinking bugs the grader will hit too.

---

## 10. Norm pass

Run `norminette` now (bonus files are norm-checked too, so do this before
touching bonus). Common norm issues on this project specifically:
- Recursive functions with more than 5 variables — keep helpers lean.
- Ternaries are allowed but nested ternaries are not.
- Each function ≤ 25 lines, ≤ 4 parameters.

---

## 11. Bonus (only after mandatory is 100% — the subject is explicit that bonus isn't even looked at otherwise)

Bonus scope from the subject:
- Flags `-` `0` and field width, on all conversions.
- Flags `#`, `+`, and space, plus precision `.`

Don't bolt these onto your Step 1–8 helpers by hacking in extra branches.
The cleaner pattern (and the one that survives a "modify this on the spot"
defense request) is a small struct you parse once per `%...` sequence:

```c
typedef struct s_flags
{
	int minus;
	int zero;
	int plus;
	int space;
	int hash;
	int width;
	int precision;  // -1 if not specified
}	t_flags;
```
Parse into this struct *before* dispatching to a conversion, then have each
`ft_print_*` helper take a `t_flags` (or the padding logic wraps around the
existing helpers — either architecture is defensible, but decide and be able
to explain the trade-off at defense).

I'd suggest building this incrementally the same way as above: get `-` and
`0` and width working for `%d` only, test thoroughly, *then* generalize to
the other conversions, rather than writing the general parser first. Want me
to walk through just the flag-parsing step the same way, once mandatory is
solid?

---

## 12. Known failure modes / pitfall table

| Symptom | Likely cause |
|---|---|
| Segfault on `%s` with NULL | Didn't guard `NULL` before dereferencing |
| Wrong output only for `INT_MIN` | Negation overflow — see step 3 |
| `%p` off by a few chars vs system printf | NULL handling mismatch (`(nil)` vs `0x0`) — check your system |
| Return value wrong but output looks right | Not accumulating `count` from every helper, or double-counting the `%` itself |
| Works standalone, breaks when combined with libft | Duplicate symbol names between your printf helpers and libft — namespace clash at link time |
| Norm fails only on bonus files | Forgot bonus files are norm-checked too (subject says so explicitly) |
| Leak on `va_copy` paths (if you use one for width/precision tricks) | Missing matching `va_end` for every `va_copy`/`va_start` |

---

## 13. README.md — required sections (per this subject's Readme Requirements chapter)

```markdown
*This project has been created as part of the 42 curriculum by <yourlogin>.*

## Description
[goal + brief overview of ft_printf]

## Instructions
[compile with make, link -L. -lftprintf, include ft_printf.h]

## Resources
[man 3 printf, C variadic functions references, etc — and a section
describing how AI was used and for which parts, as the subject requires]

## Algorithm / Data Structure justification
[explain the recursive digit-printing approach, and if you do bonus,
the flags struct — this section is explicitly required, not optional]
```

---

Want to keep going with the bonus flag-parsing step next, in the same
incremental/test-against-libc style?
