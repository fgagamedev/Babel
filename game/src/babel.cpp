#include "babel.h"
#include "environment.h"
#include "frontend.h"
#include "menu.h"

Babel::Babel()
    : Game("classification")
{
}

void
Babel::init(const string& title, int w, int h) throw (Exception)
{
    Environment *env = Environment::get_instance();

    env->video->set_resolution(w, h);
    env->video->set_window_name(title);

    env->events_manager->register_system_event_listener(this);
    env->events_manager->register_keyboard_event_listener(this);
    env->events_manager->register_mouse_button_event_listener(this);

    m_level = load_level();
}

void
Babel::run()
{
    while (m_level and not m_done)
    {
        unsigned long now = update_timestep();
        
        env->events_manager->dispatch_pending_events();

        m_level->update(now);
        m_level->draw();

        update_screen();
        delay(1);

        if (m_level->is_done())
        {
            m_id = m_level->next();
            delete m_level;
            m_level = load_level();
        }
    }
}

Level *
Babel::load_level()
{
    if(m_id == "menu")
    {
        return load_menu();
    }
    else
    {
        return load_frontend(m_id);
    }
}

Level *
Babel::load_frontend(const string& id)
{
    if (id == "classification")
    {
        return new FrontEnd("game_logo", "res/images/classification.png");
    }
    else if (id == "game_logo")
    {
        return new FrontEnd("sdl_logo", "res/images/game_logo.png");
    }
    else if (id == "sdl_logo")
    {
        return new FrontEnd("menu", "res/images/sdl_logo.png");
    }

    return nullptr;
}

Level *
Babel::load_menu()
{
    return new Menu("", "res/images/menu.png");
}

bool 
Babel::onMouseButtonEvent(const MouseButtonEvent& event)
{
    if(event.action() == MouseButtonEvent::UP and
        event.button() == MouseButtonEvent::LEFT)
    {
        if(m_id == "menu")
        {
            Menu * menu = dynamic_cast<Menu *>(m_level);
            menu->execute_action(event.x(), event.y());
            return true;
        }
    }
    return false;
}