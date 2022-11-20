.PHONY: build run clean

init:
	@echo "no target selected"

build:
	g++ -o program.out Source.cpp

run:
	./program.out

clean:
	rm analysis_*.txt analysis_csv.csv
