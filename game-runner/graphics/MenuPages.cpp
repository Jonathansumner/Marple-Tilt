#include "MenuPages.h"
#include <iostream>

#include "gfx.h"
#include "images.h"
#include "../FSM/MarpleTiltMachine.h"

using namespace rgb_matrix;
using namespace std;

Font font;
Color fontColor(60, 170, 50);
Color borderColor(100, 28, 156);
Color titleColor(255, 0, 0);

int getOffset(char word[], int spaces) {
    int len = strlen(word);

    int offset = 64 - ((len * 4) + (len - 1) + spaces);

    return offset/2;
}

void drawMenu(Canvas *c, char* title) {
    font.LoadFont("img/5x8.bdf");
    fillBorder(borderColor, 2);
    if (title != "")
    {
        Textbox *title_box = new Textbox(getOffset(title, 1), 2 + font.height(), font, fontColor, c, title);
    }

}

void drawMainMenu(Canvas *c)
{
    drawMenu(c, "Main Menu");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/play.png";
    StateButton *chooseMap = new StateButton(14, 18, 16, 16, "img/map.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, 0));

    char word2[] = "img/question.png";
    StateButton *chooseTutorial = new StateButton(36, 18, 16, 16, "img/question.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new TutorialMenu(c));

    char word3[] = "img/compass.png";
    StateButton *chooseCalibrate = new StateButton(14, 44, 16, 16, "img/compass.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new CalibrateMenu(c));

    char word4[] = "img/wrench.png";
    StateButton *chooseSettings = new StateButton(36, 44, 16, 16, "img/wrench.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SettingsMenu(c));
}

void drawSettingsMenu(Canvas *c)
{
    drawMenu(c, "Settings");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/sun.png";
    StateButton *chooseBrightness = new StateButton(25, 30, 16, 16, "img/sun.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new BrightnessMenu(c));

    char word2[] = "img/audio.png";
    StateButton *chooseSound = new StateButton(45, 30, 16, 16, "img/audio.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SoundMenu(c));

    char word3[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawSoundMenu(Canvas *c)
{
    drawMenu(c, "Sound Menu");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    drawImage("img/audioup.png", c, {25, 30, 16, 16});
    drawImage("img/audiodown.png", c, {45, 30, 16, 16});

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawBrightnessMenu(Canvas *c)
{
    drawMenu(c, "Brightness");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    drawImage("img/sun.png", c, {30, 30, 16, 16});

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawGameplayMenu(Canvas *c)
{
    drawMenu(c, "Gameplay");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawTutorialMenu(Canvas *c)
{
    drawMenu(c, "Tutorial");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    StateButton *startButton = new StateButton(30, 30, 16, 16, "img/play.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MoveTutorial(c));

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawCalibrateMenu(Canvas *c)
{
    drawMenu(c, "Calibrate");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawMapMenu(Canvas *c, vector<string> files, int pageNum, MapMenu *mm)
{
    drawMenu(c, "Map Menu");

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    vector<StateButton*> buttons;
    vector<Textbox*> boxes;
    int i = 0;

    if (files.size() > 0) 
    {
        for (string file : files)
        {
            char *tmp = new char[file.length() + 1];
            strcpy(tmp, file.c_str());

            buttons.push_back(new StateButton(4, 12 + (i*12), 12, 12, "img/map.png", 
                                &MarpleTiltMachine::StaticStateChange, &BaseState::runner, 
                                new GameRunning(c, mm->getLoader(), (i)+(pageNum*3)), 1));
            boxes.push_back(new Textbox(22, 18 + (i*12), font, borderColor, c, tmp, NULL));
            i++;
        }
    } else 
    {
        boxes.push_back(new Textbox(4, 30, font, titleColor, c, "No Maps Found", NULL));
    }

    if (files.size() == 3)
    {
        StateButton *forwardButton = new StateButton(50, 50, 10, 10, "img/right.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, pageNum + 1));
    }

    string page = string("page ") + to_string(pageNum + 1);
    char *arr = new char[page.length() + 1];
    strcpy(arr, page.c_str());

    boxes.push_back(new Textbox(20, 60, font, titleColor, c, arr, NULL));

    if (pageNum > 0) {
        StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, pageNum-1));
    } else  {
        StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
    }

    boxes.clear();
    buttons.clear();
}

void drawGameOver(rgb_matrix::Canvas *c, double time)
{
    drawMenu(c, "");

    string s = "Well Done!";
    char *arr = new char[s.length() + 1];
    strcpy(arr, s.c_str());
    Textbox *resultBox = new Textbox(6, 20, font, borderColor, c, arr, NULL);

    string s2 = "You Took";
    char *arr2 = new char[s2.length() + 1];
    strcpy(arr2, s2.c_str());
    Textbox *resultBox2 = new Textbox(6, 30, font, borderColor, c, arr2, NULL);

    float a = floor(time * 100.0) / 100.0;
    string timeString = to_string(a) + string(" secs");
    char *tArr = new char[timeString.length() + 1];
    strcpy(tArr, timeString.c_str());
    Textbox *scoreBox = new Textbox(6, 40, font, borderColor, c, tArr, NULL);

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    StateButton *returnButton = new StateButton(8, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawTutOver(rgb_matrix::Canvas *c)
{
    drawMenu(c, "");

    string s = "You are now";
    char *arr = new char[s.length() + 1];
    strcpy(arr, s.c_str());
    Textbox *resultBox = new Textbox(8, 20, font, borderColor, c, arr, NULL);

    string s2 = "ready to play";
    char *arr2 = new char[s2.length() + 1];
    strcpy(arr2, s2.c_str());
    Textbox *resultBox2 = new Textbox(6, 30, font, borderColor, c, arr2, NULL);

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    StateButton *returnButton = new StateButton(8, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawMoveTutorial()
{

}

void drawZone(int x, int y, int d, Canvas *c, clock_t t) {
    End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new GameOver(c, t));
}