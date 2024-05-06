#include <raylib.h>
#include <render.h>
#include <stdint.h>
#include <stdlib.h>

void VisulizeFile(FILE *file, int win_width, int win_height, uint8_t alpha_step,
                  bool use_max, char *image_path) {
  SetTraceLogLevel(LOG_ERROR);

  InitWindow(win_width, win_height, "binvis");
  SetTargetFPS(60);

  int rec_width = win_width / 256;
  int rec_height = win_height / 256;

  fseek(file, 0, SEEK_END);
  int len = ftell(file);
  rewind(file);

  uint8_t *buffer = malloc(len);
  fread(buffer, 1, len, file);

  uint16_t *screen = calloc(256 * 256, sizeof(uint16_t));

  if (!screen) {
    fprintf(stderr, "Error: Not enough memory\n");
    free(buffer);
    CloseWindow();
    exit(1);
  }

  uint16_t max = 0;

  for (int i = 0; i < len - 1; i++) {
    uint8_t x = buffer[i];
    uint8_t y = buffer[i + 1];

    uint16_t val = ++screen[y * 255 + x];

    if (val > max)
      max = val;
  }

  free(buffer);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    for (int y = 0; y < 256; y++) {
      for (int x = 0; x < 256; x++) {
        uint16_t count = screen[y * 255 + x];
        Color c = {255, 255, 255};

        if (use_max) {
          float a = (float)count / max * 255 * alpha_step;
          c.a = a > UINT8_MAX ? 255 : a;
        } else {
          c.a = count * alpha_step > 255 ? 255 : count * alpha_step;
        }

        DrawRectangle(x * rec_width, y * rec_height, rec_width, rec_height, c);
      }
    }
    EndDrawing();

    if (IsKeyPressed(KEY_F1))
      TakeScreenshot(image_path);
  }

  free(screen);
  CloseWindow();
}
