.PHONY: all
all: build examples

.PHONY: build
build:
	dune build @all

.PHONY: examples
examples:
	dune exec ./bin/main.exe examples/test.json

.PHONY: watch
watch:
	dune build @check --watch

.PHONY: doc
doc:
	dune build @doc

.PHONY: format
format:
	dune build @fmt --auto-promote

.PHONY: clean
clean:
	dune clean

.PHONY: test
test:
	dune runtest
