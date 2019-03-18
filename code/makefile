CC = g++
SRCDIR = src
OBJDIR = build
INCDIR = include
BINDIR = bin

SRCEXT  = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TARGET  = $(BINDIR)/sod

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< -I$(INCDIR)

run: $(TARGET)
	./$(TARGET) HLL 0.0025 0.5 HLL-dx0.0025-cfl0.5.sod

clean: 
	@echo "Cleaning..."
	rm -rf $(OBJDIR) $(TARGET)
