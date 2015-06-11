#ifndef FACILITIES_H
#define FACILITIES_H

#include "button.h"
#include "base.h"
#include <core/level.h>
#include <memory>
#include <map>

using std::map;

class Texture;

class Facilities : public Level
{
public:
    Facilities(const string& next = "");

private:
    typedef enum { CHAT, MILITARY, PSIONIC, TECH } Screen;

    Screen m_screen;
    map<ObjectID, Button*> m_buttons;

    bool on_message(Object *sender, MessageID id, Parameters p);
    void draw_self();
    void create_buttons();
    void change_buttons();
    void change_to_chat();
    void change_to_military();
    void change_to_psionic();
    void change_to_tech();
};

#endif