cxx = clang++
cxxflag = -Wall -Wextra -std=c++17

src = lib/main/main.cpp lib/main/module/banner.cpp lib/main/module/logger.cpp
out = build/intipnet

all: $(out)

$(out): $(src)
	@echo "build intipnet resource -> $(src)"
	$(cxx) $(src) -o $(out)

clean:
	@echo "removing binary $(out)"
	rm -f $(out)

run:
	./$(out)
