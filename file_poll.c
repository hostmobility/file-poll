/**
 *
 * file-poll - program that waits for poll events on a file
 *
 * Copyright (C) 2017 Host Mobility AB 
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdio.h>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

int main (int argc, char *argv[])
{
	char* path;
	char buf[10];
	ssize_t bytes;

	struct pollfd fds;

	if (argc != 2)
	{
		printf("The file descriptor to listen is needed as first (and only) parameter\n");
		return 1;
	}

	path = argv[1];

	fds.fd = open (path, O_RDONLY);

	if (!fds.fd)
	{
		printf("Unable to open file descriptor\n");
		return 1;
	}

	fds.events = POLLERR | POLLPRI;
	fds.revents = 0;
	printf ("listening for events in:%s\n", path);

	while (1)
	{
		printf("-- poll start -- \n");
		if (poll (&fds, 1, -1) > 0)
		{
			lseek(fds.fd, 0, SEEK_SET);
			bytes = read (fds.fd, buf, 10);
			if (bytes < 0)
				printf("Error on read: %s", strerror(errno));

			printf("%s : %s\n", path, buf);

			if (fds.revents & POLLPRI)
				printf("POLLPRI event recieved\n");

			if (fds.revents & POLLERR)
				printf("POLLERR event recieved\n");

			if (fds.revents & POLLIN)
				printf("POLLIN event recieved\n");

			if (fds.revents & POLLOUT)
				printf("POLLOUT event recieved\n");

			if (fds.revents & POLLHUP)
				printf("POLLHUP event recieved\n");

			if (fds.revents & POLLNVAL)
				printf("POLLNVAL event recieved\n");
		}
		printf("-- poll end -- \n\n");
	}

	printf ("Finish\n");
	return 0;
}
