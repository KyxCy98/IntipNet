cxx = clang++
cxxflag = -Wall -Wextra -std=c++17 -Iinclude

src = lib/main/main.cpp lib/main/module/banner.cpp lib/main/module/logger.cpp lib/main/module/message.cpp
out = build/intipnet

all: $(out)

$(out): $(src)
	@echo "Make directory 'debug' for output debug script"
	mkdir debug
	@echo "build intipnet resource -> $(src)"
	$(cxx) $(src) -o $(out) $(cxxflag)

clean:
	@echo "removing binary $(out)"
	rm -f $(out)
	@echo "removing debug output"
	rm -fr debug

run:
	./$(out)
