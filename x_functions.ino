void resetMainCount() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time > 200) {
    mainCount = 0;
    millisAtStepOne = millis();
  }
  last_interrupt_time = interrupt_time;
}


void checkNextStep() {
  if (millis() - millisAtStepOne >= times[mainCount]) nextStep = true;
}

void setTempo() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  tempo = interrupt_time - last_interrupt_time;
  last_interrupt_time = interrupt_time;
}


//void doAfter() {
//  digitalWrite(output1, LOW);
//  digitalWrite(output2, LOW);
//  digitalWrite(output3, LOW);
//}


//void sendPulses() {
//  t.after(50, doAfter);
//}


void sendSerialToMega() {
  Serial.println(mainCount);
  Serial.println("");

  Serial1.print("[1,");
  Serial1.print(mainCount);
  Serial1.println("]");
}


void printArray(int arr[3][16], int arraySize, int arrayNumber) {
  for (int i = 0; i < arraySize; i++) {
    Serial.print(arr[arrayNumber][i]);
    if (i == arraySize - 1) Serial.println("");
    else Serial.print(",");
  }
}

void printArray(int x[], int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    Serial.print(x[i]);
    if (i == arraySize - 1) Serial.println("");
    else Serial.print(",");
  }
}


void setArray(int x[], int value, int arraySize) {
  for (int i = 0; i < arraySize; i++) {
    x[i] = value;
  }
}
