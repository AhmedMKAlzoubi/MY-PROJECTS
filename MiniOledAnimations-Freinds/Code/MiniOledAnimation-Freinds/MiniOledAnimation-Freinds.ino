#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Draw a detailed stick figure at (x, y)
void drawStickGuy(int x, int y, int legStep, int mouthType, bool leftHandShake, bool rightHandShake, bool hugMode, bool happyEyes) {
  // Head
  display.drawCircle(x, y, 7, SSD1306_WHITE);

  // Eyes
  display.drawPixel(x-3, y-2, SSD1306_WHITE);
  display.drawPixel(x+3, y-2, SSD1306_WHITE);
  if (happyEyes) {
    display.drawPixel(x-3, y-1, SSD1306_WHITE);
    display.drawPixel(x+3, y-1, SSD1306_WHITE);
  }

  // Mouth (smile/frown/neutral) - fix: use drawPixel and drawLine
  if (mouthType == 1) { // Smile
    display.drawPixel(x-2, y+5, SSD1306_WHITE);
    display.drawPixel(x-1, y+6, SSD1306_WHITE);
    display.drawPixel(x,   y+6, SSD1306_WHITE);
    display.drawPixel(x+1, y+6, SSD1306_WHITE);
    display.drawPixel(x+2, y+5, SSD1306_WHITE);
  } else if (mouthType == -1) { // Frown
    display.drawPixel(x-2, y+7, SSD1306_WHITE);
    display.drawPixel(x-1, y+6, SSD1306_WHITE);
    display.drawPixel(x,   y+6, SSD1306_WHITE);
    display.drawPixel(x+1, y+6, SSD1306_WHITE);
    display.drawPixel(x+2, y+7, SSD1306_WHITE);
  } else { // Neutral
    display.drawLine(x-2, y+6, x+2, y+6, SSD1306_WHITE);
  }

  // Body
  display.drawLine(x, y+7, x, y+29, SSD1306_WHITE);

  // Legs (walk animation)
  int legY = y+29;
  display.drawLine(x, legY, x-7+legStep*3, legY+11, SSD1306_WHITE);
  display.drawLine(x, legY, x+7-legStep*3, legY+11, SSD1306_WHITE);

  // Arms
  if (hugMode)
    display.drawLine(x, y+10, x-10, y+18, SSD1306_WHITE);
  else if (leftHandShake)
    display.drawLine(x, y+10, x-18, y+14, SSD1306_WHITE);
  else
    display.drawLine(x, y+10, x-14, y+8, SSD1306_WHITE);

  if (hugMode)
    display.drawLine(x, y+10, x+10, y+18, SSD1306_WHITE);
  else if (rightHandShake)
    display.drawLine(x, y+10, x+18, y+14, SSD1306_WHITE);
  else
    display.drawLine(x, y+10, x+14, y+8, SSD1306_WHITE);

  // Hand/finger detail
  if (leftHandShake)
    display.drawCircle(x-18, y+14, 2, SSD1306_WHITE);
  if (rightHandShake)
    display.drawCircle(x+18, y+14, 2, SSD1306_WHITE);
  if (hugMode) {
    display.drawCircle(x-10, y+18, 2, SSD1306_WHITE);
    display.drawCircle(x+10, y+18, 2, SSD1306_WHITE);
  }
}

void drawSmallHeart(int x, int y) {
  display.fillCircle(x-1, y, 2, SSD1306_WHITE);
  display.fillCircle(x+2, y, 2, SSD1306_WHITE);
  display.drawTriangle(x-3, y, x+4, y, x, y+4, SSD1306_WHITE);
}

void drawSmallStar(int x, int y) {
  display.drawPixel(x, y, SSD1306_WHITE);
  display.drawLine(x-1, y, x+1, y, SSD1306_WHITE);
  display.drawLine(x, y-1, x, y+1, SSD1306_WHITE);
}

void setup() {
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
}

void loop() {
  int leftX = 30;
  int rightX = 98;
  int y = 20;

  // Step 1: Walking towards each other
  for (int step = 0; step <= 17; step += 1) {
    display.clearDisplay();
    drawStickGuy(leftX + step, y, (step % 4 == 0) ? 1 : ((step % 4 == 2) ? -1 : 0), 0, false, false, false, false);
    drawStickGuy(rightX - step, y, (step % 4 == 0) ? -1 : ((step % 4 == 2) ? 1 : 0), 0, false, false, false, false);
    display.display();
    delay(48);
  }
  delay(150);

  // Step 2: Smile and handshake arms
  for (int t = 0; t < 5; t++) {
    display.clearDisplay();
    drawStickGuy(leftX + 17, y, 0, 1, false, true, false, true);
    drawStickGuy(rightX - 17, y, 0, 1, true, false, false, true);
    display.display();
    delay(56);
  }
  delay(230);

  // Step 3: Handshake (wiggle arms, smiling faces)
  for (int i = 0; i < 7; i++) {
    int wiggle = (i % 2 == 0) ? 3 : -3;
    display.clearDisplay();
    drawStickGuy(leftX + 17 + wiggle, y, 0, 1, false, true, false, true);
    drawStickGuy(rightX - 17 + wiggle, y, 0, 1, true, false, false, true);
    display.display();
    delay(100);
  }
  delay(120);

  // Step 4: Hug (wrapping arms, happy eyes)
  for (int t = 0; t < 7; t++) {
    display.clearDisplay();
    drawStickGuy(leftX + 17, y, 0, 1, false, false, true, true);
    drawStickGuy(rightX - 17, y, 0, 1, false, false, true, true);
    display.display();
    delay(60);
  }
  delay(320);

  // Step 5: Stars and hearts, speech bubble
  for (int starFrame = 0; starFrame < 21; starFrame++) {
    display.clearDisplay();
    drawStickGuy(leftX + 17, y, 0, 1, false, false, true, true);
    drawStickGuy(rightX - 17, y, 0, 1, false, false, true, true);

    if (starFrame > 2) drawSmallStar(44, 37);
    if (starFrame > 4) drawSmallHeart(56, 27);
    if (starFrame > 5) drawSmallStar(69, 21);
    if (starFrame > 8) drawSmallHeart(81, 36);
    if (starFrame > 6) drawSmallHeart(88, 25);
    if (starFrame > 10) drawSmallStar(105, 40);
    if (starFrame > 6) drawSmallHeart(65, 46);
    if (starFrame > 14) drawSmallStar(118, 41);

    // Speech bubble "<3"
    if (starFrame > 12) {
      display.drawRoundRect(62, 6, 22, 9, 3, SSD1306_WHITE);
      display.setTextSize(1);
      display.setCursor(68, 8);
      display.print("<3");
    }

    display.display();
    delay(70);
  }

  // Step 6: Pause, loop again
  delay(1600);
}
