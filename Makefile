.PHONY: all clean

all:
	cmake -B build -G Ninja
	$(MAKE) build

build:
	ninja -C build
	ln -sf build/compile_commands.json ./

clean:
	rm -rf build/

fast:
	ninja -C build
