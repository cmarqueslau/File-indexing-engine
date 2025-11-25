# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Isrc

# Pastas
SRCDIR = src
OBJDIR = output

# Procura recursivamente todos .cpp dentro de src/
SRCS = $(shell find $(SRCDIR) -name '*.cpp')

# Converte src/xxx.cpp → output/xxx.o
OBJS = $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# Executável final
TARGET = $(OBJDIR)/main

# Regra padrão
all: $(TARGET)

# Como gerar o executável
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Como gerar cada .o automaticamente
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf $(OBJDIR)
