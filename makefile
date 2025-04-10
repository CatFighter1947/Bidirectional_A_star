# Компилятор
CC = gcc

# Флаги компилятора
CFLAGS = -Wall -g

# Целевой исполняемый файл
TARGET = out

# Исходные файлы
SOURCES = File_Out.c

# Объектные файлы
OBJECTS = $(SOURCES:.c=.o)

# Правила
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)



