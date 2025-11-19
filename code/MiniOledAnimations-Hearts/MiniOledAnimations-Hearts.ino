#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

#define TOUCH_PIN 4
#define THRESHOLD 40

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool animationRunning = false;

// Draw a heart at (x,y) with size s
void drawHeart(int x, int y, int s) {
  for (float t = 0; t < 6.28; t += 0.01) {
    int hx = x + s * 16 * pow(sin(t), 3) / 32;
    int hy = y - s * (13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t)) / 32;
    display.drawPixel(hx, hy, SSD1306_WHITE);
  }
}

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("Touch sensor to");
  display.println("start animation!");
  display.display();
}

void loop() {
  static bool lastTouch = false;
  int touchValue = touchRead(TOUCH_PIN);
  bool currentTouch = (touchValue < THRESHOLD);

  // Run animation only on NEW touch (rising edge)
  if(currentTouch && !lastTouch && !animationRunning) {
    animationRunning = true;
    runAnimation();
    animationRunning = false;
  }

  lastTouch = currentTouch;
  delay(50); // Debounce
}

void runAnimation() {
  // Animation 1: Expanding heart
  for(int s = 4; s <= 32; s += 2) {
    display.clearDisplay();
    drawHeart(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 8, s);
    display.display();
    delay(80);
  }
  delay(500);

  // Animation 2: Beating heart
  for(int beat = 0; beat < 8; beat++) {
    int s = (beat % 2 == 0) ? 28 : 20;
    display.clearDisplay();
    drawHeart(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 8, s);
    display.display();
    delay(180);
  }
  delay(500);

  // Animation 3: Exploding heart
  int cx = SCREEN_WIDTH/2;
  int cy = SCREEN_HEIGHT/2 + 8;
  int s = 26;
  for(int frame = 0; frame < 20; frame++) {
    display.clearDisplay();
    for (float t = 0; t < 6.28; t += 0.20) {
      int hx = cx + s * 16 * pow(sin(t), 3) / 32;
      int hy = cy - s * (13 * cos(t) - 5 * cos(2*t) - 2 * cos(3*t) - cos(4*t)) / 32;
      int dx = hx - cx;
      int dy = hy - cy;
      int ex = cx + dx + frame*dx/8 + random(-1,2);
      int ey = cy + dy + frame*dy/8 + random(-1,2);
      display.drawPixel(ex, ey, SSD1306_WHITE);
    }
    display.display();
    delay(60);
  }

  // Show done
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  display.println("Done!");
  display.display();
  delay(2000);

  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 10);
  display.println("Touch sensor to");
  display.println("start animation!");
  display.display();
}
