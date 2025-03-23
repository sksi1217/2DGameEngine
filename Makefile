# Определение имени исполняемого файла
TARGET = build/myapp

# Исходные файлы вашего проекта
SRCS = main.cpp \
	src/core/Game.cpp \
	src/core/GameWindow.cpp \
	src/core/GameObject.cpp \
	src/core/GameManager.cpp \
	src/openGL/OpenGLContex.cpp \
	src/graphics/Texture2D.cpp \
	src/graphics/ShaderProgram.cpp \
	src/utils/ShaderLoader.cpp \
	src/utils/TextureLoader.cpp

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -std=c++17 -I. -Iinclude

# Проверка операционной системы
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	# Для Linux: добавляем библиотеки OpenGL, X11 и GLEW
	LDFLAGS += -lGL -lX11 -lGLEW
	SRCS += src/platform/linux/X11Window.cpp
else ifeq ($(OS), Windows_NT)
	# Для Windows: добавляем флаг -mwindows и библиотеку OpenGL
	LDFLAGS += -mwindows -lopengl32 -lgdi32
	SRCS += src/platform/windows/Win32Window.cpp
else
	$(error Unsupported platform)
endif

# Объектные файлы будут помещены в одну папку
OBJS_DIR = build/objs
OBJS = $(patsubst %.cpp,$(OBJS_DIR)/%.o,$(SRCS))

# Цель по умолчанию
all: $(TARGET)

# Создание каталога build, если он не существует
$(TARGET): $(OBJS)
	@mkdir -p build
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Правило для компиляции .cpp файлов в .o файлы
$(OBJS): $(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки временных файлов
clean:
	rm -rf build

.PHONY: all clean

# sed -i 's/^\s\+/\t/' Makefile
