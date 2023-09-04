#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "main.h"

#define BUFSIZE 1024

/**
 * main - Copies the content of a file to another file.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 *
 * Return: 0 on success, exit with appropriate error codes on failure.
 */
int main(int argc, char **argv)
{
    int fd_from, fd_to, close_status;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFSIZE];

    if (argc != 3)
    {
        dprintf(2, "Usage: %s file_from file_to\n", argv[0]);
        return (97);
    }

    fd_from = open(argv[1], O_RDONLY);
    if (fd_from == -1)
    {
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        return (98);
    }

    fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_to == -1)
    {
        dprintf(2, "Error: Can't write to %s\n", argv[2]);
        close(fd_from);
        return (99);
    }

    while ((bytes_read = read(fd_from, buffer, BUFSIZE)) > 0)
    {
        bytes_written = write(fd_to, buffer, bytes_read);
        if (bytes_written == -1 || bytes_written != bytes_read)
        {
            dprintf(2, "Error: Can't write to %s\n", argv[2]);
            close(fd_from);
            close(fd_to);
            return (99);
        }
    }

    if (bytes_read == -1)
    {
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        close(fd_from);
        close(fd_to);
        return (98);
    }

    close_status = close(fd_from);
    if (close_status == -1)
    {
        dprintf(2, "Error: Can't close fd %d\n", fd_from);
        return (100);
    }

    close_status = close(fd_to);
    if (close_status == -1)
    {
        dprintf(2, "Error: Can't close fd %d\n", fd_to);
        return (100);
    }

    return (0);
}

