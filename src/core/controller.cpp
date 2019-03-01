#include "controller.h"
#include "genalgo_impl_custom.h"

void Controller::on_key_press(unsigned int) {
    delete m_current_system;
    //m_current_system = new JManager(this);
    get_new_state();
    get_new_state();
    get_new_state();
    get_new_state();
    get_new_state();
    
    m_current_system = get_new_state();
    
    /*
    JManager* z = new JManager(this);
    std::cout << " !!!new state " << z << " fitness " << z->calc_intersections() << std::endl;

    z->add_change();
    std::cout << " !!!new state " << z << " fitness " << z->calc_intersections() << std::endl;

    z->add_change();
    std::cout << " !!!new state " << z << " fitness " << z->calc_intersections() << std::endl;

    z->add_change();
    std::cout << " !!!new state " << z << " fitness " << z->calc_intersections() << std::endl;

    m_current_system = z;
    //m_current_system->add_change();
    //m_current_system->calc_intersections();
    */
}

void Controller::on_mouse_click(unsigned int) {
    if ( m_is_running ) 
        return;
    
    m_is_running = true;
    m_algo->run();
}

void Controller::on_draw_event() {
    //TODO: run if only done
    m_current_system->draw();
}
        
Controller::Controller() {
    m_is_running = false;
    m_current_system = new JManager(this);
    m_algo = new JGeneticAlgo<MyValType>(new JGeneticAlgoImpl<MyValType>(9999,this));
}
    
/*
void Controller::add_change(MyValType* d) {
    d->add_change();
}
*/

int Controller::get_fitness(const MyValType & d){
    return d->calc_intersections();
}

void Controller::set_winner(MyValType d) {
    m_current_system = d;
}

MyValType Controller::get_current_winner() {
    return m_current_system;
}   

MyValType Controller::get_new_state() {
    JManager* z = new JManager(this);
    z->add_change();
    std::cout << " new state " << z << " fitness " << z->calc_intersections() << std::endl;
    return z;
}
