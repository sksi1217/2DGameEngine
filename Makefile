# Определение имени исполняемого файла
TARGET = build/myapp

# Исходные файлы вашего проекта
SRCS = main.cpp \
	Core/Game.cpp \
	Core/GameWindow.cpp \
	Platform/X11Window.cpp \
	Platform/Win32Window.cpp \
	Resources/GameManager.cpp \
	OpenGL/OpenGLContex.cpp \
	Utils/TextureLoader.cpp \
	Graphics/Texture2D.cpp \
	Graphics/ShaderProgram.cpp \
	Utils/ShaderLoader.cpp

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -std=c++17 -I. -Iinclude

# Проверка операционной системы
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	# Для Linux: добавляем библиотеки OpenGL и X11
	LDFLAGS += -lGL -lX11 -lGLEW
else ifeq ($(OS), Windows_NT)
	# Для Windows: добавляем флаг -mwindows и библиотеку OpenGL
	LDFLAGS += -mwindows -lopengl32 -lgdi32
else
	$(error Unsupported platform)
endif

# Цель по умолчанию
all: $(TARGET)

# Создание каталога build, если он не существует
$(TARGET): $(OBJS)
	@mkdir -p build
	$(CXX) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Правило для компиляции .cpp файлов в .o файлы
%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки временных файлов
clean:
	rm -rf build $(OBJS)

.PHONY: all clean


# sed -i 's/^\s\+/\t/' Makefile
