#ifndef COLONY_H
#define COLONY_H

#include "button.h"
#include <core/environment.h>
#include <core/listener.h>
#include <core/object.h>
#include <core/text.h>
#include <core/texture.h>
#include <memory>

class Colony : public Object
{
public:
    Colony(Object *parent = nullptr, ObjectID id = "");

    int data() const;
    int matter() const;
    int energy() const;

    void set_data(int data);
    void set_matter(int matter);
    void set_energy(int energy);

private:
    shared_ptr<Texture> m_right_bracket;
    shared_ptr<Texture> m_colony;
    shared_ptr<Texture> m_tower_img;
    shared_ptr<Texture> m_planet_img;
    shared_ptr<Texture> m_left_bracket;
    shared_ptr<Texture> m_resources;

    Button *m_center_bracket;
    Button *m_tower;
    Button *m_planet;

    int m_data;
    int m_matter;
    int m_energy;

    shared_ptr<Settings> m_settings;

    bool on_message(Object *sender, MessageID id, Parameters p);
    void draw_self();

    template<typename T>
    void write(const string& attr, const T& value);
};

#endif
