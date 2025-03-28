# Определение имени исполняемого файла
TARGET = build/myapp

# Исходные файлы вашего проекта
SRCS = main.cpp \
	src/core/Game.cpp \
	src/core/GameWindow.cpp \
	src/core/GameObject.cpp \
	src/core/Camera.cpp \
	src/core/ImGuiManager.cpp \
	src/openGL/OpenGLContext.cpp \
	src/openGL/Framebuffer.cpp \
	src/graphics/Texture2D.cpp \
	src/graphics/ScreenQuadRenderer.cpp \
	src/graphics/Shader.cpp \
	src/graphics/Render.cpp \
	src/utils/ShaderLoader.cpp \
	src/utils/TextureLoader.cpp \
	imgui/imgui.cpp \
	imgui/imgui_demo.cpp \
	imgui/imgui_draw.cpp \
	imgui/imgui_tables.cpp \
	imgui/imgui_widgets.cpp \
	imgui/backends/imgui_impl_opengl3.cpp \
	imgui/backends/imgui_impl_glfw.cpp \

# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -Wall -std=c++17 -I. -Iinclude -Iimgui -g

# Проверка операционной системы
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	# Для Linux: добавляем библиотеки OpenGL, GLFW и GLEW
	LDFLAGS += -lGL -lglfw -lGLEW
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
