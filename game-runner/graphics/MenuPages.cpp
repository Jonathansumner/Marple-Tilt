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
    Textbox * title_box = new Textbox(getOffset(title, 1), 2 + font.height(), font, fontColor, c, title);
}

void drawMainMenu(Canvas *c)
{
    drawMenu(c, "Main Menu");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/play.png";
    StateButton *chooseMap = new StateButton(14, 18, 16, 16, "img/map.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c));

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

    char word[] = "img/left.png";
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
    cout << "Starting drawing\n";
    drawMenu(c, "Map Menu");
    cout << "Menu Core Drawn\n";

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

            buttons.push_back(new StateButton(6, 12 + (i*16), 16, 16, "img/map.png", 
                                &MarpleTiltMachine::StaticStateChange, &BaseState::runner, 
                                new GameRunning(c, mm->getLoader(), (i)*pageNum+1)));
            boxes.push_back(new Textbox(24, 20 + (i*16), font, borderColor, c, tmp, NULL));
            i++;
        }
    } else 
    {
        boxes.push_back(new Textbox(30, 30, font, titleColor, c, "No Maps Found", NULL));
    }

    cout << "State Buttons drawn\n";

    string page = string("page ") + to_string(pageNum + 1);
    char *arr = new char[page.length() + 1];
    strcpy(arr, page.c_str());

    boxes.push_back(new Textbox(20, 60, font, titleColor, c, arr, NULL));

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    boxes.clear();
    buttons.clear();
}

void drawGameOver(rgb_matrix::Canvas *c, double time)
{
    drawMenu(c, "Game Over");

    DrawText(c, font, 25, 20, titleColor, NULL, "Well Done!");
    DrawText(c, font, 35, 20, titleColor, NULL, "You took");

    const char result[] = "54.5 secs";
    DrawText(c, font, 45, 20, titleColor, NULL, result);

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));
    BaseState::runner.GetCurrentState()->setMarple(m);

    StateButton *returnButton = new StateButton(8, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
}

void drawZone(int x, int y, int d, Canvas *c, clock_t t) {
    End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new GameOver(c, t));
}