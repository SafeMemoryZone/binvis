#ifndef RENDER_H
#define RENDER_H
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void VisulizeFile(FILE *file, int win_width, int win_height, uint8_t alpha_step,
                  bool use_max, char *image_path);
#endif
