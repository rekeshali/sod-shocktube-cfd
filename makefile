CC = g++
SRCDIR = src
OBJDIR = build
INCDIR = include
BINDIR = bin

SRC = %.cpp
OBJ = %.o
BIN = shocktube

# $(BINDIR)/$(BIN): $(OBJDIR)/$(OBJ):
# 	$(CC) -o $(BINDIR)/$(BIN) 

$(OBJDIR)/$(OBJ): $(SRCDIR)/$(SRC):
	$(CC) -c -o $@ $<


