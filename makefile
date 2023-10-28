CC = g++
SUBDIRS    = src
OBJDIR     = obj
BINDIR     = bin
OBJECTS    = $(SOURCES:.cpp:=.o)
EXECUTABLE = trading_platform
CPPFLAGS   = -O3 -std=c++17 -Wall -Werror
LIBS       = -lpthread
#-lstdc++fs

MOVED_OBJECTS =  $(addprefix $(OBJDIR)/, $(OBJECTS))

.PHONY : all clean

all: $(OBJECTS)
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)
	$(foreach subdir, $(SUBDIRS), cd $(subdir); make all; cd ../;)
	$(CC) $(OBJDIR)/* $(LIBS) -o $(EXECUTABLE)
	mv $(EXECUTABLE) $(BINDIR)

clean:
	rm -rf $(BINDIR) $(OBJDIR)
	$(foreach subdir,$(SUBDIRS), cd $(subdir); make clean; cd ../;)