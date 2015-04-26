#include "button.h"
#include "environment.h"
#include "image.h"
#include "settings.h"
#include "resourcesmanager.h"


Settings::Settings(const string& next, const string& image)
    : Level("", next), m_image(nullptr)
{
    env = Environment::get_instance();
    shared_ptr<Resource> r = env->resources_manager->get(Resource::IMAGE,
        image);
    m_image = dynamic_cast<Image *>(r.get());
}

void
Settings::draw_self()
{
    env->canvas->clear();
    env->canvas->draw(m_image, 0, 0);
}

void 
Settings::update_coodirnates_buttons()
{
    double scale = env->canvas->scale();
    m_x_back = scale * X_BACK;
    m_y_back = scale * Y_BACK;
    m_w_back_button = scale * W_BACK_BUTTON;
    m_h_back_button = scale * H_BACK_BUTTON;
    m_x_up_resolution = scale * X_UP_RESOLUTION;
    m_y_up_resolution = scale * Y_UP_RESOLUTION;
    m_x_down_resolution = scale * X_DOWN_RESOLUTION;
    m_y_down_resolution = scale * Y_DOWN_RESOLUTION;
    m_w_resolution_button = scale * W_RESOLUTION_BUTTON;
    m_h_resolution_button = scale * H_RESOLUTION_BUTTON;
}

bool
Settings::execute_action(const int x, const int y)
{
    update_coodirnates_buttons();
    
    Button back_button(m_x_back, m_y_back, m_w_back_button, m_h_back_button);
    Button up_resolution_button(m_x_up_resolution, m_y_up_resolution, m_w_resolution_button, m_h_resolution_button);
    Button down_resolution_button(m_x_down_resolution, m_y_down_resolution, m_w_resolution_button, m_h_resolution_button);

    if (back_button.is_clicked(x, y))
    {
        m_next = "menu";
        m_done = true;
    }
    else if (up_resolution_button.is_clicked(x, y))
    {
        int w, h;
        w = env->video->resolution().first;
        h = env->video->resolution().second;
        
        if(w < MAX_RESOLUTION)
        {
            w *= SCALE;
            h *= SCALE;   
            env->video->set_resolution(w, h);
            env->canvas->set_scale(SCALE);
        }

    }
    else if (down_resolution_button.is_clicked(x, y))
    {
        int w, h;
        w = env->video->resolution().first;
        h = env->video->resolution().second;
        
        if(w > MIN_RESOLUTION)
        {
            w /= SCALE;
            h /= SCALE;
            env->video->set_resolution(w, h);
            env->canvas->set_scale(1/SCALE);
        }
    }

    return false;
}
