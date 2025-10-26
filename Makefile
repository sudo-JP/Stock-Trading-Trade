.PHONY: all clean

ENV = source ./.env
CMAKE = cmake -B build -G Ninja
NINJA = ninja -C build
IDE = ln -sf build/compile_commands.json ./

all:
	@bash -c '$(ENV) && $(CMAKE) && $(NINJA) && $(IDE)'


clean:
	@rm -rf build/
