// elf.h - Declarations for writing object files

#ifndef _ELF_H
#define _ELF_H

#include <stdbool.h>
#include <stdio.h>
#include "elf_std.h"

#define NUM_SECTIONS 9

/* elf_section represents the body of each section */
typedef struct {
    unsigned char *data;
    unsigned int   logical_len;
    unsigned int   memory_len;
} elf_section;

/* elf_context represents all the information we collect to write the file */
typedef struct {
    Elf32_Ehdr  ehdr;
    elf_section sections[NUM_SECTIONS + 1]; // +1 for globals. See append_symbols()
    Elf32_Shdr  shdrs[NUM_SECTIONS];
} elf_context;

/* elf_init() does initial setup of the context */
bool elf_init(elf_context *elf);

/* elf_add_instr() adds one machine code instruction to the text section */
bool elf_add_instr(elf_context *elf, unsigned int instr);

/* elf_add_symbol() adds one human-readable name to the symbol table
   Binding:
     STB_LOCAL for local labels
     STB_GLOBAL for .global functions you want the linker to resolve
*/
bool elf_add_symbol(elf_context *elf, char *name, int offset, int binding);

/* elf_write_file() writes the ELF headers and data to the file */
bool elf_write_file(elf_context *elf, FILE *f);

#endif /* _ELF_H */
