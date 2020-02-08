void MIDImessage(int command, int data1, int data2) {
  Serial.write(command);//send command byte
  Serial.write(data1);//send data byte #1
  Serial.write(data2);//send data byte #2
}
