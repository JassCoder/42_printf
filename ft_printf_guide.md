# ft_printf — Build It With Me, Step by Step

This is a pair-programming guide. We're not going to write the finished project and hand it to you — we're going to build it one conversion at a time, test constantly, and commit at every checkpoint. By the end you'll understand *why* every line exists, not just that it compiles.

Rule for this whole guide: **if you can't explain why a line is there, don't move to the next step.**

---

## Step 0 — Setup

```bash
mkdir ft_printf && cd ft_printf
git init
touch ft_printf.h ft_printf.c Makefile
mkdir libft   # if you're linking your libft, put it here or symlink it
```

`ft_printf.h`:

```c
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

#endif
```

Nothing fancy yet. We'll add prototypes for helper functions as we write them, not before — no point declaring functions you don't have yet.

**Checkpoint:** `git add -A && git commit -m "init: skeleton files"`

---

## Step 1 — The dumbest version that could possibly work

**Goal:** print literal text, no `%` handling at all. This proves your loop and your `write` counting are correct before you add any complexity.

```c
#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		write(1, &format[i], 1);
		count++;
		i++;
	}
	va_end(args);
	return (count);
}
```

Notice: `va_start`/`va_end` are already here even though we don't use `args` yet. That's deliberate — it forces you to think about the variadic machinery from line one instead of bolting it on later.

**Test it** — `main.c`:

```c
#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;

	a = ft_printf("Hello, 42!\n");
	b = printf("Hello, 42!\n");
	printf("mine=%d real=%d\n", a, b);
	return (0);
}
```

Compile: `cc ft_printf.c main.c -o test && ./test`

If `mine` and `real` don't match, stop — don't add `%d` on top of a broken counter. Fix the loop first.

**Checkpoint:** commit.

---

## Step 2 — `%c` and `%%`

**Goal:** the first real branch in your parser. This is the shape every later conversion follows.

```c
static int	print_char(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);   // char is promoted to int in variadic calls
	write(1, &c, 1);
	return (1);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] == 'c')
		{
			count += print_char(args);
			i += 2;
		}
		else if (format[i] == '%' && format[i + 1] == '%')
		{
			write(1, "%", 1);
			count++;
			i += 2;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
			i++;
		}
	}
	va_end(args);
	return (count);
}
```

**Why `va_arg(args, int)` and not `char`?** The variadic ABI promotes `char` and `short` to `int` when passed through `...`. Ask for `char` here and you'll read garbage on some platforms.

**Test:**

```c
ft_printf("%c %c %c\n", 'A', 'B', 'C');
ft_printf("100%%\n");
```

This `if/else if` chain is already ugly and about to get worse. That's fine for now — Step 7 is where we refactor into a real dispatcher. Don't over-engineer early; get conversions *correct* first, structure them *later*.

**Checkpoint:** commit.

---

## Step 3 — `%s`

**Goal:** strings, with the NULL edge case real printf handles specially.

```c
static int	print_str(va_list args)
{
	char	*s;
	int		i;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
```

Plug it into the dispatcher exactly like `print_char` — add a branch for `format[i+1] == 's'`.

**Test — this one matters, don't skip it:**

```c
ft_printf("%s\n", "hello");
ft_printf("%s\n", NULL);          // must print "(null)" and count 6
ft_printf("string: %s, char: %c\n", "test", 'X');
```

**Pitfall:** some evaluators mark you down for `(null)` and want a segfault-safe empty print instead — check your subject's exact wording once, and once only, then move on.

**Checkpoint:** commit.

---

## Step 4 — `%d` and `%i`

**Goal:** signed integers, including the one input that breaks naive solutions: `INT_MIN`.

**Decision point.** Two honest options:

1. **`ft_itoa`-style:** convert to a heap string, print it, free it.
2. **Recursive print:** no allocation, prints digit by digit.

I'll show recursive, because it's what most 42 students settle on for `ft_printf` (no malloc to leak, and the recursion is short):

```c
static int	print_nbr(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		write(1, "-", 1);
		count++;
		n = -n;
	}
	if (n >= 10)
		count += print_nbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	return (count + 1);
}

static int	print_int(va_list args)
{
	long	n;

	n = (long)va_arg(args, int);
	return (print_nbr(n));
}
```

