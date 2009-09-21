#include <stdio.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

static const unsigned int SLEEP_INTERVAL = 92; // in seconds, a minute and a half plus a small offset so we work together with update(8) nicely, which works at a 30-second interval

// wake up a disk
static void wake ( const char* disk )
{
	struct timeval tv;
	char name[1024];
	struct stat buf;
	int fd;
	int rc = stat(disk, &buf);
	if (rc != 0)
		return; // we couldn't stat it: probably unmounted. Ignore.
	if (!(buf.st_mode & 0222))
		return; // the device is probably mounted read-only. TODO: fall back to read
	gettimeofday(&tv, NULL);
	sprintf(name, "%s/.pks_keepalive", disk);
	fd = open(name, O_WRONLY | O_CREAT, 0600);
	if (fd == -1)
		return; // couldn't open file for writing. Ignore.
	write(fd, &tv, sizeof(tv)); // the time is just a random thing to write which always changes
	fsync(fd); // make it immediately write to keep the thing spun up
	close(fd);
	unlink(name);
}

static void yield ()
{
	unsigned int slept = 0;
	while (slept < SLEEP_INTERVAL)
		slept += sleep(SLEEP_INTERVAL - slept); // we unschedule the thing to save CPU
}

int main ( int argc, char** argv )
{
	int i;
	if (argc == 1)
	{
		// print usage
		printf("Usage: %s [disk] [disk]...\n", argv[0]);
		return 1;
	}
	umask(0600);
	while (1)
	{
		for (i = 1; i < argc; i++)
		{
			wake(argv[i]);
		}
		yield();
	}
	return 0;
}
