.PHONY: build run clean

init:
	@echo "ERROR: No target selected."
	@echo ""
	@echo "USAGE: make [build, run, clean]"

build:
	g++ -o program.out Source.cpp

run:
	./program.out

clean:
	rm analysis_*.txt analysis_csv.csv
