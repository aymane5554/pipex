# pipex

`pipex` is a 42 project that reproduces Unix piping behavior by chaining commands
through pipes and handling file redirection.

## Features

- Execute multiple commands in a pipeline.
- Redirect input from a file and output to a file.
- Support `here_doc` mode with a limiter.
- Resolve commands using `PATH`.

## Build

From the project root:

```bash
make
```

This builds the executable:

```bash
./pipex
```

## Usage

### Standard mode

```bash
./pipex infile "cmd1" "cmd2" ... "cmdn" outfile
```

Equivalent shell behavior:

```bash
< infile cmd1 | cmd2 | ... | cmdn > outfile
```

### here_doc mode

```bash
./pipex here_doc LIMITER "cmd1" "cmd2" ... "cmdn" outfile
```

Equivalent shell behavior:

```bash
cmd1 | cmd2 | ... | cmdn >> outfile
```

In this mode, input is read from standard input until `LIMITER` is reached,
and output is appended to `outfile`.

## Examples

```bash
./pipex input.txt "grep hello" "wc -l" output.txt
```

```bash
./pipex here_doc EOF "cat" "wc -c" output.txt
```

## Notes

- Use quotes for commands that include arguments.
- Make sure input files exist in standard mode.
- Ensure commands are available in your environment `PATH`.
