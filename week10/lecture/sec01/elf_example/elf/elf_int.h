// elf_int.h contains internal declarations for writing ELF files
//           elf.h is the public file

#ifndef _ELF_INT_H
#define _ELF_INT_H

#include <stdbool.h>
#include "elf.h"

// Section indexes 
enum {
    SEC_NULL = 0,
    SEC_TEXT,
    SEC_REL_TEXT,
    SEC_DATA,
    SEC_BSS,
    SEC_ARM_ATTRS,
    SEC_SYMTAB,
    SEC_STRTAB,
    SEC_SHSTRTAB,
    SEC_GSYMTAB, // This is beyond NUM_HEADERS. See append_symbols for the reason
};

// Some functions which could/should be static, but need to share across files
bool grow_and_add(elf_section *sec, void *src, size_t src_len);
bool add_symbol(elf_section *sec, Elf32_Sym *sym);
void finalize_sections(elf_context *elf);
void finalize_shdrs(elf_context *elf);

#endif
