cc = clang++
linker = clang++
cc_flags = -std=c++20 -c -g -Wall -I$(includedir)/ -Ofast
linker_flags = -g
srcdir = src
includedir = include
builddir = build
libdir = lib
src = $(wildcard $(srcdir)/*.cpp)
inc = $(wildcard $(includedir)/*.hpp) $(wildcard $(includedir)/*.h)
obj = $(subst $(srcdir),$(builddir),$(src:.cpp=.o))
lib = $(wildcard $(libdir)/*.o)

all: $(obj) $(inc) makefile

test: $(builddir)/exe makefile

$(builddir)/exe: $(obj)
	@echo "Now linking"
	@$(linker) $(linker_flags) -o $(builddir)/exe $(builddir)/*.o $(lib)

$(builddir)/%.o: $(srcdir)/%.cpp $(inc)
	@echo "Now compiling $<"
	@$(cc) $(cc_flags) $< -o $@

clean:
	@echo Clearing build/...
	@rm -r build/*