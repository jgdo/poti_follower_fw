#define ADC_ONESHOT_FORCE_USE_ADC2_ON_C3

#include <Arduino.h>

#ifdef ESP32C3
static constexpr auto PIN_LED = 8;
#else
static constexpr auto PIN_LED = LED_BUILTIN;
#endif

static constexpr auto NUM_ADC = 6;

static constexpr auto NUM_SAMPLES = 8;

void setup() {
    Serial.begin(1000000);
    analogReadResolution(12);

    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, HIGH);

    for (size_t i = 0; i < NUM_ADC; i++)
    {
        pinMode(A0+i, INPUT);
    }
}

int readAverageADC(uint8_t pin, size_t numSamples)
{
    int adcValue = 0;
    for (size_t i = 0; i < numSamples; i++)
    {
        adcValue += analogRead(pin);
        delayMicroseconds(30);
    }
    adcValue += numSamples / 2;  // for rounding
    adcValue /= numSamples;
    return adcValue;
}

void loop() {
    delay(5);
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));

    if(!Serial)
    {
        return;
    }

    for (size_t i = 0; i < NUM_ADC; i++)
    {
        const auto adcValue = readAverageADC(A0+i, NUM_SAMPLES);
        Serial.print(adcValue);
        Serial.print(" ");
    }
    Serial.println();
}
