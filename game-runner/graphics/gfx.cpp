#include "gfx.h"
#include <iostream>

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

void Marple::returnHome() {
    std::cout << "setting position\n";
    setPos({home->getX(), home->getY()});
}

void Marple::returnWrapper(Marple * m) {
    m->returnHome();
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

CollisionBox::CollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*func)(Marple * marple), bool loading_bar, bool touch_trig) { //
    Colliders.push_back(this);
    x = x_pos;
    y = y_pos;
    width = w;
    height = h;
    progress = 0;
    callback = func;
    progress_secs = trigger_time;
    trigger_type = touch_trig;
    if (loading_bar) {
        bar = new LoadingBar(x, y, height);
    }
    else {
        bar = nullptr;
    }
}

bool CollisionBox::checkCollisionTouch(Marple *marple, CollisionBox *collider) {
    int marp_x = (int)std::round(marple->getPos()[0]), marp_y = (int)std::round(marple->getPos()[1]), marp_d = marple->getDiameter();
    if ((((collider->x <= marp_x) && (marp_x <= collider->x + collider->width)) ||
         ((collider->x <= marp_x + marp_d) && (marp_x + marp_d <= collider->x + collider->width)))
        &&
        (((collider->y <= marp_y) && (marp_y <= collider->y + collider->height)) ||
         ((collider->y <= marp_y + marp_d) && (marp_y + marp_d <= collider->y + collider->height)))) {
        return true;
    }
    return false; //TODO: look into destructor and removing from vectors
}

bool CollisionBox::checkCollisionProx(Marple *marple, CollisionBox *collider, double threshold) {
    int marp_d = marple->getDiameter();
    auto marp_x = marple->getPos()[0], marp_y = marple->getPos()[1];
    auto col_x = collider->getX(), col_y = collider->getY(),
    col_w = collider->getWidth(), col_h = collider->getHeight();
    double centre_x = col_x + col_w/2, centre_y = col_y + col_h/2;
    double m_centre_x = marp_x + marp_d/2, m_centre_y = marp_y + marp_d/2;
    double dist = sqrt(pow((centre_x - m_centre_x),2) + pow((centre_y-m_centre_y),2)); // think abs is not necessary
    if (dist <= threshold) {
        return true;
    }
    return false;
}

void CollisionBox::colliderPoll(Marple *marple) { //TODO: make real-time?
    for (CollisionBox *collider: Colliders) {
        if ((checkCollisionTouch(marple, collider) && collider->trigger_type) or //check based on which trigger type
            (checkCollisionProx(marple, collider) && !collider->trigger_type )) {
            if (collider->progress <= (collider->progress_secs * 60) - 1) {
                collider->progress++;
            } else {
                collider->callback(marple); // if progress bar limit reached, run specific callback
                collider->progress = 0;
            }
        } else {
            collider->progress = 0;
        }
        if (collider->bar){
            collider->bar->setDiameter(collider->progress * ((float)collider->width/(float)(collider->progress_secs * 60)));
        }
    }
}

// -- //

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
        if (checkCollisionTouch(marple, collider))
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

// -- //

MapCollisionBox::MapCollisionBox(int x_pos, int y_pos, int w, int h, int trigger_time, void (*f)(MapMenu *, int), bool loading_bar, MapMenu *mm, int ID) : CollisionBox{x_pos, y_pos, w, h, trigger_time, NULL, loading_bar}
{
    mapColliders.push_back(this);
    callback = f;
    mmState = mm;
    mapID = ID;
}

void MapCollisionBox::colliderMapPoll(Marple *marple)
{ // TODO: make real-time?
    for (MapCollisionBox *collider : mapColliders)
    {
        if (checkCollision(marple, collider))
        {
            if (collider->progress <= (collider->progress_secs * 60) - 1)
            {
                collider->progress++;
            }
            else
            {
                collider->callback(collider->mmState, collider->mapID); // if progress bar limit reached, run specific callback
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

bool MapCollisionBox::checkCollision(Marple *marple, MapCollisionBox *collider)
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

// -- //

int Button::getWidth() {
    return width;
}

LoadingBar *CollisionBox::getBar() {
    if (bar){
        return bar;
    }
    return nullptr;
}

int CollisionBox::getWidth() {
    return width;
}

int CollisionBox::getHeight() {
    return height;
}

int CollisionBox::getX() {
    return x;
}

int CollisionBox::getY() {
    return y;
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

float Home::getX() {
    return getPos()[0];
}

float Home::getY() {
    return getPos()[1];
}

MapButton::MapButton(int xp, int yp, int w, int h, char *p, void (*f)(MapMenu *, int), MapMenu *mm, int mID, int t) : Button{xp, yp, w, h, p}
{

    box = new MapCollisionBox(xp, yp, w, h, t, f, true, mm, mID);
}
