-include colors.mk

# =========================
# Project Configuration
# =========================

NAME :=	npuzzle

# Preprocessor
INCLUDES :=	-Ihdr
DEFINES ?=	
CPPFLAGS ?=	
CPPFLAGS +=	$(INCLUDES) $(DEFINES) -DDEBUG=$(DEBUG)

WARNFLAGS :=	-Wall -Wextra -Werror
# WARNFLAGS +=	-Wno-unused-result
# WARNFLAGS +=	-Wno-unused-variable

# C++ Compiler
CXX ?=		c++
CXXFLAGS ?=	-std=c++11
CXXFLAGS +=	$(WARNFLAGS)

# Dependency generation
#   -MMD    Exclude system headers (C/C++)
#   -MP     Phony targets for removed headers (C/C++)
#   -MF     Output dependency file
#   -MT     Set target name in .d file
DEPFLAGS =		-MMD -MP -MF $(DEP_DIR)$*.d -MT $@

# Linking
LDFLAGS ?=	-Lassets/raylib/src
LDLIBS ?=	-lraylib -lGL -lm -lpthread -ldl -lrt -lX11
# LDLIBS +=	-lft

# =========================
# Build types
# =========================

BUILD ?=	debug
# Release
ifeq ($(BUILD),release)
	CXXFLAGS +=		-O3
	DEBUG ?=		1
# debug
else ifeq ($(BUILD),debug)
	CXXFLAGS +=		-O0 -g3
	DEBUG ?=		4
# Sanitizer (ASan / UBSan)
#
# Debug helpers (ASan symbols)
# addr2line -f -C -e visu-hex <addresses>
#
# Example:
# Direct leak of 24 byte(s) in 1 object(s) allocated from:
#     #0 0x49a3dd  (/sgoinfre/ohengelm/CodamAdvancedProjects/lem_in/visu-hex+0x49a3dd)
#     #1 0x4f3c20  (/sgoinfre/ohengelm/CodamAdvancedProjects/lem_in/visu-hex+0x4f3c20)
# Results in:
# addr2line -f -C -e visu-hex 0x49a3dd 0x4f3c20
else ifeq ($(BUILD),sanitize)
	CXXFLAGS +=		-O0 -g3 \
					-fsanitize=address,undefined \
					-fsanitize-address-use-after-scope \
					-fno-omit-frame-pointer \
					-fno-sanitize-recover=all
	LDFLAGS +=		-fsanitize=address,undefined \
					-fsanitize-address-use-after-scope
	DEBUG ?=		4
else
	$(error Unknown BUILD='$(BUILD)')
endif

# =========================
# Source Definition
# =========================

SRC_DIR :=	src/
OBJ_DIR :=	obj/
DEP_DIR :=	dep/

SRC_MAIN :=	main.cpp

DIR_PARSE :=	$(SRC_DIR)parse/
SRC_PARSE :=	parse.cpp

DIR_CLASS :=	$(SRC_DIR)
SRC_CLASS :=	nPuzzleState.cpp nPuzzleTile.cpp nPuzzleTarget.cpp nPuzzle.cpp

DIR_GRAPHIC :=	$(SRC_DIR)graphics/
SRC_GRAPHIC :=	displayNPuzzle.cpp	Display.cpp	Display.HUD.cpp

SRC_$(NAME) :=	$(SRC_MAIN:%=$(SRC_DIR)%) \
				$(SRC_PARSE:%.cpp=$(DIR_PARSE)%.cpp)\
				$(SRC_CLASS:%.cpp=$(DIR_CLASS)%.cpp)\
				$(SRC_GRAPHIC:%.cpp=$(DIR_GRAPHIC)%.cpp)

OBJ_$(NAME) :=	$(SRC_$(NAME):$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
DEP_$(NAME) :=	$(SRC_$(NAME):$(SRC_DIR)%.cpp=$(DEP_DIR)%.d)

# =========================
# OUTPUT_TYPEs
# =========================

all: $(NAME)

$(NAME): $(OBJ_$(NAME)) assets/raylib/src/libraylib.a
	@printf	"$(CC_LINE)$(C_DORANGE)Linking C++ object files into $(C_ORANGE)%s$(C_DORANGE)...$(C_RESET)\n" "$@"
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@

assets/raylib/src/libraylib.a:
	$(MAKE) -C assets/raylib/src/

# =========================
# Build Rules
# =========================

# Ensure directories exist
$(OBJ_DIR) $(DEP_DIR):
	@printf	"$(CC_LINE)$(C_DCYBL)Creating directory $(C_CYBL)%s$(C_DCYBL)...$(C_RESET)"	"$@"
	@mkdir -p $@

# Compile C++
$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp | $(OBJ_DIR) $(DEP_DIR)
	@mkdir -p $(@D) $(DEP_DIR)/$(*D)
	@printf	"$(CC_LINE)$(C_DCYAN)Compiling $(C_CYAN)%s$(C_DCYAN) to $(C_CYAN)%s$(C_DCYAN)...$(C_RESET)" "$<" "$@"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

# =========================
# Cleaning
# =========================

clean:
	@printf	"$(CC_LINE)$(C_DRED)Removing object and dependency files...$(C_RESET)\n"
	@rm -rf $(OBJ_DIR) $(DEP_DIR)

fclean: clean
	@printf	"$(CC_LINE)$(C_DRED)Removing $(C_RED)%s$(C_DRED)...$(C_RESET)\n"	"$(NAME)"
	@rm -f $(NAME)

re: fclean all

# =========================
# Dependencies
# =========================

-include $(DEP_$(NAME))

# =========================
# Phony
# =========================

.PHONY: all clean fclean re
