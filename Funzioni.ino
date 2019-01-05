void inizializzaPulsanti()
{
  for (int i=2; i<15; i++)
  {
    pinMode(i,INPUT);
    digitalWrite(i,HIGH);
  }
  for (int i=0; i<IR_BUFFER_SIZE; i++) IRBuffer[i]=0;

}


void LeggiPulsanti()
{
  for (int i=0; i<12; i++)
  {
    TastoNota[i]=digitalRead(i+2);
  }
}



void LeggiPotenziometri()
{
  for (int i=0; i<6; i++) 
  {
    POTVal[i]=analogRead(POTPin[i]);
    POTVal[i]=map(POTVal[i],0,1023,0,127);

    PotTotal[i]=PotTotal[i]-PotBuffer[i][PotIndex[POTPin[i]]];
    PotBuffer[i][PotIndex[POTPin[i]]]=POTVal[i];
    PotTotal[i]=PotTotal[i]+PotBuffer[i][PotIndex[POTPin[i]]];
    PotAverage[i]=PotTotal[i]/POT_BUFFER_SIZE;
    PotIndex[POTPin[i]]++;
    if (PotIndex[POTPin[i]]>=POT_BUFFER_SIZE) PotIndex[POTPin[i]]=0;
  }
  delay(1);
}


void TastiSoundAction(int cc)
{
  if (TastoNota[cc]!=TastoNotaOld[cc])
  {
    TastoNotaOld[cc]=TastoNota[cc];
    if (TastoNota[cc]==0) MIDImessage(NOTAON,cc+65,Vel);
    else  MIDImessage(NOTAOFF,cc+65,0);
    delay(1);
  }
}

int RandNum(int rmin, int rmax) {
  int result;
  randomSeed(millis()/(analogRead(5)+1));
  result =random(rmin, rmax+1);
  return result;
}

void spengoNote()
{
  //spengo tutte le note
  for (int i=50; i<89; i++) MIDImessage(NOTAOFF,i,0);
}


void OnOff(){
  acceso=!acceso;
  if (acceso==true){
    LedVal(1,0,0,0);
  }
  else{
    spengoNote();
    LedVal(0,0,0,0);
  }
}

void LedVal(boolean l1,boolean l2, boolean l3, int del){
  digitalWrite(10,l1); 
  digitalWrite(11,l2); 
  digitalWrite(12,l3);
  delay(del);
}

void setDefault(){
  PotAverage[0]=64;
  PotAverage[2]=96;
  PotAverage[3]=0;
  }
  
  String padS(String sstt, int lens, String charsub) {
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return sstt + spaces;
}
