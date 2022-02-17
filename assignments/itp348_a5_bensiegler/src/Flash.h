

class Flash
{
private:
    int redVal;
    int greenVal;
    int blueVal;
    unsigned int flashLengthInMillis;

public:
    Flash()
    {
        redVal = rand() % 255;
        greenVal = rand() % 255;
        blueVal = rand() % 255;
        flashLengthInMillis = 150;
    };

    Flash(int red, int green, int blue)
    {
        redVal = red;
        greenVal = green;
        blueVal = blue;
        flashLengthInMillis = 150;
    };

    Flash(int red, int green, int blue, unsigned int flashLength)
    {
        redVal = red;
        greenVal = green;
        blueVal = blue;
        flashLengthInMillis = flashLength;
    };

    int getRedVal()
    {
        return redVal;
    };
    int getGreenVal()
    {
        return greenVal;
    };
    int getBlueVal()
    {
        return blueVal;
    };
    int getFlashLengthInMillis()
    {
        return flashLengthInMillis;
    };
};