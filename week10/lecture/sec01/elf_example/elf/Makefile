LIB = elf.a
OBJS = elf_add.o elf_init.o elf_write.o

CC = gcc
CFLAGS = -c -g
AR = ar
ARFLAGS = rcs

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(LIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -rf $(LIB) $(OBJS)
