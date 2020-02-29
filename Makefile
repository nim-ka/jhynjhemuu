TARGET = jhynjhemuu

IDIR =include
CXX=g++
CXXFLAGS=-I$(IDIR)

SRCDIR=src

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o
OBJ = $(patsubst %,$(SRCDIR)/%,$(_OBJ))


$(SRCDIR)/%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(SRCDIR)/*.o *~ core $(INCDIR)/*~ $(TARGET)