// Number of pins
#define NUM_OF_BUTTON 4

// Define pins
#define BUTTON_1 2
#define BUTTON_2 3
#define BUTTON_3 4
#define BUTTON_4 5
#define BUZZER_PIN 8

// Musical note frequencies (in Hz)
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Duration of each note (in milliseconds)
#define NOTE_DURATION 500

// Debouncing constants
#define DEBOUNCE_DELAY 50      // Debounce time (milliseconds)
#define HOLD_TIME 100          // Minimum time to hold button (milliseconds)

// Button state tracking
struct ButtonState {
  int pin;
  int lastState;
  unsigned long lastChangeTime;
  boolean buttonPressed;
  int frequency;
};

ButtonState buttons[NUM_OF_BUTTON] = {
  {BUTTON_1, LOW, 0, false, NOTE_C4},
  {BUTTON_2, LOW, 0, false, NOTE_D4},
  {BUTTON_3, LOW, 0, false, NOTE_E4},
  {BUTTON_4, LOW, 0, false, NOTE_F4}
};

void setup() {
  // Set button pins as INPUT_PULLUP (built-in pull-up resistors)
  pinMode(BUTTON_1, INPUT_PULLUP);
  pinMode(BUTTON_2, INPUT_PULLUP);
  pinMode(BUTTON_3, INPUT_PULLUP);
  pinMode(BUTTON_4, INPUT_PULLUP);
  
  // Set buzzer pin as OUTPUT
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Tone Keyboard Ready!");
  Serial.println("Press buttons to play notes...");
}

void loop() {
  // Check all buttons
  for (int i = 0; i < NUM_OF_BUTTON; i++) {
    checkButton(i);
  }
}

// Advanced debouncing function
void checkButton(int buttonIndex) {
  ButtonState* btn = &buttons[buttonIndex];
  
  // Read current state (LOW = pressed, HIGH = not pressed with INPUT_PULLUP)
  int currentState = digitalRead(btn->pin);
  
  // Check if state has changed
  if (currentState != btn->lastState) {
    btn->lastChangeTime = millis();  // Reset timer
    btn->lastState = currentState;
    return;  // Wait for debounce time
  }
  
  // If enough time has passed since the last change
  unsigned long timeSinceChange = millis() - btn->lastChangeTime;
  
  if (timeSinceChange >= DEBOUNCE_DELAY) {
    // Button is definitely pressed (LOW = pressed with INPUT_PULLUP)
    if (currentState == LOW && !btn->buttonPressed) {
      btn->buttonPressed = true;
      
      // Debug output
      Serial.print("Button ");
      Serial.print(buttonIndex + 1);
      Serial.println(" pressed!");
      
      // Play the tone
      playTone(btn->frequency, NOTE_DURATION);
    }
    
    // Button is released (HIGH = released with INPUT_PULLUP)
    else if (currentState == HIGH && btn->buttonPressed) {
      btn->buttonPressed = false;
      
      Serial.print("Button ");
      Serial.print(buttonIndex + 1);
      Serial.println(" released!");
    }
  }
}

// Function to play a tone at a specific frequency for a duration
void playTone(int frequency, int duration) {
  tone(BUZZER_PIN, frequency, duration);
  delay(duration);
  noTone(BUZZER_PIN);  // Stop the tone
}