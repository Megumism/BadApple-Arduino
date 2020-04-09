int singer = 9;
enum TONE
{
    C,
    UC,
    D,
    UD,
    E,
    F,
    UF,
    G,
    UG,
    A,
    UA,
    B
};

void setup()
{
    Serial.begin(1200);
    pinMode(singer, OUTPUT);
}

int ToneX(enum TONE main, int SoundIN, bool up) //主调映射函数
{
    int Sound2Tone;
    int Sound2Height;
    int SoundOUT;
    if (SoundIN >= 0)
    {
        Sound2Tone = SoundIN % 10;
        Sound2Height = SoundIN / 10;
    }
    else
    {
        Sound2Tone = (-SoundIN) % 10;
        Sound2Height = -(((-SoundIN) / 10) + 1);
        // Serial.println(Sound2Tone);
        // Serial.println(Sound2Height);
    }
    if (Sound2Tone == 1)
        Sound2Tone = 0;
    else if (Sound2Tone == 2)
        Sound2Tone = 2;
    else if (Sound2Tone == 3)
        Sound2Tone = 4;
    else if (Sound2Tone == 4)
        Sound2Tone = 5;
    else if (Sound2Tone == 5)
        Sound2Tone = 7;
    else if (Sound2Tone == 6)
        Sound2Tone = 9;
    else if (Sound2Tone == 7)
        Sound2Tone = 11;
    SoundOUT = main - A + up + Sound2Tone + Sound2Height * 12;
    // Serial.println(SoundOUT);
    return int(pow(2, SoundOUT / 12.0) * 440.0 + 0.5); //这里加0.5实现四舍五入
}

void Sing(enum TONE Main, float Song[], int length, int beat)
{
    int sing;
    bool up;
    for (int i = 0; i < length; i++)
    {
        if (Song[i] != 0)
        {
            if (int(Song[i] * 2) % 2)
                up = true;
            else
                up = false;
            sing = Song[i];
            Serial.println(ToneX(Main, sing, up));
            tone(singer, ToneX(Main, sing, up));
        }
        else
            noTone(singer);
        delay(beat);
    }
}

void loop()
{
    // int Song[] =
    //     {1, 2, 3, 4, 5, 6, 7};

    float Song[] = {
        -6, -7, 1, 2, 3, 3, 6, 5,
        3, 3, -6, -6, 3, 2, 1, -7,
        -6, -7, 1, 2, 3, 3, 2, 1,
        -7, -6, -7, 1, -7, -6, -5.5, -7,

        -6, -7, 1, 2, 3, 3, 6, 5,
        3, 3, -6, -6, 3, 2, 1, -7,
        -6, -7, 1, 2, 3, 3, 2, 1,
        -7, -7, 1, 1, 2, 2, 3, 3,

        5, 6, 3, 2, 3, 3, 2, 3,
        5, 6, 3, 2, 3, 3, 2, 3,
        2, 1, -7, -5, -6, -6, -5, -6,
        -7, 1, 2, 3, -6, -6, 3, 5,

        5, 6, 3, 2, 3, 3, 2, 3,
        5, 6, 3, 2, 3, 3, 2, 3,
        2, 1, -7, -5, -6, -6, -5, -6,
        -7, 1, 2, 3, -6, -6, 3, 5,

        5, 6, 3, 2, 3, 3, 2, 3,
        5, 6, 3, 2, 3, 3, 2, 3,
        2, 1, -7, -5, -6, -6, -5, -6,
        -7, 1, 2, 3, -6, -6, 3, 5,

        5, 6, 3, 2, 3, 3, 2, 3,
        5, 6, 3, 2, 3, 3, 6, 7,
        11, 7, 6, 5, 3, 3, 2, 3,
        2, 1, -7, -5, -6, -6, 3, 5};

    int length = sizeof(Song) / sizeof(Song[0]);
    // Serial.println(length);

    Sing(UF, Song, length, 210);
    noTone(singer);
    delay(1000);
}