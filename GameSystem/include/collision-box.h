#pragma once

#include <vector>

class Marple;
class LoadingBar;

class CollisionBox
{
protected:
    int x, y;
    int width;
    int height;
    int progress;
    int progress_secs;
    void (*callback)(Marple *marple);
    bool trigger_type; // trigger_type = true : touch trigger | trigger_type = false : proximity trigger
    static bool checkCollisionTouch(Marple *marple, CollisionBox *collider);
    static bool checkCollisionProx(Marple *marple, CollisionBox *collider, double threshold = 1);
    static std::vector<CollisionBox *> Colliders; // TODO: make an Object instead? or keep separate track
public:
    CollisionBox(void){};
    CollisionBox(int x, int y, int w, int h, int progress_secs, void (*func)(Marple *marple), bool loading_bar = true, bool touch_trig = true);
    
    static void colliderPoll(Marple *marple);
    LoadingBar *getBar();
    LoadingBar *bar;

    static void clear();

    int getWidth();
    int getHeight();
    int getX();
    int getY();
};