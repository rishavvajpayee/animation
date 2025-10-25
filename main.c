#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

typedef struct {
  float X;
  float Y;
  bool collected;
} Positions;

#define NUM_COLLECTIBLES 3

Positions p = {100, 100, false};
Positions collectibles[NUM_COLLECTIBLES];
int score = 0;
int collectiblesGathered = 0;

void DrawCircleV(Vector2 center, float radius, Color color);
Positions CheckAvatarMovement(float X, float Y);

void InitCollectibles() {
  for (int i = 0; i < NUM_COLLECTIBLES; i++) {
    collectibles[i].X = GetRandomValue(50, 1150);
    collectibles[i].Y = GetRandomValue(50, 950);
    collectibles[i].collected = false;
  }
}

void CheckCollisions() {
  for (int i = 0; i < NUM_COLLECTIBLES; i++) {
    if (!collectibles[i].collected) {
      float dx = p.X - collectibles[i].X;
      float dy = p.Y - collectibles[i].Y;
      float distance = sqrt(dx * dx + dy * dy);

      if (distance < 50) {  // Increased collision distance for larger avatar
        collectibles[i].collected = true;
        score += 100;
        collectiblesGathered++;
      }
    }
  }
}

int main() {
  InitWindow(1200, 1000, "Collect the Stars!");
  SetTargetFPS(60);
  Image image = LoadImage("./assets/github-octopuss.gif");
  Texture2D texture = LoadTextureFromImage(image);

  InitCollectibles();

  while (!WindowShouldClose()) {
    p = CheckAvatarMovement(p.X, p.Y);
    CheckCollisions();

    BeginDrawing();
    ClearBackground(GetColor(0x181818FF));

    // Draw collectibles
    for (int i = 0; i < NUM_COLLECTIBLES; i++) {
      if (!collectibles[i].collected) {
        DrawCircle(collectibles[i].X, collectibles[i].Y, 10, YELLOW);
      }
    }

     // Draw player (scaled up by 2x)
     DrawTextureEx(texture, (Vector2){p.X, p.Y}, 0.0f, 2.0f, WHITE);

    // Draw UI
    DrawText("PRESS ARROW KEYS TO MOVE AND COLLECT STARS", 10, 10, 20, WHITE);
    char scoreText[32];
    sprintf(scoreText, "Score: %d", score);
    DrawText(scoreText, 10, 40, 20, WHITE);

    // Check win condition
    if (collectiblesGathered == NUM_COLLECTIBLES) {
      DrawText("YOU WIN!", 500, 400, 50, GREEN);
    }

    EndDrawing();
  }

  UnloadTexture(texture);
  UnloadImage(image);
  CloseWindow();
  return 0;
}

Positions CheckAvatarMovement(float posX, float posY) {
  Positions p = {posX, posY};

  if (IsKeyPressed(KEY_SPACE)) {
    TraceLog(LOG_INFO, "SPACE KEY IS PRESSED");
  }
  if (IsKeyDown(KEY_RIGHT)) {
    p.X += GetFrameTime() * 400;  // Increased speed to 400 pixels per second
    TraceLog(LOG_INFO, "RIGHT KEY IS DOWN");
  }
  if (IsKeyDown(KEY_LEFT)) {
    p.X -= GetFrameTime() * 400;  // Increased speed to 400 pixels per second
    TraceLog(LOG_INFO, "LEFT KEY IS DOWN");
  }
  if (IsKeyDown(KEY_UP)) {
    p.Y -= GetFrameTime() * 400;  // Increased speed to 400 pixels per second
    TraceLog(LOG_INFO, "UP KEY IS DOWN");  // Fixed log message
  }
  if (IsKeyDown(KEY_DOWN)) {
    p.Y += GetFrameTime() * 400;  // Increased speed to 400 pixels per second
    TraceLog(LOG_INFO, "DOWN KEY IS DOWN");  // Fixed log message
  }
  return p;
}
