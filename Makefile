project_name = pitaya

DUNE = opam exec -- dune
opam_file = $(project_name).opam

.PHONY: help
help:
	@echo "";
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: build
build:
	$(DUNE) build @all

.PHONY: build-prod
build-prod:
	$(DUNE) build --profile=prod @all

.PHONY: build-dev
dev:
	$(DUNE) build -w @all

.PHONY: clean
clean: ## Clean artifacts
	$(DUNE) clean

.PHONY: test
test: ## Run the unit tests
	$(DUNE) build @runtest
	yarn jest

.PHONY: test-watch
test-watch: ## Run the unit tests in watch mode
	$(DUNE) build @runtest -w

.PHONY: format
format: 
	$(DUNE) build @fmt --auto-promote

.PHONY: format-check
format-check:
	$(DUNE) build @fmt

.PHONY: pin
pin:
	opam install dune.3.10.0
	opam pin add reason-react-ppx.dev "https://github.com/reasonml/reason-react.git#0ccff71796b60d6c32ab6cf01e31beccca4698b9" -y
	opam pin add server-reason-react "https://github.com/ml-in-barcelona/server-reason-react.git#main" -y
	opam pin add reason-react.dev "https://github.com/reasonml/reason-react.git#3971e42df555f3c8fb5b4eab94a26e8e51d79f02" -y
	opam pin add melange-webapi.dev "git+https://github.com/melange-community/melange-webapi.git#master" -y
	opam pin add universal-portal.dev "https://github.com/pedrobslisboa/universal-portal.git#bdb36e8100c038613c9a8a0c3dbb08d4a2d1281d" -y
	opam pin add melange-json.dev "https://github.com/melange-community/melange-json.git#c3c70a61af5914aed6d3773afcc82773cb9d6041" -y

.PHONY: create-switch
create-switch:
	opam switch create . 5.1.0 --deps-only --with-test -y

.PHONY: install
install: create-switch pin

.PHONY: init
init: install

.PHONY: demo
demo: build
	yarn webpack
	$(DUNE) exec src/server/server.exe