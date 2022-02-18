#include <dirent.h>

int	main(void)
{
	struct dirent	*entry;
	DIR		*dir;

	dir = opendir(".");
	while ((entry = readdir(dir)))
	{
		printf("%s\n", entry->d_name);
	}
}
