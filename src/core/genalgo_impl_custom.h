#ifndef algo_impl_custom
#define algo_impl_custom

#include "genalgo_impl_default.h"
#include "instance.h"
#include "controller.h"
#include "logic.h"

#include <vector>

//Particular implementation details for MyValType type

typedef JManager* MyValType;

//typedef std::vector<std::vector<JInstance*> > MyValType;
typedef std::vector<JInstance*> PCLM; 
typedef std::vector<PCLM> JGen;

//template<typename T>
//class JGeneticAlgoImplZ: public JGeneticAlgoDefaultImpl<T> {};

//template<>
//class JGeneticAlgoImpl : public <MyValType>
template<typename T>
class JGeneticAlgoImpl: public JGeneticAlgoDefaultImpl<T>
{

public:
    JGeneticAlgoImpl(int initial_fitness, Controller* logic) :JGeneticAlgoDefaultImpl<T>(initial_fitness) {
        m_controller = logic; 
    }

public:
    int get_fitness(const T& t) {
        return m_controller->get_fitness(t);
    }
    
    T make_crossover(const T& g0,const T& g1) {
        //return g0;
        //T t = new JManager;
        //g0->set_data(merge(g0->get_data(),g1->get_data()));
        return g0;
    }

    T make_mutation(T& g) {
        //return m_controller->add_change(g);
    }
    
    void post_process() {
        m_controller->set_winner(JGeneticAlgoDefaultImpl<T>::get_winner());
    }
    
    void create_first_generation() {            
        JGeneticAlgoDefaultImpl<T>::create_or_set_inital_state(m_controller->get_current_winner());
        for(int i=0;i<JGeneticAlgoDefaultImpl<T>::get_population_size();i++) 
            JGeneticAlgoDefaultImpl<T>::add_gen(m_controller->get_new_state()); 
    }

private:
    JGen merge(const JGen& g0,const JGen& g1) {
        JGen z;
        for(int i=0;i<g0.size();i++) z.push_back(merge_columns(g0[i],g1[i]));
        
        return z; 
    }

    PCLM merge_columns(const PCLM& f, const PCLM& s) {
        PCLM z;
        for(int i=0;i<f.size()/2;i++) z.push_back(f[i]);
        for(int i=0;i<s.size();i++) 
            if ( std::find(z.begin(),z.end(),s[i]) == z.end() ) 
            z.push_back(s[i]);
        return z;
    }
        
private:
    Controller* m_controller;
};

#endif

