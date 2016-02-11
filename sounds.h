#ifndef SOUNDS
#define SOUNDS

#include <QSound>
#include <QVector>


class myQSound : public QSound
{
    bool isPlaying;

public:
    myQSound(const QString& filename, QObject* parent = 0) :
        QSound(filename, parent), isPlaying(false)
    {
    }

    bool isPlay() const
    {
        return isPlaying;
    }

    void play()
    {
        isPlaying = true;
        QSound::play();
    }

    void stop()
    {
        isPlaying = false;
        QSound::stop();
    }
};


class Sounds
{    
private:
    QVector<myQSound *> themes;
    myQSound crash_sound;
    myQSound catch_sound;
    myQSound win_sound;
    myQSound lose_sound;

protected:
    Sounds():
        crash_sound("sounds/Crash.wav"),
        catch_sound("sounds/Catch.wav"),
        win_sound("sounds/Win.wav"),
        lose_sound("sounds/Lose.wav")
    {
        themes.append(new myQSound("sounds/Theme1.wav"));
        themes.append(new myQSound("sounds/Theme2.wav"));
        themes.append(new myQSound("sounds/Theme3.wav"));
        themes.append(new myQSound("sounds/Theme4.wav"));
        themes.append(new myQSound("sounds/Theme5.wav"));
        themes.append(new myQSound("sounds/Theme6.wav"));
        themes.append(new myQSound("sounds/Theme7.wav"));
    }
    ~Sounds()
    {
        for (int i = 0; i < themes.count(); i++)
        {
            delete themes[i];
        }
    }

public:
    static Sounds &getInstance()
    {
        static Sounds sounds;
        return sounds;
    }

    void playCatch()
    {
        catch_sound.play();
    }
    void playCrash()
    {
        crash_sound.play();
    }
    void playTheme(int levelNum)
    {
        int track_num = levelNum % themes.count();
        for (int i = 0; i < themes.count(); i++)
        {
            if (i != track_num) themes[i]->stop();
        }
        if (!themes[track_num]->isPlay())
        {
            themes[track_num]->setLoops(-1);
            themes[track_num]->play();
        }
    }

    void stopTheme()
    {
        for (int i = 0; i < themes.count(); i++)
        {
            themes[i]->stop();
        }
    }

    void playWin()
    {
        stopTheme();
        win_sound.play();
    }

    void playLose()
    {
        stopTheme();
        lose_sound.play();
    }

};


#endif // SOUNDS

