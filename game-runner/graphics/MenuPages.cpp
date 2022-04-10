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

void drawMenu(Canvas *c, char title[]) {
    font.LoadFont("img/5x8.bdf");
    fillBorder(borderColor, 2);
    DrawText(c, font, getOffset(title, 1), 2 + font.height(), fontColor, NULL, title, 0);
}

void drawMainMenu(Canvas *c)
{
    drawMenu(c, "Main Menu");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/play.png";
    StateButton *chooseMap = new StateButton(14, 18, 16, 16, "img/map.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MapMenu(c));

    char word2[] = "img/question.png";
    StateButton *chooseTutorial = new StateButton(36, 18, 16, 16, "img/question.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new TutorialMenu(c));

     char word3[] = "img/compass.png";
     StateButton *chooseCalibrate = new StateButton(14, 44, 16, 16, "img/compass.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new CalibrateMenu(c));

     char word4[] = "img/wrench.png";
     StateButton *chooseSettings = new StateButton(36, 44, 16, 16, "img/wrench.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new SettingsMenu(c));
}

void drawSettingsMenu(Canvas *c)
{
    drawMenu(c, "Settings");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/sun.png";
    StateButton *chooseBrightness = new StateButton(25, 30, 16, 16, "img/sun.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new BrightnessMenu(c));

    char word2[] = "img/audio.png";
    StateButton *chooseSound = new StateButton(45, 30, 16, 16, "img/audio.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new SoundMenu(c));

    char word3[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawSoundMenu(Canvas *c)
{
    drawMenu(c, "Sound Menu");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    drawImage("img/audioup.png", c, {25, 30, 16, 16});
    drawImage("img/audiodown.png", c, {45, 30, 16, 16});

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawBrightnessMenu(Canvas *c)
{
    drawMenu(c, "Brightness");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    drawImage("img/sun.png", c, {30, 30, 16, 16});

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawGameplayMenu(Canvas *c)
{
    drawMenu(c, "Gameplay");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawTutorialMenu(Canvas *c)
{
    drawMenu(c, "Tutorial");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawCalibrateMenu(Canvas *c)
{
    drawMenu(c, "Calibrate");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));
}

void drawMapMenu(Canvas *c, vector<string> files, int pageNum)
{
    drawMenu(c, "Map Menu");

    Home *home = new Home(32, 32, 5);
    Marple *m = new Marple(32, 32, 3, home);
    GameState::runner.GetCurrentState()->setMarple(m);

    int filesLeft = files.size() - (pageNum * 4);

    for (int i=1; i<=filesLeft && i<5; i++) {
        string option = to_string(i + (pageNum * 4)) + " " + files[(i-1) + (pageNum * 4)];
        const char *array = option.c_str();

        DrawText(c, font, 6, 10 + (i*10), fontColor, NULL, array, 0);
    }

    string page = "page " + to_string(pageNum + 1);
    const char *tmp = page.c_str();

    char word[] = "img/left.png";
    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &GameState::runner, new MainMenu(c));

    DrawText(c, font, 20, 60, titleColor, NULL, tmp, 0);
    drawImage("img/right.png", c, {52, 56, 10, 10});
}