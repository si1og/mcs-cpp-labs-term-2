CC = g++
CFLAGS = -g -I$(SRC_DIR)
LDFLAGS = 

SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests

OBJECTS = $(BUILD_DIR)/my-string.o $(BUILD_DIR)/matrix.o \
					$(BUILD_DIR)/short_array.o

# TESTS = \
#   $(BUILD_DIR)/test_rect_basic_methods.out \
#   $(BUILD_DIR)/test_rect_properties.out \
#   $(BUILD_DIR)/test_rect_operations.out \
#   $(BUILD_DIR)/test_bounding_rect.out

# Цели по умолчанию
.PHONY: all debug leaks clean test gdb

all: debug

debug: $(BUILD_DIR)/debug.out

gdb: debug
	gdb $(BUILD_DIR)/debug.out

# Проверка утечек через Valgrind
leaks: $(BUILD_DIR)/leaks.out
	valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all $(BUILD_DIR)/leaks.out

# Основная отладочная сборка
$(BUILD_DIR)/debug.out: $(OBJECTS) $(SRC_DIR)/lab3.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/lab3.cpp $(OBJECTS) $(LDFLAGS)

$(BUILD_DIR)/rect-functions.o: $(SRC_DIR)/rect-functions.cpp $(SRC_DIR)/rect-functions.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Сборка для проверки утечек
$(BUILD_DIR)/leaks.out: $(OBJECTS) $(SRC_DIR)/lab3.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $(SRC_DIR)/lab3.cpp $(OBJECTS) $(LDFLAGS)

# Сборка тестов
# test: $(TESTS)
# 	@for test in $(TESTS); do echo Running $$test...; $$test; done

# Каждая сборка теста
$(BUILD_DIR)/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp $(SRC_DIR)/rect.cpp
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/test_rect_properties.out: tests/test_rect_properties.cpp $(SRC_DIR)/rect.cpp
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/test_rect_operations.out: tests/test_rect_operations.cpp $(SRC_DIR)/rect.cpp
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/test_bounding_rect.out: tests/test_bounding_rect.cpp $(SRC_DIR)/rect.cpp $(SRC_DIR)/rect-functions.cpp
	$(CC) $(CFLAGS) -o $@ $^

# Правило для объектных файлов
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.hpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Создание директории сборки
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Очистка
clean:
	rm -rf $(BUILD_DIR)