**Why `long` and not `int`?** `INT_MIN` is `-2147483648`. Doing `n = -n` on that value *as an int* is undefined behavior — there's no positive `INT_MAX+1` to represent it. Widening to `long` before negating sidesteps the whole problem. This is the single most common bug in student `ft_printf` submissions — it passes every test except the one with `INT_MIN`, and evaluators know to test exactly that.

**Test — all of these, not just the easy ones:**

```c
ft_printf("%d\n", 42);
ft_printf("%d\n", -42);
ft_printf("%d\n", 0);
ft_printf("%d\n", INT_MIN);   // -2147483648
ft_printf("%d\n", INT_MAX);
ft_printf("%i\n", 123);
ft_printf("%d %s %c\n", 42, "hello", 'A');   // multiple args in sequence
```

`%i` and `%d` are identical in behavior for output — just route both to `print_int`.

**Checkpoint:** commit. This is the step most people get evaluated on hardest — don't rush it.

---

## Step 5 — `%u`

**Goal:** unsigned, no sign logic at all.

```c
static int	print_unbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n >= 10)
		count += print_unbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
	return (count + 1);
}

static int	print_uint(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (print_unbr(n));
}
```

**Test:**

```c
ft_printf("%u\n", 42);
ft_printf("%u\n", -1);   // must print 4294967295 — this is the point of the test
ft_printf("%u\n", 0);
```

`-1` passed to `%u` reinterprets the bit pattern as unsigned — `va_arg(args, unsigned int)` does that reinterpretation for you automatically, so there's nothing extra to write. If you get anything other than `4294967295`, the bug is upstream (probably you're still using `int` somewhere in the chain).

**Checkpoint:** commit.

---

## Step 6 — `%x`, `%X`, `%p`

**Goal:** base conversion, reused three ways.

```c
static int	print_base(unsigned long n, char *base)
{
	int	len;
	int	count;

	len = 0;
	while (base[len])
		len++;
	count = 0;
	if (n >= (unsigned long)len)
		count += print_base(n / len, base);
	write(1, &base[n % len], 1);
	return (count + 1);
}

static int	print_hex(va_list args, char *base)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (print_base((unsigned long)n, base));
}

static int	print_ptr(va_list args)
{
	unsigned long	addr;
	int				count;

	addr = (unsigned long)va_arg(args, void *);
	count = 0;
	if (addr == 0)
	{
		write(1, "0x0", 3);
		return (3);
	}
	write(1, "0x", 2);
	count += 2;
	count += print_base(addr, "0123456789abcdef");
	return (count);
}
```

Call `print_hex(args, "0123456789abcdef")` for `%x`, `print_hex(args, "0123456789ABCDEF")` for `%X`.

**Pitfall — check this before you evaluate:** some 42 subjects require NULL pointer to print `(nil)`, others want `0x0`. This is one of the few things that's genuinely inconsistent between campuses/subject versions. Open your actual subject PDF, search for "nil", and settle it now — don't guess in your defense.

**Test:**

```c
ft_printf("%x\n", 255);     // ff
ft_printf("%X\n", 255);     // FF
ft_printf("%p\n", &main);   // 0x... (compare against printf's own %p)
ft_printf("%p\n", NULL);
```

**Checkpoint:** all mandatory conversions now work. Commit — this is a real milestone, tag it if you want: `git tag mandatory-complete`.

---

## Step 7 — Refactor for the Norm (≤25 lines/function)

Nothing here changes behavior — this is purely structural. Split into:

```
ft_printf.h              — all prototypes
ft_printf.c              — main loop + dispatcher
ft_printf_utils.c        — print_char, print_str
ft_printf_numbers.c      — print_nbr, print_unbr
ft_printf_base.c         — print_base, print_hex, print_ptr
```

The dispatcher, once you pull it out of the giant `if/else if` chain:

```c
static int	dispatch(char c, va_list args)
{
	if (c == 'c')
		return (print_char(args));
	if (c == 's')
		return (print_str(args));
	if (c == 'd' || c == 'i')
		return (print_int(args));
	if (c == 'u')
		return (print_uint(args));
	if (c == 'x')
		return (print_hex(args, "0123456789abcdef"));
	if (c == 'X')
		return (print_hex(args, "0123456789ABCDEF"));
	if (c == 'p')
		return (print_ptr(args));
	if (c == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			count += dispatch(format[i + 1], args);
			i += 2;
		}
		else
		{
			write(1, &format[i], 1);
			count++;
			i++;
		}
	}
	va_end(args);
	return (count);
}
```

