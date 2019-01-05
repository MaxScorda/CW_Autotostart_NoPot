


String string2CW(String message)
/* 
 Description: Converts characters in a string to the Morse code sequence
 Argument:    String to be converted
 Returns:     nul
 Calls:       morseLED
 */
{
  String resultCW;
  for (int pos = 0; pos < message.length(); pos++)
  { 
    message.toLowerCase();

    switch (message.charAt(pos)){
    case '.':
      resultCW=morseSTable[0];
      break;
    case ',':
      resultCW=morseSTable[1];
      break;
    case '?':
      resultCW=morseSTable[2];
      break;
    case '!':
      resultCW=morseSTable[3];
      break;
    case ':':
      resultCW=morseSTable[4];
      break;
    case '"':
      resultCW=morseSTable[5];
      break;
    case 39:
      resultCW=morseSTable[6];
      break;
    case '=':
      resultCW=morseSTable[7];
      break;
    default:
      // Check for a lower case character
      if ((message.charAt(pos) >= 97) && (message.charAt(pos) <= 122)) resultCW=morseATable[message.charAt(pos)-97];
      // Check for a number
      if ((message.charAt(pos) >= 48) && (message.charAt(pos) <= 57)) resultCW=morseNTable[message[pos]-48];  
      // Check for a space, a space is equal to 3 dots
      if (message.charAt(pos) == 32)  resultCW="   ";  
    }
    return resultCW;

  }
}

// FUNZIONI PER LED

void morseLED(String sequence)
/* 
 Description: Passes individual dots and dashes (and Spaces) to flashLED handler
 Argument:    Morse Code sequence
 Returns:     nul
 Calls:       flashLED
 */
{  
  for (int pos = 0; pos < sequence.length(); pos++)


    flashLED(sequence.charAt(pos));
  delay(2 * dot);                                                             // Space between two letters is equal to three dots (one dash)
}


void flashLED(char dotOrDash)
/* 
 Description: Produces a dot, dash or space flash on the LED
 Argument:    Individual dot or dash
 Returns:     nul
 Calls:       none
 */
{
  if (dotOrDash == 46)              // ASCII code for a dot is 46
  {
    digitalWrite(led, HIGH);   // turn the LED on
    tone (speakerPin, pitch1);
    delay(dot);                   // wait for period of the dot
    digitalWrite(led, LOW);    // turn the LED off 
    noTone(speakerPin); 
    delay(dot);
  }
  else
    if (dotOrDash == 45)
    {                               // ASCII code for a dash is 45
      digitalWrite(led, HIGH);   // turn the LED on 
      tone (speakerPin, pitch2);
      delay(dash);                  // wait for period of the dash
      digitalWrite(led, LOW);    // turn the LED off 
      noTone(speakerPin); 
      delay(dot);
    }
    else
      if (dotOrDash == 32)            // ASCII code for a space is 32
          delay(dot);                   // No flashes, just a time delay
}


// Funzioni per suonare duplicate dal led

void morseNote(String sequence, int Distanza, int Segno)
{  
  float inclinazione;
  inclinazione=map(PotAverage[3],0,127,0,sequence.length());
  inclinazione=inclinazione/sequence.length();
  //Distanza=Distanza+(-1*Segno); //siccome salta di 1 o - a seconda del segno, lo pareggio
  for (int pos = 0; pos < sequence.length(); pos++)
    flashNote(sequence.charAt(pos), Distanza+(Segno*(pos*inclinazione)));
  delay(2 * dot);                                                             // Space between two letters is equal to three dots (one dash)
}

void flashNote(char dotOrDash, int Distanza)
{
  switch (dotOrDash){
  case 46:  // ASCII code for a dot is 46
    MIDImessage(NOTAON,Distanza,PotAverage[2]); 
    delay(dot);        // wait for period of the dot
    MIDImessage(NOTAOFF,Distanza,PotAverage[2]); 
    delay(dot);
    break;

  case 45: // ASCII code for a dash is 45
    MIDImessage(NOTAON,Distanza,PotAverage[2]); 
    delay(dash);       // wait for period of the dash
    MIDImessage(NOTAOFF,Distanza,PotAverage[2]); 
    delay(dot);
    break;

  case 32: // ASCII code for a space is 32
    delay(dot);       // No flashes, just a time delay
    break;
  }
}






