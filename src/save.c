#include "../include/connectfour.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

#ifdef BYTE_OFFSET
#undef BYTE_OFFSET
#endif
#define BYTE_OFFSET 19

bfield_t bfield[BF_SIZE_X][BF_SIZE_Y];

void save_game(object_t *sender, const char *path) {
	if (!sender || !path) return;

	time_t t = time(NULL);
	struct tm local = *localtime(&t);
	char buff[64];

	int n = sprintf(buff, "%d-%d-%d %d:%d:%d\n%d %d %d %d %d %d\n", \
		local.tm_year+1900, local.tm_mon+1, local.tm_mday, \
		local.tm_hour, local.tm_min, local.tm_sec, \
		BF_SIZE_X, BF_SIZE_Y, NUM_PLAYERS, \
		sender->player, sender->nmoves, sender->winner);

	buff[n] = '\0';

	size_t sz = sizeof(bfield), idx = 0;
	char *data = malloc(sz);
	if (!data) return;

	memcpy(data, bfield, sz);
	for (idx = 0; idx < sz; idx++) data[idx] += BYTE_OFFSET;
	
	int fd = open(path, O_RDWR | O_CREAT, S_IRWXU);
	ssize_t ret;
	
	if ((ret = write(fd, buff, n)) < 0)
		printf("Can't save header...\n");
	if ((ret = write(fd, data, sz)) < 0)
		printf("Can't save data...\n");

	free(data);
	close(fd);
}