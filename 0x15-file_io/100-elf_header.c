#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <elf.h>
#include "main.h"

/**
 * display_elf_header - Display information from the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void display_elf_header(Elf64_Ehdr *header)
{
    printf("ELF Header:\n");
    printf("  Magic:   %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
           header->e_ident[0], header->e_ident[1], header->e_ident[2], header->e_ident[3],
           header->e_ident[4], header->e_ident[5], header->e_ident[6], header->e_ident[7],
           header->e_ident[8], header->e_ident[9], header->e_ident[10], header->e_ident[11],
           header->e_ident[12], header->e_ident[13], header->e_ident[14], header->e_ident[15]);

    printf("  Class:                             ");
    switch (header->e_ident[EI_CLASS])
    {
    case ELFCLASS32:
        printf("ELF32\n");
        break;
    case ELFCLASS64:
        printf("ELF64\n");
        break;
    default:
        printf("<unknown: %02x>\n", header->e_ident[EI_CLASS]);
    }

    printf("  Data:                              ");
    switch (header->e_ident[EI_DATA])
    {
    case ELFDATA2LSB:
        printf("2's complement, little endian\n");
        break;
    case ELFDATA2MSB:
        printf("2's complement, big endian\n");
        break;
    default:
        printf("<unknown: %02x>\n", header->e_ident[EI_DATA]);
    }

    printf("  Version:                           %d (current)\n", header->e_ident[EI_VERSION]);
    printf("  OS/ABI:                            ");
    switch (header->e_ident[EI_OSABI])
    {
    case ELFOSABI_SYSV:
        printf("UNIX - System V\n");
        break;
    case ELFOSABI_HPUX:
        printf("UNIX - HP-UX\n");
        break;
    case ELFOSABI_NETBSD:
        printf("UNIX - NetBSD\n");
        break;
    case ELFOSABI_LINUX:
        printf("UNIX - Linux\n");
        break;
    case ELFOSABI_SOLARIS:
        printf("UNIX - Solaris\n");
        break;
    case ELFOSABI_IRIX:
        printf("UNIX - IRIX\n");
        break;
    case ELFOSABI_FREEBSD:
        printf("UNIX - FreeBSD\n");
        break;
    case ELFOSABI_TRU64:
        printf("UNIX - TRU64\n");
        break;
    case ELFOSABI_ARM:
        printf("UNIX - ARM\n");
        break;
    default:
        printf("<unknown: %02x>\n", header->e_ident[EI_OSABI]);
    }

    printf("  ABI Version:                       %d\n", header->e_ident[EI_ABIVERSION]);

    printf("  Type:                              ");
    switch (header->e_type)
    {
    case ET_NONE:
        printf("NONE (No file type)\n");
        break;
    case ET_REL:
        printf("REL (Relocatable file)\n");
        break;
    case ET_EXEC:
        printf("EXEC (Executable file)\n");
        break;
    case ET_DYN:
        printf("DYN (Shared object file)\n");
        break;
    case ET_CORE:
        printf("CORE (Core file)\n");
        break;
    default:
        printf("<unknown: %04x>\n", header->e_type);
    }

    printf("  Entry point address:               0x%lx\n", (unsigned long)header->e_entry);
}

/**
 * main - Display ELF header information.
 * @argc: The number of command-line arguments.
 * @argv: An array of command-line argument strings.
 *
 * Return: 0 on success, exit with appropriate error codes on failure.
 */
int main(int argc, char **argv)
{
    int fd;
    Elf64_Ehdr elf_header;

    if (argc != 2)
    {
        dprintf(2, "Usage: %s elf_filename\n", argv[0]);
        return (98);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        dprintf(2, "Error: Can't open file %s\n", argv[1]);
        return (98);
    }

    if (read(fd, &elf_header, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
    {
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        close(fd);
        return (98);
    }

    if (elf_header.e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header.e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header.e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header.e_ident[EI_MAG3] != ELFMAG3)
    {
        dprintf(2, "Error: Not an ELF file: %s\n", argv[1]);
        close(fd);
        return (98);
    }

    display_elf_header(&elf_header);
    close(fd);

    return (0);
}

