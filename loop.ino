void loop() {

  t.update();
  checkNextStep();
  

  if (nextStep) {
    for (int i = 0; i < num_of_channels; i++) {
      channels[i]->sendPulses(mainCount);
    }

    //sendSerialToMega();
    nextStep = false;
    mainCount++;
    if ( mainCount >= stepsMain ) resetMainCount();
  }
  
  for (int i = 0; i < num_of_channels; i++) {

    channels[i]->check();

    int encoder_value = encoders[i]->read() / 4;

    if (encoder_value != 0) {
      encoders[i]->write(0);
      channels[i]->setEncVal(encoder_value);
    }

    if (channels[i]->detectEncChange()) {
      channels[i]->drawPulses();
      channels[i]->printPulses();
    }
  }
}
