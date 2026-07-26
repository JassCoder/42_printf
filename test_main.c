#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	ft_len;
	int	real_len;

	printf("\n=== TESTING FT_PRINTF ===\n\n");

	// 1. Basic string
	printf("1. Basic string:\n");
	ft_len = ft_printf("Hello, World!\n");
	real_len = printf("Hello, World!\n");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 2. Character
	printf("2. Character:\n");
	ft_len = ft_printf("Char: %c\n", 'A');
	real_len = printf("Char: %c\n", 'A');
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 3. String
	printf("3. String:\n");
	ft_len = ft_printf("String: %s\n", "Hello 42");
	real_len = printf("String: %s\n", "Hello 42");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 4. NULL string
	printf("4. NULL string:\n");
	ft_len = ft_printf("NULL: %s\n", (char *)NULL);
	real_len = printf("NULL: %s\n", (char *)NULL);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 5. Integer positive
	printf("5. Integer positive:\n");
	ft_len = ft_printf("Int: %d\n", 42);
	real_len = printf("Int: %d\n", 42);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 6. Integer negative
	printf("6. Integer negative:\n");
	ft_len = ft_printf("Int: %d\n", -42);
	real_len = printf("Int: %d\n", -42);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 7. Integer MAX
	printf("7. INT_MAX:\n");
	ft_len = ft_printf("Max: %d\n", INT_MAX);
	real_len = printf("Max: %d\n", INT_MAX);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 8. Integer MIN
	printf("8. INT_MIN:\n");
	ft_len = ft_printf("Min: %d\n", INT_MIN);
	real_len = printf("Min: %d\n", INT_MIN);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 9. Unsigned
	printf("9. Unsigned:\n");
	ft_len = ft_printf("Unsigned: %u\n", 4294967295u);
	real_len = printf("Unsigned: %u\n", 4294967295u);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 10. Hex lowercase
	printf("10. Hex lowercase:\n");
	ft_len = ft_printf("Hex: %x\n", 255);
	real_len = printf("Hex: %x\n", 255);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 11. Hex uppercase
	printf("11. Hex uppercase:\n");
	ft_len = ft_printf("HEX: %X\n", 255);
	real_len = printf("HEX: %X\n", 255);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 12. Pointer
	printf("12. Pointer:\n");
	int	x = 42;
	ft_len = ft_printf("Pointer: %p\n", &x);
	real_len = printf("Pointer: %p\n", &x);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 13. NULL pointer
	printf("13. NULL pointer:\n");
	ft_len = ft_printf("NULL ptr: %p\n", (void *)NULL);
	real_len = printf("NULL ptr: %p\n", (void *)NULL);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 14. Percent
	printf("14. Percent:\n");
	ft_len = ft_printf("Percent: %%\n");
	real_len = printf("Percent: %%\n");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 15. Multiple conversions
	printf("15. Multiple conversions:\n");
	ft_len = ft_printf("Mix: %c %s %d %x %%\n", 'A', "test", 42, 255);
	real_len = printf("Mix: %c %s %d %x %%\n", 'A', "test", 42, 255);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 16. No arguments
	printf("16. No arguments:\n");
	ft_len = ft_printf("Just text\n");
	real_len = printf("Just text\n");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 17. Empty string
	printf("17. Empty string:\n");
	ft_len = ft_printf("");
	real_len = printf("");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 18. Multiple percent
	printf("18. Multiple percent:\n");
	ft_len = ft_printf("Percent: %% %% %%\n");
	real_len = printf("Percent: %% %% %%\n");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 19. Percent at end
	printf("19. Percent at end:\n");
	ft_len = ft_printf("End with %%");
	real_len = printf("End with %%");
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	// 20. Mixed with all specifiers
	printf("20. All specifiers together:\n");
	ft_len = ft_printf("All: %c %s %p %d %u %x %X %%\n", 
	                   'Z', "final", &x, 123, 456, 789, 987);
	real_len = printf("All: %c %s %p %d %u %x %X %%\n", 
	                  'Z', "final", &x, 123, 456, 789, 987);
	printf("ft: %d, real: %d\n\n", ft_len, real_len);

	printf("=== TEST COMPLETE ===\n");
	printf("Check if all return values match!\n");
	
	return (0);
}