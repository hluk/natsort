natsort: main.c
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $<

clean:
	$(RM) natsort

