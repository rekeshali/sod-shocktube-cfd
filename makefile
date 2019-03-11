CC = g++
SRCDIR = src
OBJDIR = build
INCDIR = include
BINDIR = bin

SRCEXT  = cpp
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TARGET  = $(BINDIR)/flow

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

$(OBJDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $@ $< -I$(INCDIR)

run: $(TARGET)
	./$(TARGET)

clean: 
	@echo " Cleaning..."
	rm -rf $(OBJDIR) $(TARGET)
