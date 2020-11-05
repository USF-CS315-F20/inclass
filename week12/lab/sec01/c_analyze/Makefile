PROG = analyze
OBJS = analyze.o sum_array_s.o fact_s.o substr_s.o quadratic_s.o reverse_s.o

%.o: %.c
	gcc -c -g -o $@ $<

%.o: %.s
	as -g -o $@ $<

$(PROG): $(OBJS)
	gcc -g -o $@ $^
	
clean:
	rm -rf $(PROG) $(OBJS)
