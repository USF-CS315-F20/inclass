/* elf_std.h contains only documented and standard values and structures
             Implementation choices are in elf.c 

   Sources:
   http://www.skyfree.org/linux/references/ELF_Format.pdf
   https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
   https://static.docs.arm.com/ihi0044/g/aaelf32.pdf
   https://developer.arm.com/documentation/ihi0045/e/ (ARM build attributes section)
*/

#ifndef _ELFDEFS_H
#define _ELFDEFS_H

// Executable header constants
#define EI_NIDENT 16          // Sizeof ident buf
#define EV_CURRENT 1          // version number
#define EF_ARM_ABI 0x05000000 // EABI v5

// Word width
enum {
    ELFCLASS32 = 1,  // 32 bit words
    ELFCLASS64,      // 64 bit words
};

// Endianness
enum {
    ELFDATA2LSB = 1,  // Little endian, 2's complement
    ELFDATA2MSB,      // Big endian, 2's complement
};

// ELF machine types (e_machine)
enum {
    EM_NONE = 0,   // No machine
    EM_M32,        // AT&T WE 32100
    EM_SPARC,      // Sun SPARC
    EM_386,        // Intel 80386
    EM_68K,        // Motorola 68000
    EM_88K,        // Motorola 88000
    EM_860,        // Intel 80860
    EM_MIPS,       // MIPS RS3000
    EM_ARM = 0x28  // ARM
};

// ELF file types (e_type)
enum {
    ET_NONE = 0,         // No file type
    ET_REL,              // Relocatable file
    ET_EXEC,             // Executable file
    ET_DYN,              // Shared object file
    ET_CORE,             // Core file 
    ET_LOPROC = 0xff00,  // Processor-specific
    ET_HIPROC = 0xffff,  // Processor-specific
};

typedef unsigned int   Elf32_Addr;
typedef unsigned short Elf32_Half;
typedef unsigned int   Elf32_Off;
typedef int            Elf32_Sword;
typedef unsigned int   Elf32_Word;

// Executable header type. One per ELF file.
typedef struct {
    unsigned char e_ident[EI_NIDENT]; 
    Elf32_Half e_type;
    Elf32_Half e_machine;
    Elf32_Word e_version;
    Elf32_Addr e_entry;
    Elf32_Off  e_phoff;
    Elf32_Off  e_shoff;
    Elf32_Word e_flags;
    Elf32_Half e_ehsize;
    Elf32_Half e_phentsize;
    Elf32_Half e_phnum;
    Elf32_Half e_shentsize;
    Elf32_Half e_shnum;
    Elf32_Half e_shstrndx;
} Elf32_Ehdr;

// Section header types
enum {
    SHT_NULL = 0,
    SHT_PROGBITS,
    SHT_SYMTAB,
    SHT_STRTAB,
    SHT_RELA,
    SHT_HASH,
    SHT_DYNAMIC,
    SHT_NOTE,
    SHT_NOBITS,
    SHT_REL,
    SHT_SHLIB,
    SHT_DYNSYM,
    SHT_INIT_ARRAY,
    SHT_FINI_ARRAY,
    SHT_GROUP,
    SHT_SYMTAB_SHNDX,
    SHT_NUM,
    SHT_ARM_ATTRS = 0x70000003,
};

// Section header flags
enum {
    SHF_WRITE = 0x1,
    SHF_ALLOC = 0x2,
    SHF_EXECINSTR = 4,
    SHF_MASKPROC = 0xf0000000,
};

// Section header
typedef struct {
    Elf32_Word sh_name;
    Elf32_Word sh_type;
    Elf32_Word sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    Elf32_Word sh_size;
    Elf32_Word sh_link;
    Elf32_Word sh_info;
    Elf32_Word sh_addralign;
    Elf32_Word sh_entsize;
} Elf32_Shdr;

// ARM Attributes constants. See the Build Attributes reference above
#define AA_VERSION 0x41
#define AA_SIZE 0x16
#define AA_VENDOR "aeabi"
#define AA_TAG_FILE 1
#define AA_FILE_BYTE_SIZE 0x0b
#define AA_TAG_CPU 6
#define AA_CPU_V4T 2
#define AA_TAG_ARM_ISA 8
#define AA_ARM_ISA 1
#define AA_TAG_THUMB_ISA 9
#define AA_THUMB_ISA 1

// ARM attributes. I tried to make this a real struct but the 
// compiler's alignment rules were in the way.
typedef unsigned char elf_arm_attributes[AA_SIZE];

// Symbol binding
enum {
    STB_LOCAL = 0,
    STB_GLOBAL,
    STB_WEAK,
    STB_LOPROC = 13,
    STB_HIPROC = 15,
};

// Symbol type
enum {
    STT_NOTYPE = 0,
    STT_OBJECT,
    STT_FUNC,
    STT_SECTION,
    STT_FILE,
    STT_LOPROC = 13,
    STT_HIPROC = 15,
};

// Macros for symbol st_info
#define ELF32_ST_BIND(i) ((i)>>4)
#define ELF32_ST_TYPE(i) ((i)&0xf)
#define ELF32_ST_INFO(b,t) (((b)<<4)+((t)&0xf))

// Symbol in the symbol table
typedef struct {
    Elf32_Word    st_name;
    Elf32_Addr    st_value;
    Elf32_Word    st_size;
    unsigned char st_info;
    unsigned char st_other;
    Elf32_Half    st_shndx;
} Elf32_Sym;

// This appears to be the only R_TYPE code we need (of a long list)
#define R_ARM_V4BX 40

// High 28 bits of BX to identify needed relocations
#define ARM_BX_28 0xe12fff1

// Macros for r_info
#define ELF32_R_SYM(i) ((i)>>8)
#define ELF32_R_TYPE(i) ((unsigned char)(i))
#define ELF32_R_INFO(s,t) (((s)<<8)+(unsigned char)(t))

// Relocation
typedef struct {
    Elf32_Addr r_offset;
    Elf32_Word r_info;
} Elf32_Rel;

#endif // _ELFDEFS_H
