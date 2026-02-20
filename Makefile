# --- Konfigurasi Warna & Simbol ---
GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
CYAN   := \033[1;36m
RESET  := \033[0m
TICK   := \033[1;32m[✔]\033[0m
INFO   := \033[1;34m[i]\033[0m

# --- Konfigurasi ---
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -fsanitize=address -g
DEPFLAGS  = -MT $@ -MMD -MP -MF $(OBJ_DIR)/$*.d

SRC_DIR  := lib/main
OBJ_DIR  := build/obj
BIN_DIR  := build
TARGET   := $(BIN_DIR)/intipnet

SRCS     := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS     := $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
DEPS     := $(OBJS:.o=.d)

# --- Rules ---

.PHONY: all clean run setup help

all: setup $(TARGET)
	@echo "$(TICK) $(GREEN)Build process completed successfully!$(RESET)"

# Linking
$(TARGET): $(OBJS)
	@echo "$(INFO) $(CYAN)Linking binary:$(RESET) $@"
	@$(CXX) $(OBJS) -o $@ $(CXXFLAGS)
	@echo "$(TICK) $(GREEN)Executable ready at:$(RESET) $(TARGET)"

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@printf "$(BLUE)[CC] Compiling:$(RESET) %-30s $(YELLOW)->$(RESET) %s\n" "$<" "$@"
	@$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

setup:
	@echo "$(INFO) Preparing directories..."
	@mkdir -p $(BIN_DIR) $(OBJ_DIR) debug

clean:
	@clear
	@echo "$(YELLOW)Cleaning up build artifacts...$(RESET)"
	@rm -rf $(BIN_DIR) debug
	@echo "$(TICK) $(GREEN)Cleaned!$(RESET)"

run: all
	@echo "$(BLUE)==========================================$(RESET)"
	@echo "$(CYAN)Launching:$(RESET) $(TARGET)"
	@echo "$(BLUE)==========================================$(RESET)"
	@./$(TARGET)

help:
	@echo "$(BLUE)Available commands:$(RESET)"
	@echo "  make       : Build the project"
	@echo "  make run   : Build and execute"
	@echo "  make clean : Remove build files"