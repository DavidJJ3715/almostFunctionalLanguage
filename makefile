flags = -Wall -Wextra
dependencies = compiler.cpp sampleCode.afl
fileToCompile = sampleCode.afl

run: $(dependencies)
	g++ $(flags) compiler.cpp -o executable
	./executable $(fileToCompile)