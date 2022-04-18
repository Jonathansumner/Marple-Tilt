#pragma once
#include "button.h"

class MarpleTiltMachine;
class BaseState;

class StateButton : public Button
{
private:
public:
    StateButton(int xp, int yp, int w, int h, char *p, void (*f)(MarpleTiltMachine *, BaseState *), MarpleTiltMachine *fsm, BaseState *ns, int time = 1);
};