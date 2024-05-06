#include <render.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ParsedArgs {
  char *file_path;
  bool use_max;
  uint8_t alpha_step;
  int win_width;
  int win_height;
};

void PrintUsageError() {
  fprintf(stderr, "Error: Usage: [-a <alpha>] [--m] [-w <window width>] [-h "
                  "<window height>] -f <file>\n");
  exit(1);
}

struct ParsedArgs ParseArgs(int argc, char **argv) {
  if (argc < 3) {
    PrintUsageError();
  }

  struct ParsedArgs args = {0};

  int i = 1;

  while (i < argc) {
    if (strcmp(argv[i], "--m") == 0 || strcmp(argv[i], "--max") == 0) {
      args.use_max = true;
      i++;
      continue;
    }

    if (i == argc - 1)
      PrintUsageError();

    if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "-file") == 0) {
      args.file_path = argv[i + 1];

    } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-alpha") == 0) {
      args.alpha_step = atoi(argv[i + 1]);

    } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "-width") == 0) {
      args.win_width = atoi(argv[i + 1]);

    } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-height") == 0) {
      args.win_height = atoi(argv[i + 1]);

    } else {
      printf("Warning: Ignoring argument '%s'\n", argv[i]);
      i++;
      continue;
    }

    i += 2;
  }

  return args;
}

int main(int argc, char **argv) {
  struct ParsedArgs args = ParseArgs(argc, argv);
  FILE *f = fopen(args.file_path, "rb");

  if (!f) {
    fprintf(stderr, "Unable to open file '%s'\n", argv[2]);
    return 1;
  }

  if (args.win_width > 0 && args.win_width % 256 != 0) {
    fprintf(stderr, "Error: Window width must be a multiple of 256\n");
    exit(1);
  }

  if (args.win_height > 0 && args.win_height % 256 != 0) {
    fprintf(stderr, "Error: Window height must be a multiple of 256\n");
    exit(1);
  }

  VisulizeFile(f, args.win_width > 0 ? args.win_width : 768,
               args.win_height > 0 ? args.win_height : 768,
               args.alpha_step > 0 ? args.alpha_step : 20, args.use_max,
               "screenshot.png");

  fclose(f);

  return 0;
}
