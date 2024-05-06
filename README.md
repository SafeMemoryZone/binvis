# binvis

Binary visualiser written in C using RayLib.

## Usage

```console
$ ./binvis [-a <alpha>] [--m] [-w <window width>] [-h <window height>] -f <file>
```

- `-a` specifies the alpha step (greater alpha, brighter pixels - 255 is max)
- `--m` specifies to use max mode (the most referenced pixel will be the brightest) 
- `-w` specifies the window width
- `-h` specifies the window height
- `-f` specifies the path to the file to be visualised (required)

## Keybidings

- `<ESC>` to close the window
- `<F1>` to take screenshot and save it to `screenshot.png`

## Quick start

1. Create a build directory

```console
$ mkdir build
```

2. Compile the project

```console
$ cmake -B build -S .
$ cmake --build build
```

3. Run the project

```console
$ ./build/src/binvis -f <file>
```
