NAME        = test
CXX         = g++
CXXFLAGS    = -Wall -Wextra -pedantic -std=c++14 -g
LINKER_INPUT = -L ~/.brew/lib -framework OpenGL -lSDL2 -lglew -lSDL2_image

OBJ_DIR    = obj/
SRC_DIR    = src/

INC_DIRS    = $(SRC_DIR) ~/.brew/include res/extern 

FILES  = main Shader IndexBuffer VertexBuffer VertexBufferLayout VertexArray Texture Renderer imgui imgui_draw imgui_impl_sdl_gl3
TESTS = Test3DBox Test3DBox36 Test3DBoxMany TestClearColor

OBJ        = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES) $(addprefix Tests/, $(TESTS) ) ) )
HEADERS    = $(addsuffix .hpp, $(FILES))

INCLUDES    = $(addprefix -I , $(INC_DIRS))

VPATH += src/

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ_DIR)/Tests $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LINKER_INPUT)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/Tests:
	@mkdir -p $(OBJ_DIR)/Tests

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(COMPILE.cpp) $(OUTPUT_OPTION) $< $(INCLUDES)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
