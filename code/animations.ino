#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define WIDTH       8
#define HEIGHT      8
#define NUM_LEDS    (WIDTH * HEIGHT)
#define BRIGHTNESS  16

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// ======================================================
// Animation selector
// ======================================================
int op = 1;  
// 1 = Bouncing Balls
// 2 = Color Wipe (full HSV)
// 3 = Continuous Rainbow
// 4 = Sparkle
// 5 = Waves
// 6 = Solid Color Test

// ======================================================
// 180° Rotated Serpentine XY Mapping
// ======================================================
int XY(int x, int y) {
  x = (WIDTH - 1) - x;
  y = (HEIGHT - 1) - y;

  int col = x;

  if (col % 2 == 0)
    return col * HEIGHT + y;
  else
    return col * HEIGHT + (HEIGHT - 1 - y);
}

// ======================================================
// HSV → RGB
// ======================================================
uint32_t hsvToRgb(float h, float s, float v) {
  float r, g, b;

  int i = int(h * 6);
  float f = h * 6 - i;
  float p = v * (1 - s);
  float q = v * (1 - f * s);
  float t = v * (1 - (1 - f) * s);

  switch (i % 6) {
    case 0: r = v; g = t; b = p; break;
    case 1: r = q; g = v; b = p; break;
    case 2: r = p; g = v; b = t; break;
    case 3: r = p; g = q; b = v; break;
    case 4: r = t; g = p; b = v; break;
    case 5: r = v; g = p; b = q; break;
  }

  return strip.Color(int(r * 255), int(g * 255), int(b * 255));
}

// ======================================================
// 1 — Bouncing Balls
// ======================================================
#define BALLS 4
float posX[BALLS];
float posY[BALLS];
float velX[BALLS];
float velY[BALLS];
float hue[BALLS];

void initBalls() {
  for (int i = 0; i < BALLS; i++) {
    posX[i] = random(0, WIDTH);
    posY[i] = random(0, HEIGHT);
    velX[i] = (random(100) / 100.0f * 0.8f) - 0.4f;
    velY[i] = (random(100) / 100.0f * 0.8f) - 0.4f;
    hue[i] = float(i) / BALLS;
  }
}

void bouncingStep() {
  strip.clear();

  for (int i = 0; i < BALLS; i++) {
    hue[i] += 0.0025;
    if (hue[i] > 1.0) hue[i] -= 1.0;

    posX[i] += velX[i];
    posY[i] += velY[i];

    if (posX[i] < 0) { posX[i] = 0; velX[i] = -velX[i]; }
    if (posX[i] > WIDTH - 1) { posX[i] = WIDTH - 1; velX[i] = -velX[i]; }
    if (posY[i] < 0) { posY[i] = 0; velY[i] = -velY[i]; }
    if (posY[i] > HEIGHT - 1) { posY[i] = HEIGHT - 1; velY[i] = -velY[i]; }

    int cx = int(posX[i]);
    int cy = int(posY[i]);

    uint32_t color = hsvToRgb(hue[i], 1.0, 1.0);
    strip.setPixelColor(XY(cx, cy), color);

    for (int dx = -2; dx <= 2; dx++) {
      for (int dy = -2; dy <= 2; dy++) {
        int nx = cx + dx;
        int ny = cy + dy;
        if (nx < 0 || nx >= WIDTH || ny < 0 || ny >= HEIGHT) continue;

        float dist = sqrt(dx*dx + dy*dy);
        if (dist > 2.2) continue;

        float fade = 1.0 - (dist / 2.2);
        uint32_t glow = hsvToRgb(hue[i], 1.0, fade * 0.7);
        strip.setPixelColor(XY(nx, ny), glow);
      }
    }
  }

  strip.show();
}

// ======================================================
// 2 — Color Wipe (Full Color Cycle)
// ======================================================
int wipeIndex = 0;
float wipeHue = 0;

void colorWipeStep() {
  static bool started = false;
  if (!started) { strip.clear(); started = true; }

  uint32_t color = hsvToRgb(wipeHue, 1.0, 1.0);
  strip.setPixelColor(wipeIndex, color);

  wipeIndex++;

  if (wipeIndex >= NUM_LEDS) {
    wipeIndex = 0;
    started = false;

    wipeHue += 0.1;
    if (wipeHue > 1.0) wipeHue -= 1.0;
  }

  strip.show();
}

// ======================================================
// 3 — Continuous Rainbow
// ======================================================
float rainbowPos = 0;

void rainbowStep() {
  rainbowPos += 0.015;
  if (rainbowPos >= 1.0) rainbowPos -= 1.0;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      float h = fmod(rainbowPos + (float)x / WIDTH, 1.0);
      strip.setPixelColor(XY(x, y), hsvToRgb(h, 1.0, 1.0));
    }
  }

  strip.show();
}

// ======================================================
// 4 — Sparkle Effect
// ======================================================
void sparkleStep() {
  strip.clear();
  for (int i = 0; i < 20; i++) {
    int p = random(NUM_LEDS);
    float hue = random(1000) / 1000.0;
    strip.setPixelColor(p, hsvToRgb(hue, 1.0, 1.0));
  }
  strip.show();
}

// ======================================================
// 5 — Waves
// ======================================================
float waveT = 0;

void wavesStep() {
  waveT += 0.1;

  for (int x = 0; x < WIDTH; x++) {
    for (int y = 0; y < HEIGHT; y++) {
      float v = (sin(x * 0.4 + waveT) + sin(y * 0.4 + waveT)) * 0.25 + 0.5;
      strip.setPixelColor(XY(x, y), hsvToRgb(v, 1.0, 1.0));
    }
  }

  strip.show();
}

// ======================================================
// 6 — Solid Color Test
// ======================================================
void solidColorStep() {
  float h = millis() * 0.0001;  
  h = fmod(h, 1.0);
  uint32_t color = hsvToRgb(h, 1.0, 1.0);

  for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, color);
  strip.show();
}

// ======================================================
void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();
  initBalls();
}

void loop() {
  switch (op) {
    case 1: bouncingStep();   break;
    case 2: colorWipeStep();  break;
    case 3: rainbowStep();    break;
    case 4: sparkleStep();    break;
    case 5: wavesStep();      break;
    case 6: solidColorStep(); break;
  }

  delay(20);
}
