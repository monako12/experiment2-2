CC	= gcc
CFLAGS	= -Wall -O2
OBJS	= num.o sigmoid.o set_problem.o
LIBS	= -lm
PROG    = nn_num

ALL: $(PROG)
$(PROG):$(OBJS)
	$(CC) $(FLAGS) -o $@ $(OBJS)  $(LIBS)
$(OBJS): parameter.h
clean:
	rm -f $(OBJS) *~ a.out $(PROG)
