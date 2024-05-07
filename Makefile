.PHONY = help compile clean lint sc format
.DEFAULT_GOAL = help

define HELP_LIST_TARGETS
To compile binary:
    $$ make compile
To remove build directory:
    $$ make clean
To run cppcheck linter:
    $$ make lint
To run shellcheck linter:
    $$ make sc
To format C++ code:
    $$ make format
endef

export HELP_LIST_TARGETS

help:
	@echo "$$HELP_LIST_TARGETS"

compile:
	@cmake -S Eloquence -B build
	@make --jobs=12 --directory=build

clean:
	@rm -rfv build

lint:
	@cppcheck Eloquence --enable=all

sc:
	@shellcheck --shell=bash run

format:
	@clang-format -i --verbose --style=file Eloquence/src/*.cpp Eloquence/include/*.hpp
