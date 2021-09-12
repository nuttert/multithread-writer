export PROJECT_NAME=TestProject
build:
	mkdir -p build
	cd ./build && cmake .. && make
run:
	mkdir -p build
	cd ./build && cmake .. && make && cd .. && ./build/$(PROJECT_NAME)
run-test:
	mkdir -p build
	cd ./build && cmake .. && make && cd .. && ./build/$(PROJECT_NAME)
