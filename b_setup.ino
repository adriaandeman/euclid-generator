
void setup() {

  Serial.begin(115200);
  Serial1.begin(115200);

  delay(2000);

  encoders[0] = &encoder_one;
  encoders[1] = &encoder_two;
  encoders[2] = &encoder_three;

  channels[0] = &channel1;
  channels[1] = &channel2;
  channels[2] = &channel3;

  myTimer.begin(checkNextStep, 50000);

  pinMode(13, OUTPUT);
  pinMode(20, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);

  pinMode(23, INPUT);
  attachInterrupt(23, setTempo, FALLING);
  pinMode(24, INPUT);
  attachInterrupt(22, resetMainCount, FALLING);

  channels[0]->drawPulses();
  channels[1]->drawPulses();
  channels[2]->drawPulses();

  for (int i = 0; i < 3; i++) {
    printArray(channels[i]->array, 16);
  }

  for (int i = 0; i < 16; i++) {
    times[i] = (i * tempo) + timeOffset[i];
  }

  setArray(lengths, 50, 16);

  printArray(lengths, 16);
  printArray(times, 16);

  Serial.println("Start.");
  resetMainCount();
}
