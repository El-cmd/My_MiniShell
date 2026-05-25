# AGENT.md

## Project Snapshot
- Repository: `El-cmd/My_MiniShell`
- Default branch: `main`
- Detected stack: C
- Notable root entries: `builtins/`, `error/`, `exec/`, `free/`, `ft_split_special/`, `init/`, `libft/`, `meta/`, `.gitignore`, `ignoreLibError`, `main.c`, `Makefile`, `minishell.h`, `README.md`
- Source mix: .c:82, .h:2, makefile:2, ignoreliberror:1, .gitignore:1, .md:1

## Working Guidelines
- Keep changes scoped to the requested behavior and follow the style already present in the touched files.
- Check `README.md`, `Makefile`, package scripts, and Docker files before introducing new commands or tooling.
- Preserve the existing C/C++ layout and Makefile conventions; avoid committing binaries, object files, or local test outputs.
- Do not commit local secrets, `.env` files, generated dependency folders, build artifacts, or editor metadata.

## Setup
- `No explicit dependency install command is defined in the repository.`

## Run
- `No canonical run command is defined; inspect README/Makefile/package scripts first.`

## Validate
- `make`
- `make re`
- `make clean`
- `make fclean`

## Makefile Targets Detected
- `my_all`, `clean`, `fclean`, `re`
