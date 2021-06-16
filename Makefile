CC = gcc
CFLAGS = -Wall
LDFLAGS = -ltss2-esys
OBJECTFILES = src/primarykey.o src/secondarykey.o src/main.o
TARGET = build/tpmsecret

all: $(TARGET)

$(TARGET): $(OBJECTFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTFILES) $(LDFLAGS)

clean:
	rm -f $(OBJECTFILES) $(TARGET) *~
