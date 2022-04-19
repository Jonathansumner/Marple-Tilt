#include "menu-pages.h"
#include <iostream>

#include "images.h"
#include "graphics.h"
#include "marple-tilt-machine.h"
#include "render.h"
#include "buttons.h"
#include "textbox.h"
#include "game-objects.h"
#include "collision-boxes.h"

#include <math.h>

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

void drawMenu(Canvas *c, string title) {
    font.LoadFont("img/5x8.bdf");
    fillBorder(borderColor, 2);
    if (title != "")
    {
        Textbox *title_box = new Textbox(getOffset(&title[0], 1), 2 + font.height(), {60, 170, 50}, c, title);
    }

}

Marple* drawStartMenu(Canvas *c)
{
    drawMenu(c, "");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    Textbox *text = new Textbox(14, 24, {60, 170, 50}, c, "Marple");
    Textbox *text2 = new Textbox(20, 34 + font.height(), {60, 170, 50}, c, "Tilt");

    StateButton *startGame = new StateButton(24, 44, 16, 16, "img/play.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawMainMenu(Canvas *c)
{
    drawMenu(c, "Main Menu");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    StateButton *chooseMap = new StateButton(14, 18, 16, 16, "img/map.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, 0));

    StateButton *chooseTutorial = new StateButton(36, 18, 16, 16, "img/question.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new TutorialMenu(c));

    StateButton *chooseCalibrate = new StateButton(14, 44, 16, 16, "img/compass.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new CalibrateMenu(c));

    StateButton *chooseSettings = new StateButton(36, 44, 16, 16, "img/wrench.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SettingsMenu(c));

    return m;
}

Marple* drawSettingsMenu(Canvas *c)
{
    drawMenu(c, "Settings");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    StateButton *chooseBrightness = new StateButton(12, 30, 16, 16, "img/sun.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new BrightnessMenu(c));

    StateButton *chooseSound = new StateButton(32, 30, 16, 16, "img/audio.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SoundMenu(c));

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawSoundMenu(Canvas *c)
{
    drawMenu(c, "Sound Menu");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    Textbox *tempBox = new Textbox(30, 20, {60, 170, 50}, c, "Coming", NULL);
    Textbox *tempBox2 = new Textbox(32, 30, {60, 170, 50}, c, "Soon", NULL);

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SettingsMenu(c));

    return m;
}

Marple* drawBrightnessMenu(Canvas *c)
{
    drawMenu(c, "Brightness");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    Textbox *tempBox = new Textbox(20, 30, {60, 170, 50}, c, "Coming", NULL);
    Textbox *tempBox2 = new Textbox(22, 30, {60, 170, 50}, c, "Soon", NULL);

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new SettingsMenu(c));

    return m;
}

Marple* drawGameplayMenu(Canvas *c)
{
    drawMenu(c, "Gameplay");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    Textbox *tempBox = new Textbox(20, 30, {60, 170, 50}, c, "Coming", NULL);
    Textbox *tempBox2 = new Textbox(22, 40, {60, 170, 50}, c, "Soon", NULL);

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawTutorialMenu(Canvas *c)
{
    drawMenu(c, "Tutorial");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    StateButton *startButton = new StateButton(30, 30, 16, 16, "img/play.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MoveTutorial(c));

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawCalibrateMenu(Canvas *c)
{
    drawMenu(c, "Calibrate");

    Marple *m = new Marple(32, 32, 3, new Home(32, 32, 5));

    Textbox *tempBox = new Textbox(20, 30, {60, 170, 50}, c, "Coming", NULL);
    Textbox *tempBox2 = new Textbox(22, 40, {60, 170, 50}, c, "Soon", NULL);

    StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawMapMenu(Canvas *c, vector<string> files, int pageNum, MapMenu *mm)
{
    drawMenu(c, "Map Menu");

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));

    vector<StateButton*> buttons;
    vector<Textbox*> boxes;
    int i = 0;

    if (files.size() > 0) 
    {
        for (string file : files)
        {
            buttons.push_back(new StateButton(4, 12 + (i*12), 12, 12, "img/map.png", 
                                &MarpleTiltMachine::StaticStateChange, &BaseState::runner, 
                                new GameRunning(c, mm->getLoader(), (i)+(pageNum*3)), 1));
            boxes.push_back(new Textbox(22, 18 + (i * 12), {60, 170, 50}, c, file, NULL));
            i++;
        }
    } else 
    {
        boxes.push_back(new Textbox(4, 30, {255, 0, 0}, c, "No Maps Found", NULL));
    }

    if (files.size() == 3)
    {
        StateButton *forwardButton = new StateButton(50, 50, 10, 10, "img/right.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, pageNum + 1));
    }

    string page = string("page ") + to_string(pageNum + 1);
    boxes.push_back(new Textbox(20, 60, {255, 0, 0}, c, page, NULL));

    if (pageNum > 0) {
        StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MapMenu(c, pageNum-1));
    } else  {
        StateButton *backButton = new StateButton(4, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));
    }

    boxes.clear();
    buttons.clear();

    return m;
}

Marple* drawGameOver(rgb_matrix::Canvas *c, double time)
{
    drawMenu(c, "");

    Textbox *resultBox = new Textbox(6, 20, {60, 170, 50}, c, "Well Done!", NULL);
    Textbox *resultBox2 = new Textbox(6, 30, {60, 170, 50}, c, "You Took", NULL);

    float a = roundf(time * 100.0) / 100.0;
    string timeString = to_string(a) + string(" secs");
    Textbox *scoreBox = new Textbox(6, 40, {60, 170, 50}, c, timeString, NULL);

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));

    StateButton *returnButton = new StateButton(8, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

Marple* drawTutOver(rgb_matrix::Canvas *c)
{
    drawMenu(c, "");


    Textbox *resultBox = new Textbox(4, 14, {60, 170, 50}, c, "You are now", NULL);
    Textbox *resultBox2 = new Textbox(8, 24, {60, 170, 50}, c, "ready to", NULL);
    Textbox *resultBox3 = new Textbox(10, 34, {60, 170, 50}, c, "play!", NULL);

    Marple *m = new Marple(32, 32, 3, new Home(20, 20, 5));

    StateButton *returnButton = new StateButton(8, 50, 10, 10, "img/left.png", &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new MainMenu(c));

    return m;
}

void drawZone(int x, int y, int d, Canvas *c, clock_t t, int tutNum) {
    if (tutNum == 1)
    {
        End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new FullTutorial(c), new StateCollisionBox(x, y, d, d, 0, &MarpleTiltMachine::StaticStateChange, false, &BaseState::runner, new FullTutorial(c)));
    }
    else if (tutNum == 2)
    {
        End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new HoleTutorial(c), new StateCollisionBox(x, y, d, d, 0, &MarpleTiltMachine::StaticStateChange, false, &BaseState::runner, new HoleTutorial(c)));
    }
    else if (tutNum == 3)
    {
        End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new TutorialOver(c), new StateCollisionBox(x, y, d, d, 0, &MarpleTiltMachine::StaticStateChange, false, &BaseState::runner, new TutorialOver(c)));
    }
    else
    {
        End *end = new End(x, y, d, &MarpleTiltMachine::StaticStateChange, &BaseState::runner, new GameOver(c, t), new StateCollisionBox(x, y, d, d, 0, &MarpleTiltMachine::StaticStateChange, false, &BaseState::runner, new GameOver(c, t)));
    }
}