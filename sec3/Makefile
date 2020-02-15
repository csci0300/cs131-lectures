PROGS = wild-write1.nosan wild-write1.withsan wild-write2.nosan wild-write2.withsan

all: $(PROGS)

%.nosan: %.c
	$(CC) -o $@ $< -g

%.withsan: %.c
	$(CC) -o $@ $< -g -fsanitize=address
