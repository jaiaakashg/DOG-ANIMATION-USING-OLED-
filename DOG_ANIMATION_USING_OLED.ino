#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64 
#define OLED_RESET    -1 

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int dogX = 0;          
int dogY = SCREEN_HEIGHT / 2; 
int dogWidth = 20;      
int dogHeight = 10;     
int animationState = 0; 
unsigned long lastUpdateTime = 0; 
const int animationInterval = 200; 

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.display();
  

  lastUpdateTime = millis();
  animate();
}

void loop() {
}

void animate() {
  while (true) {
    unsigned long currentTime = millis();
    
    if (currentTime - lastUpdateTime >= animationInterval) {
      lastUpdateTime = currentTime;
      updateAnimation()
      drawFrame();
      display.display();
    }
  }
}

void updateAnimation() {
  animationState = (animationState + 1) % 2; 
}

void drawFrame() {
  // Clear display
  display.clearDisplay();
  drawBackground();
  switch (animationState) {
    case 0:
      drawWalkingDog();
      break;
    case 1:
      drawRunningDog();
      break;
  }
}

void drawBackground() {
  display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_BLACK); 
}

void drawWalkingDog() {
  display.fillRect(dogX + 2, dogY + 5, 16, 8, SSD1306_WHITE); 
  display.fillRect(dogX, dogY + 4, 4, 4, SSD1306_WHITE); 
  display.fillRect(dogX + 4, dogY + 2, 4, 2, SSD1306_WHITE); 
  display.fillRect(dogX + 12, dogY + 2, 4, 2, SSD1306_WHITE); 
  display.fillRect(dogX + 4, dogY + 12, 2, 4, SSD1306_WHITE);
  display.fillRect(dogX + 14, dogY + 12, 2, 4, SSD1306_WHITE); 
  display.fillRect(dogX + 6, dogY + 12, 2, 4, SSD1306_WHITE); 
  display.fillRect(dogX + 12, dogY + 12, 2, 4, SSD1306_WHITE); 
}

void drawRunningDog() {
  display.fillRect(dogX + 2, dogY + 5, 16, 8, SSD1306_WHITE); 
  display.fillRect(dogX, dogY + 4, 4, 4, SSD1306_WHITE);
  display.fillRect(dogX + 4, dogY + 2, 4, 2, SSD1306_WHITE); 
  display.fillRect(dogX + 12, dogY + 2, 4, 2, SSD1306_WHITE); 
  display.fillRect(dogX + 4, dogY + 14, 2, 4, SSD1306_WHITE); 
  display.fillRect(dogX + 14, dogY + 14, 2, 4, SSD1306_WHITE);
  display.fillRect(dogX + 6, dogY + 12, 2, 4, SSD1306_WHITE); 
  display.fillRect(dogX + 12, dogY + 12, 2, 4, SSD1306_WHITE); 
}

