SRCDIR= src
OBJDIR= obj
CC =gcc -Wall
CFLAGS= -I$(SRCDIR) -g
LDFLAGS= -lwiringPi -lpthread
EXEC= jandroid
SRC= $(wildcard $(SRCDIR)/*.c)
OBJ= $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -o $@ -c $^ $(CFLAGS)

.PHONY: clean mrproper

clean:
		@rm -rf $(OBJ)

mrproper: clean
		@rm -rf $(EXEC)
