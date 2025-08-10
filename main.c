#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

typedef struct {
  float X;
  float Y;
} Positions;

// initialized Starting Positions
Positions p = {100, 100};

void DrawCircleV(Vector2 center, float radius, Color color);
Positions CheckAvatarMovement(float X, float Y);

int main() {
  InitWindow(1200, 1000, "Hello Raylib 5.5");
  SetTargetFPS(60);
  Image image = LoadImage("./assets/github-octopuss.gif");
  Texture2D texture = LoadTextureFromImage(image);
  while (!WindowShouldClose()) {
    p = CheckAvatarMovement(p.X, p.Y);
    BeginDrawing();
    ClearBackground(GetColor(0x181818FF));
    DrawText("PRESS ARROW KEYS TO MOVE THE OBJECT", 10, 10, 20, WHITE);
    DrawTexture(texture, p.X, p.Y, WHITE);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}

Positions CheckAvatarMovement(float posX, float posY) {
  Positions p = {posX, posY};

  if (IsKeyPressed(KEY_SPACE)) {
    TraceLog(LOG_INFO, "SPACE KEY IS PRESSED");
  }
  if (IsKeyDown(KEY_RIGHT)) {
    p.X += GetFrameTime() + 2;
    TraceLog(LOG_INFO, "RIGHT KEY IS DOWN");
  }
  if (IsKeyDown(KEY_LEFT)) {
    p.X -= GetFrameTime() + 2;
    TraceLog(LOG_INFO, "LEFT KEY IS DOWN");
  }
  if (IsKeyDown(KEY_UP)) {
    p.Y -= GetFrameTime() + 2;
    TraceLog(LOG_INFO, "LEFT KEY IS DOWN");
  }
  if (IsKeyDown(KEY_DOWN)) {
    p.Y += GetFrameTime() + 2;
    TraceLog(LOG_INFO, "LEFT KEY IS DOWN");
  }
  return p;
}
