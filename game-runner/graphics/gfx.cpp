#include "gfx.h"

vector<float> Object::move(float x, float y) {
    if (x_pos + x >= 0 && x_pos + x < 64) {
        x_pos += x;
    }
    if (x_pos + y >= 0 && x_pos + y < 64) {
        y_pos += y;
    }
    vector<float> ret{x_pos, y_pos};
    return ret;
}

vector<float> Object::getPos() {
    std::vector<float> pos;
    pos.push_back(x_pos);
    pos.push_back(y_pos);
    return pos;
}

draw_type Object::getType() {
    return type;
}

void Object::setColour(std::vector<int> colour) {
    red = colour[0], green = colour[1], blue = colour[2];
}

void Object::setPos(std::vector<float> pos) {
    x_pos = pos[0];
    y_pos = pos[1];
}

int Marple::getDiameter() {
    return diameter;
}

Marple::~Marple() {
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());
}

int Hole::getDiameter() {
    return diameter;
}

void LoadingBar::setDiameter(float d) {
    diameter = d;
}

float LoadingBar::getDiameter() {
    return diameter;
}

int LoadingBar::getHeight() {
    return height;
}


// OLD SHAPES


void fillRect(float start_x, float start_y, int w, int h, Object *obj, Object *(&array)[64][64]) {
    int starting_x = (int) std::round(start_x);
    int starting_y = (int) std::round(start_y);
    for (int w_curr = 0; w_curr < w; w_curr++) {
        for (int h_curr = 0; h_curr < h; h_curr++) {
            if ((starting_x + w_curr <= 64) && (starting_x + w_curr >= 0) and (starting_y + h_curr <= 64) &&
                (starting_y + h_curr >= 0)) {
                array[starting_x + w_curr][starting_y + h_curr] = obj;
            }
        }
    }
}

void fillBorder(Canvas *c, Color borderColor, int width) {
    Wall *walls[124];
    int rVal = static_cast<int>(borderColor.r),
            gVal = static_cast<int>(borderColor.g),
            bVal = static_cast<int>(borderColor.b);

    for (int i = 0; i < 31; i++) {
        float n = static_cast<float>(i);

        walls[i] = new Wall(n * 2, 0, width);
        walls[i]->setColour({rVal, gVal, bVal});

        walls[i + 31] = new Wall(62, n * 2, width);
        walls[i + 31]->setColour({rVal, gVal, bVal});

        walls[i + 62] = new Wall(62 - n * 2, 62, width);
        walls[i + 62]->setColour({rVal, gVal, bVal});

        walls[i + 93] = new Wall(0, 62 - n * 2, width);
        walls[i + 93]->setColour({rVal, gVal, bVal});
    }
}

CollisionBox::CollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*func)(), bool loading_bar) { //
    colliders.push_back(this);
    x = x_pos;
    y = y_pos;
    width = w;
    height = h;
    progress = 0;
    callback = func;
    progress_secs = trigger_time;
    if (loading_bar) {
        bar = new LoadingBar(x, y, height);
    }
}

bool CollisionBox::checkCollision(Marple *marple, CollisionBox *collider) {
    int marp_x = marple->getPos()[0], marp_y = marple->getPos()[1], marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
         ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width)))
        &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
         ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height)))) {
        return true;
    }
    return false; //TODO: look into destructor and removing from vectors
}

bool StateCollisionBox::checkCollision(Marple *marple, StateCollisionBox *collider)
{
    int marp_x = marple->getPos()[0], marp_y = marple->getPos()[1], marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
         ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width))) &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
         ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height))))
    {
        return true;
    }
    return false; // TODO: look into destructor and removing from vectors
}

void CollisionBox::colliderPoll(Marple *marple) { //TODO: make real-time?
    for (CollisionBox *collider: colliders) {
        if (checkCollision(marple, collider)) {
            if (collider->progress <= (collider->progress_secs * 60) - 1) {
                collider->progress++;
            } else {
                collider->callback(); // if progress bar limit reached, run specific callback
                collider->progress = 0;
            }
        } else {
            collider->progress = 0;
        }
        collider->bar->setDiameter(collider->progress * ((float)collider->width/(float)(collider->progress_secs * 60)));
    }
}

StateCollisionBox::StateCollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*f)(MarpleTiltMachine *, GameState *), bool loading_bar, MarpleTiltMachine *fsm, GameState *nS) : CollisionBox{x_pos, y_pos, w, h, trigger_time, NULL, loading_bar}
{
    stateColliders.push_back(this);
    callback = f;
    StateMachine = fsm;
    NewState = nS;
}

void StateCollisionBox::colliderStatePoll(Marple *marple)
{ // TODO: make real-time?
    for (StateCollisionBox *collider : stateColliders)
    {
        if (checkCollision(marple, collider))
        {
            if (collider->progress <= (collider->progress_secs * 60) - 1)
            {
                collider->progress++;
            }
            else
            {
                collider->callback(collider->StateMachine, collider->NewState); // if progress bar limit reached, run specific callback
                collider->progress = 0;
            }
        }
        else
        {
            collider->progress = 0;
        }
        collider->bar->setDiameter(collider->progress * ((float)collider->width / (float)(collider->progress_secs * 60)));
    }
}

MapCollisionBox::MapCollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*f)(MapMenu *, int), bool loading_bar, MapMenu *mm, int ID) : CollisionBox{x_pos, y_pos, w, h, trigger_time, NULL, loading_bar}
{
    callback = f;
    mmState = mm;
    mapID = ID;
}


int Button::getWidth() {
    return width;
}

LoadingBar *CollisionBox::getBar() {
    return bar;
}

int Button::getHeight() {
    return height;
}

char *Button::getPath() {
    return path;
}

float Button::getBarWidth() {
    return box->getBar()->getDiameter();
}

StateButton::StateButton(int xp, int yp, int w, int h, char *p, void(*f)(MarpleTiltMachine*, GameState*), MarpleTiltMachine *fsm, GameState *ns, int t) : Button{xp, yp, w, h, p} {
    
    box = new StateCollisionBox(xp, yp, w, h, t, f, true, fsm, ns);
}   