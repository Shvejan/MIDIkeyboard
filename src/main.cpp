#include <Arduino.h>
#include "MIDIUSB.h"
byte data = 15;
byte set = 14;
byte insert = 16;
byte inputs[6] = {6, 8, 5, 4, 3, 2};
byte activeKey = 0;

byte col = 8;
byte row = 6;
// byte midiMaps = [6][8] = {{28}};
boolean allNotes[6][8] = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}};
void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void setValues(byte currentActiveKey)
{
  boolean states[8] = {false, false, false, false, false, false, false, false};
  states[currentActiveKey] = true;

  digitalWrite(set, LOW);
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(insert, LOW);
    digitalWrite(data, states[i]);
    digitalWrite(insert, HIGH);
  }
  digitalWrite(set, HIGH);
}

void setup()
{
  // Serial.begin(9600);
  pinMode(data, OUTPUT);
  pinMode(insert, OUTPUT);
  pinMode(set, OUTPUT);

  for (int i = 0; i < row; i++)
  {
    pinMode(inputs[i], INPUT);
  }
}

void readInputValues(byte currentActiveKey)
{

  for (int i = 0; i < row; i++)
  {
    // Serial.print(digitalRead(inputs[i]));
    // Serial.print(" - ");
    // Serial.print(allNotes[i][currentActiveKey]);
    // Serial.print(allNotes[i][currentActiveKey] != digitalRead(inputs[i]));
    // Serial.print(", ");
    if (allNotes[i][currentActiveKey] != digitalRead(inputs[i]))
    {
      if (allNotes[i][currentActiveKey] == 0)
      {
        // Serial.print("key pressed :");
        // Serial.print(currentActiveKey);
        // Serial.println(i);
        noteOn(0, 29 + i * 8 + currentActiveKey, 64); // Channel 0, middle C, normal velocity
        MidiUSB.flush();
      }
      else
      {
        // Serial.print("key released :");
        // Serial.print(currentActiveKey);
        // Serial.println(i);
        noteOff(0, 29 + i * 8 + currentActiveKey, 64); // Channel 0, middle C, normal velocity
        MidiUSB.flush();
      }
      allNotes[i][currentActiveKey] = !allNotes[i][currentActiveKey];
    }
  }
  // Serial.println("");
}
void loop()
{

  if (activeKey == 8)
    activeKey = 0;
  // Serial.println(activeKey);
  setValues(activeKey);
  readInputValues(activeKey);
  activeKey++;
  delayMicroseconds(1);
}
