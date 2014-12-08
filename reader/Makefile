OUTFILE = reader
CFLAGS = -lm
SOURCES = reader.c pb_decode.c readings.pb.c rs485_message.pb.c
GCC = gcc
all:
	$(GCC) $(CFLAGS) -o $(OUTFILE) $(SOURCES)
clean:
	rm $(OUTFILE) 

