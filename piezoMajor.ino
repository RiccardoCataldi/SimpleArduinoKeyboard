int buzzerPin = 8; // Definisci il pin a cui è collegato il buzzer
int lastMidiNote = -1; // Variabile per tenere traccia dell'ultima nota suonata

void setup() {
  pinMode(buzzerPin, OUTPUT); // Imposta il pin come output
  Serial.begin(115200); // Inizia la comunicazione seriale a 9600 bps
}

void loop() {
  if (Serial.available() > 0) {
    // Leggi il messaggio MIDI dalla porta seriale
    String serialMessage = Serial.readStringUntil('\n');
    
    if (serialMessage.startsWith("note_off")) {
      // Interrompi il suono quando ricevi un messaggio "note_off"
      noTone(buzzerPin);
      lastMidiNote = -1;
    } else {
      // Analizza il messaggio MIDI e suona la nota corrispondente
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
