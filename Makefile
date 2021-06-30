CC = gcc
CFLAGS = -Wall -g -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LDFLAGS = -ltss2-esys
OBJECTFILES = src/primarykey.o src/secondarykey.o src/encrypt_decrypt.o src/random.o src/egg.o src/main.o
TARGET = build/tpmsecret

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTFILES) $(LDFLAGS)

clean:
	rm -f $(OBJECTFILES) $(TARGET) *~
