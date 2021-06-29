CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -ltss2-esys
OBJECTFILES = src/primarykey.o src/secondarykey.o src/encrypt_decrypt.o src/random.o src/main.o
TARGET = build/tpmsecret

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTFILES) $(LDFLAGS)

clean:
	rm -f $(OBJECTFILES) $(TARGET) *~
