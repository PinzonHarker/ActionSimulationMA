SHELL:=/bin/zsh
TARGET= integration
CXX = g++ -g

all: $(TARGET).x
	./$(TARGET).x

$(TARGET).x: $(TARGET).cpp
	$(CXX) $$(pkg-config --cflags gsl) $(TARGET).cpp -o $(TARGET).x $$(pkg-config --libs gsl)

#$(TARGET).x: $(TARGET).c
#	gcc $$(pkg-config --cflags gsl) $(TARGET).cpp -o $(TARGET).x $$(pkg-config --libs gsl)

clean: 
	rm -rf *.x