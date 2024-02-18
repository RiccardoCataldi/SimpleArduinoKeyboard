int buzzerPin = 8; 
int lastMidiNote = -1; a

void setup() {
  pinMode(buzzerPin, OUTPUT); 
  Serial.begin(115200); 
}

void loop() {
  if (Serial.available() > 0) {
    // Leggi il messaggio MIDI dalla porta seriale
    String serialMessage = Serial.readStringUntil('\n');
    
    if (serialMessage.startsWith("note_off")) {
      
      noTone(buzzerPin);
      lastMidiNote = -1;
    } else {
      
      int midiNote = serialMessage.toInt();
      if (midiNote >= 0 && midiNote <= 127) {
        // Suona la nota per un breve periodo
        float frequency = 440.0 * pow(2.0, (midiNote - 69) / 12.0);
        tone(buzzerPin, frequency, 500);
        lastMidiNote = midiNote;
      }
    }
  }
}
