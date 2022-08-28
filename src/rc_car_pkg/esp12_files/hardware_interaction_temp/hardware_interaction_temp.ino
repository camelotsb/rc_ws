const int Enable_A = 4;

const int inputA1 = 3;
const int inputA2 = 2;

void setup()
{
    pinMode(Enable_A, OUTPUT);

    pinMode(inputA1, OUTPUT);
    pinMode(inputA2, OUTPUT);
}
void loop()
{
    //----Enable output A-----//
    digitalWrite(Enable_A, HIGH);

    //----------Run motor-----------//
    digitalWrite(inputA1, HIGH);
    digitalWrite(inputA2, LOW);

    delay(3000);
    //-------Disable Motor----------//
    digitalWrite(Enable_A, LOW);
    delay(3000);
    //-------Reverse Motor----------//
    digitalWrite(Enable_A, HIGH);

    digitalWrite(inputA1, LOW);
    digitalWrite(inputA2, HIGH);

    delay(3000);
    //-------Disable Motor----------//
    digitalWrite(Enable_A, LOW);

    delay(3000);
    //----------Speed rise----------//
    for (int i = 0; i < 1024; i++)
    {
        analogWrite(Enable_A, i);

        delay(40);
    }
    //----------Speed fall----------//
    for (int j = 1024; j > 0; j--)
    {
        analogWrite(Enable_A, j);

        delay(40);
    }
    //-------Disable Motor----------//
    digitalWrite(Enable_A, LOW);

    delay(3000);
}
