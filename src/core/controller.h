#ifndef my_controller_h
#define my_controller_h

#include "genalgo.h"
#include "logic.h"
#include "instance.h"

#include "../renderer/sdl_renderer.h"

#include <vector>
#include <cassert>

class Controller: public LeSdlRenderer
{
    //typedef std::vector<std::vector<JInstance*> > MyValType;
    typedef JManager* MyValType;

    JGeneticAlgo<MyValType>* m_algo;
    JManager* m_current_system;
    std::vector<JManager*> m_states;
    bool m_is_running;
    
    virtual void on_key_press(unsigned int);    
    virtual void on_mouse_click(unsigned int);
    virtual void on_draw_event();
            
public:
    Controller();
    
    int get_fitness(const MyValType & d);
    MyValType get_current_winner();
    MyValType get_new_state();
    void set_winner(MyValType);
    
    //get()

};

#endif
