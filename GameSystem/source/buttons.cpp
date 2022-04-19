#include "buttons.h"
#include "collision-boxes.h"

StateButton::StateButton(int xp, int yp, int w, int h, std::string p, void (*f)(MarpleTiltMachine *, BaseState *), MarpleTiltMachine *fsm, BaseState *ns, int t) : Button{xp, yp, w, h, p}
{
    box = new StateCollisionBox(xp, yp, w, h, t, f, true, fsm, ns);
}