#include <Arduino.h>
int data = 15;
int set = 14;
int insert = 16;
int input1 = 6;
int input2 = 8;
int input3 = 5;
int input4 = 4;
int input5 = 3;
int input6 = 2;
int activeKey = 0;

void setValues()
{
    int states[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    states[activeKey] = 1;
    activeKey++;
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
    Serial.begin(9600);
    pinMode(data, OUTPUT);
    pinMode(insert, OUTPUT);
    pinMode(set, OUTPUT);
    pinMode(input1, INPUT);
    pinMode(input2, INPUT);
    pinMode(input3, INPUT);
    pinMode(input4, INPUT);
    pinMode(input5, INPUT);
    pinMode(input6, INPUT);
}

void readInputValues()
{

    Serial.print(digitalRead(input1));

    Serial.print(digitalRead(input2));

    Serial.print(digitalRead(input3));

    Serial.print(digitalRead(input4));

    Serial.print(digitalRead(input5));

    Serial.print(digitalRead(input6));
}
void loop()
{
    if (activeKey == 8)
    {
        activeKey = 0;
    }

    //  Serial.println(activeKey);
    setValues();
    readInputValues();
    delay(10);
}
