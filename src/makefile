SOURCS = platform.cpp \
		 stock.cpp \
		 trader.cpp \
		 order.cpp \
		 stock_factory.cpp \
		 trader_factory.cpp \
		 balance_service.cpp \
		 balance_factory.cpp \
		 trader_service.cpp \
		 hot_wallet.cpp \
		 balance.cpp \
		 main.cpp

OBJDIR        = ../obj
INCLUDEDIR    = ../include
OBJECTS       = $(SOURCS:.cpp=.o)
MOVED_OBJECTS = $(adprefix ./$(OBJDIR)/,$(OBJECTS))
CC = g++
CPPFLAGS = -std=c++17 -c -Wall -Werror -O0 -g

.PHONY: clean all
all: $(OBJECTS) $(SOURCS)
	mkdir -p $(OBJDIR)
	mv *.o $(OBJDIR)

.cpp.o:
	$(CC) -I$(INCLUDEDIR) $(CPPFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)
