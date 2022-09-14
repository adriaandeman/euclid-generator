#include <Encoder.h>
#include <Wire.h>
#include <Timer.h>
#include <isr.h>

Isr isr[3] = {
  Isr(14, INPUT_PULLUP, 200),
  Isr(15, INPUT_PULLUP, 200),
  Isr(16, INPUT_PULLUP, 200)
};

const int num_of_channels = 3;
Encoder *encoders[num_of_channels];

Encoder encoder_one(5, 6);
Encoder encoder_two(7, 8);
Encoder encoder_three(9, 10);

class EuclidChannel {
  private:
    int channel;
    int steps, oldSteps;
    int pulses, oldPulses;
    const byte outputs[4] = {13, 20, 21, 33};
    bool setPulse = true;

  public:
    int array[16];

    EuclidChannel(int channel, int steps, int pulses) {
      this->channel = channel;
      this->steps = steps;
      this->pulses = pulses;
    }

    void drawPulses() {

      int pulseCounter = pulses;
      int curStep = 1;
      int arrCount = 0;

      for (int i = 0; i < steps; i++) array[i] = 0;

      while (curStep <= steps) {  //for each step
        if ( curStep > 0 ) {
          if (pulseCounter >= steps) {
            array[arrCount] = 1;
          }
          arrCount++;
        }
        if (pulseCounter >= steps) {
          pulseCounter -= steps;
        }
        pulseCounter += pulses;
        curStep++;
      }
    }

    void setEncVal(int increment) {
      if (setPulse) pulses += increment;
      else steps = steps += increment;
      pulses = constrain(pulses, 0, steps);
      steps = constrain(steps, 0, 16);
    }

    void check() {
     setPulse = isr[channel].state;
    }

    void printPulses() {
      char buf[12];
      sprintf(buf, "%d - %d | ", steps, pulses);
      Serial.print(buf);

      for (int i = 0; i < steps; i++) {
        Serial.print(array[i]);
        if (i < steps - 1) Serial.print(",");
      }
      Serial.println(" ");
    }

    bool detectEncChange() {
      if (steps != oldSteps || pulses != oldPulses) {
        oldSteps = steps;
        oldPulses = pulses;
        return true;
      }
      else return false;
    }

    void sendPulses(int count) {
      digitalWriteFast(outputs[channel], array[count]);
    }
};

EuclidChannel *channels[num_of_channels];

EuclidChannel channel1 = EuclidChannel(1, 16, 0);
EuclidChannel channel2 = EuclidChannel(2, 16, 0);
EuclidChannel channel3 = EuclidChannel(3, 16, 0);

IntervalTimer myTimer;
Timer t;

int stepsMain = 16;

int times[16];
int timeOffset[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int lengths[16];

int mainCount = 0;
int prevMainCount = 0;

volatile long millisAtStepOne = 0;
volatile boolean nextStep = false;

int width = 128;

int tempo = 200; //miliseconds