Much cleaner than the Step 2 version — this is why we didn't bother refactoring earlier. Premature structure on 3 conversions is wasted effort; on 7 conversions it's necessary.

Run `norminette` now. Fix whatever it flags before adding more code on top.

**Checkpoint:** commit.

---

## Step 8 — Makefile

```makefile
NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= ft_printf.c ft_printf_utils.c ft_printf_numbers.c ft_printf_base.c
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

**Checkpoint:** `make && make clean && make re` all run clean, no warnings. Commit.

---

## Step 9 — Testing strategy before you trust it

Three passes, in order:

1. **Isolation** — each conversion alone, nothing else.
2. **Combination** — several conversions in one call string, in the order your subject's examples use.
3. **Adversarial** — the inputs designed to break naive code: `INT_MIN`, `NULL`, `0`, empty string `""`, a format string with no `%` at all, a format string that's *only* `%`.

Comparison harness against real `printf`:

```c
#include <stdio.h>
#include "ft_printf.h"

#define TEST(fmt, ...) do { \
	int r = printf(fmt, __VA_ARGS__); \
	int m = ft_printf(fmt, __VA_ARGS__); \
	printf(" [real=%d mine=%d %s]\n", r, m, r == m ? "OK" : "MISMATCH"); \
} while (0)

int	main(void)
{
	TEST("%d\n", 42);
	TEST("%d\n", INT_MIN);
	TEST("%s\n", (char *)NULL);
	TEST("%u\n", -1);
	TEST("%x\n", 255);
	TEST("%p\n", &main);
	return (0);
}
```

Anything that prints `MISMATCH` is a bug — find it before your evaluation does.

Also run `valgrind ./test` if you allocated anything anywhere (e.g. if you went the `ft_itoa` route in Step 4) — leaks here are an automatic point loss at most 42 campuses.

---

## Step 10 — Known failure modes and fixes

| Symptom | Cause | Fix |
|---|---|---|
| Crash or wrong output on `INT_MIN` | Negating an `int` at its minimum value | Widen to `long` before negating (Step 4) |
| Return value off by a small amount | A `write` call somewhere isn't counted | Every single `write` must feed the running `count` |
| Segfault on `%s` with NULL | Dereferencing before the NULL check | Check `if (!s)` before the `while (s[i])` loop |
| `%p` doesn't match real `printf` | Wrong nil-handling convention | Reread your subject's exact wording — this varies by campus |
| Norminette fails after Step 7 | Function still over 25 lines or too many params | Split further; a helper returning `int` is cheap, use more of them |

---

## Step 11 — Bonus flags (if your subject has them)

Add in this order — each is strictly harder than the last:

1. `-` — left justify
2. `0` — zero padding
3. `.` — precision
4. `#` — alternate form (`0x` prefix stays even for value 0, etc.)
5. `+` / ` ` — force sign / space for positive

```c
typedef struct s_flags
{
	int	minus;
	int	zero;
	int	width;
	int	precision;
	int	hash;
	int	plus;
	int	space;
}	t_flags;
```

Parse flags *before* you touch the conversion character — read all flag characters, then width digits, then a `.` plus precision digits, and only then land on `c/s/d/i/u/x/X/p`. Keep flag-parsing in its own function; don't fold it into `dispatch` or you'll blow past 25 lines immediately.

Build and test flags **one at a time against real `printf`** using the harness from Step 9 — width and precision interact in non-obvious ways (e.g. precision on `%d` zero-pads the number itself, not the field, and `0` flag is ignored when `-` is also present). Don't trust your intuition here; trust the comparison test.

---

## Step 12 — Submission checklist

- [ ] All mandatory conversions (`%c %s %d %i %u %x %X %p %%`) tested against real `printf`
- [ ] `INT_MIN`, `NULL`, `0`, empty format string all tested explicitly
- [ ] Return value exactly matches `printf`'s in every test case
- [ ] `valgrind` clean if you allocate anywhere
- [ ] Every function ≤ 25 lines, norminette clean
- [ ] Makefile: `all`, `clean`, `fclean`, `re` all work, no relink on repeat `make`
- [ ] Header declares every prototype you actually use
- [ ] `.gitignore` excludes `*.o` and the `.a`

You now have a working, norm-compliant `ft_printf` you built and tested one conversion at a time — which also means you can actually explain every line of it in your evaluation. That's the real goal here, not just a passing binary.
