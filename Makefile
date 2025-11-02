.PHONY: all clean

ENV = source ./.env
CMAKE = cmake -B build -G Ninja
NINJA = ninja -C build
IDE = ln -sf build/compile_commands.json ./

all:
	@bash -c '$(CMAKE) && $(NINJA) && $(IDE)'

run: 
	@bash -c '$(ENV) && ./build/src/trade'

clean:
	@rm -rf build/
