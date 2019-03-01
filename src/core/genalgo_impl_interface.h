 
#ifndef algo_impl_interface
#define algo_impl_interface
 
template<typename T>    
class JGeneticAlgoImplInterface 
{
  public:
    JGeneticAlgoImplInterface(int initial_fitness) {
        
    }
    
    virtual void make_new_generation()=0;
    virtual void calc_fitnesses()=0;
    virtual void create_first_generation()=0;
    virtual void create_or_set_inital_state(const T&)=0;
    virtual bool is_done(int)=0;
    virtual void add_gen(const T&)=0;
    virtual int get_fitness(const T&)=0;
    
    virtual T make_crossover(const T&, const T&)=0;
    virtual T make_mutation(T&)=0;
    virtual void post_process()=0;
    virtual T get_winner() = 0;
};

#endif
