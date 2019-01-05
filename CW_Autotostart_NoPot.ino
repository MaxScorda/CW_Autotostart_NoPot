/*
  POT1: On/Off (>63)
  POT2: distanza casuale tra le note sdoppiate su due ottave sopra e sotto F3
  POT3: Velocity (0-127)
  POT4: inclinazione punto/linee
  BUT0: on/off
  BUT3: Attiva/disattiva debug
  NB: ricordarsi di disattivare in Ableton la quantizzazione delle note
*/
#include"Config.h";
//boolean debug=false;
boolean debug = true;

int POTPin[] = {
  0, 1, 2, 3, 4, 5
};

int IRBuffer[IR_BUFFER_SIZE];
int IRTotal[6] = {
  0, 0, 0, 0, 0, 0
};
int IRIndex[6] = {
  0, 0, 0, 0, 0, 0
};
int IRAverage[6] = {
  0, 0, 0, 0, 0, 0
};

int PotBuffer [6][POT_BUFFER_SIZE];
int PotTotal[6] = {
  0, 0, 0, 0, 0, 0
};
int PotAverage[6] = {
  0, 0, 0, 0, 0, 0
};
int PotIndex[6] = {
  0, 0, 0, 0, 0, 0
};


int POTVal[6];
int OldPOTVal[6];
int IRVal, OldIRVal;
int i = 0;
int TastoNota[12];
int TastoNotaOld[12];


int led = 13;
int contChar = 0;
String charCW;
int Nota1, Segno, resval;
//flag acceso/spento
boolean acceso = true;
//se nohardware acceso, scavalca i valori e metti dei default
//vedi in funzione setDefault
boolean noHardware = true;

//CW
int speakerPin = 9;
int pitch1 = 120;      //tone frequency
int pitch2 = 240;
int dot = 80;          // 250mS length of one dot
int dash = 3 * dot;     // Dash is equal to 3 dots in duration

// Morse code for Alphabet
String morseATable[ ] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",   // A-G
  "....", "..", ".---", "_._", ".-..", "--", "-.",    // H-N
  "---", ".--.", "--.-", ".-.", "...", "-", "..-",    // O-U
  "...-", ".--", "-..-", "-.--", "--.."               // V-Z
};

// Morse code for Numbers
String morseNTable[] = {
  "-----", ".----", "..---", "...--", "....-",       // 0-4
  ".....", "-....", "--...", "---..", "----."         // 5-9
};

String morseSTable[] = {
  ".-.-.-", "--..--", "..--..", "..--.",            //.,?!
  "---...", ".-..-.", ".----.", "-...-"             //:"'=
};

String Testo;
int TestoIdx = 0;
char* TestoFull[] = {
  "Ci sara' un giorno in cui il coraggio degli uomini cedera', ",
  "in cui abbandoneremo gli amici e spezzeremo ogni legame di fratellanza ma non e'questo il giorno."
  "Ci sara' l'ora dei lupi e degli scudi frantumati ",
  "quando l'era degli uomini arrivera' al crollo, ma non e' questo il giorno!",
  "Quest'oggi combattiamo! ",
  "Per tutto cio' che ritenete caro su questa bella terra, vi invito a resistere Uomini dell'ovest!!  "
};

void setup() {
  if (debug)Serial.begin(9600);
  else Serial.begin(31250);

  inizializzaPulsanti();
  pinMode(led, OUTPUT);
  Testo = TestoFull[0];
}

void loop() {
  LeggiPotenziometri();
  if (noHardware == true) setDefault();

  // se il contatore e' minore della stringa e il pot0 acceso, esegui
  // if ((acceso==true )&& (PotAverage[0]>63))  {
  if (acceso == true) {
    if (contChar < Testo.length()) {
      charCW = string2CW(String(Testo.charAt(contChar)));
      resval = map(PotAverage[1], 0, 127, 0, 11);

      Segno = RandNum(1, 2);
      if (Segno == 2) Segno = -1;
      Nota1 = 65 + (Segno * RandNum(0, resval));
      if (debug) {
        morseLED(charCW);
        Serial.print(Testo.charAt(contChar));
        Serial.print(" || ");
        Serial.print(padS(String(Testo.charAt(contChar), DEC), 3, " "));
        Serial.print(" || ");
        Serial.println(charCW);
      }
      else {
        morseNote(charCW, Nota1, Segno);
      }
      contChar++;
    }
    else {
      contChar = 0;
      //Serial.println(TestoIdx);
      if (TestoIdx == ((sizeof(TestoFull) / 2) - 1) || PotAverage[0] < 64) {
        TestoIdx = 0;
      }
      else TestoIdx++;
      Testo = TestoFull[TestoIdx];
    }
  }

  LeggiPulsanti();
  //debug mode
  if (TastoNota[3] != TastoNotaOld[3])  {
    if (TastoNota[3] == 0) {
      debug = !debug;
      if (debug)Serial.begin(9600);
      else Serial.begin(31250);
    }
  }

  //on/off
  if (TastoNota[0] != TastoNotaOld[0])  {
    if (TastoNota[0] == 0) OnOff();
  }

  //Trasferisci vecchi valori nei nuovi
  for (int i = 0; i < 6; i++)OldPOTVal[i] = PotAverage[i];
  for (int i = 0; i < 5; i++)TastoNotaOld[i] = TastoNota[i];
}
















