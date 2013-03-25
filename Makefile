OBJDIR = build
BINDIR = bin
OBJFILES=alcyone.o testmcp.o mcp23008.o
TARGETS=alcyone testmcp rawmcp cylon

OBJS = $(addprefix $(OBJDIR)/,$(OBJFILES))
BINS = $(addprefix $(BINDIR)/,$(TARGETS))

CFLAGS = -Wall -c
LFLAGS = -Wall -lwiringPi

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CFLAGS) -o $@ $<
	
all: $(BINS)

clean:
	rm -r $(BINDIR) $(OBJDIR) *.orig *~
	
$(BINS): | $(BINDIR)

$(BINDIR)/alcyone: $(OBJDIR)/alcyone.o $(OBJDIR)/mcp23008.o
	$(CXX) $(LFLAGS) -o $@ $^

$(BINDIR)/rawmcp: $(OBJDIR)/rawmcp.o
	$(CXX) $(LFLAGS) -o $@ $^

$(BINDIR)/cylon: $(OBJDIR)/cylon.o
	$(CXX) $(LFLAGS) -o $@ $^
	
$(BINDIR)/testmcp: $(OBJDIR)/testmcp.o $(OBJDIR)/mcp23008.o
	$(CXX) $(LFLAGS) -o $@ $^
	
$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)
	
$(BINDIR):
	mkdir $(BINDIR)