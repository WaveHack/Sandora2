TARGET = sandora2

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin
RESDIR = res

# Extensions
SRCEXT = c
OBJEXT = o
DEPEXT = d

# Programs
CC = gcc
RM = rm -f

# Flags
CFLAGS  = -I$(INCDIR) # Include paths
CFLAGS += -D_LINUX # Definitions
CFLAGS += --std=c11 -pedantic -Wall -Wextra # Coding standard and warning options
CFLAGS += `sdl2-config --cflags` # SDL
CFLAGS += -g -D_DEBUG -O0 # Debugging stuff
LDFLAGS = `sdl2-config --libs`

# Do not edit below this line
SOURCES = $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS = $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

all: directories $(TARGET)

remake: clean all

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)

clean:
	@$(RM) -r $(BINDIR)
	@$(RM) -r $(OBJDIR)

-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

$(TARGET): $(OBJECTS)
	$(CC) -o $(BINDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS)

$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<
	@$(CC) -MM $(CFLAGS) $(SRCDIR)/$*.$(SRCEXT) > $(OBJDIR)/$*.$(DEPEXT)
	@cp -f $(OBJDIR)/$*.$(DEPEXT) $(OBJDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(OBJDIR)/$*.$(OBJEXT):|' < $(OBJDIR)/$*.$(DEPEXT).tmp > $(OBJDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(OBJDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(OBJDIR)/$*.$(DEPEXT)
	@rm -f $(OBJDIR)/$*.$(DEPEXT).tmp

.PHONY: all remake directories clean
