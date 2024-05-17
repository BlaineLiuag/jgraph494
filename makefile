CXX = g++
CXXFLAGS = -Wall -std=c++11
BIN = bin


all: $(BIN)/QRGenerator $(BIN)/JGgenerator jgraph

$(BIN):
	mkdir -p $(BIN)

$(BIN)/QRGenerator: $(BIN)/QRGenerator.o $(BIN)/qrcodegen.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN)/QRGenerator.o: QRGen_cpp/QRGenerator.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/qrcodegen.o: QRGen_cpp/qrcodegen.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN)/JGgenerator: $(BIN)/JG_generator.o | $(BIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN)/JG_generator.o: JG_generator.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run-demo:
	sh QR_Create.sh preamble.png < preamble.txt
	sh QR_Create.sh vols.png < vols.txt
	sh QR_Create.sh earth.png < earth.txt
	sh QR_Create.sh party.png < party.txt
	sh QR_Create.sh medium.png < medium.txt

clean:
	rm -f $(BIN)/*.o $(BIN)/QRGenerator $(BIN)/JGgenerator

.PHONY: all clean
