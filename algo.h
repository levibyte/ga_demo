#ifndef algo_h
#define algo_h

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include <map>

   
template<typename T>    
class JGeneticAlgoImpl {
  public:
        virtual void make_new_generation()=0;
        virtual void calc_fitnesses()=0;
        virtual void create_first_generation()=0;
        virtual bool is_done(int)=0;
        virtual void add_gen(T&) {} ;
};

  
    
template<typename T>    
class JGeneticAlgo {
    public:  
        JGeneticAlgo(JGeneticAlgoImpl<T>* i):m_impl(i) {}
        
        void run() {
              m_impl->create_first_generation();
              m_impl->calc_fitnesses();
              
              int i=0;
              while ( ! m_impl->is_done(i) ) {
                  //m_impl->make_new_generation();
                  m_impl->calc_fitnesses();
                  i++;
              }
              
          }
        
  private:  
     JGeneticAlgoImpl<T>* m_impl;
};



template<typename T>
class JGeneticAlgoDefaultImpl: public JGeneticAlgoImpl<T> {

public:
      JGeneticAlgoDefaultImpl():m_max_generations(1000),m_perfect_fitness(0),m_current_fitness(9999999) {
        
      }
      
public:
  
      virtual void add_gen(const T& m) {
          m_population.push_back(m);
      }
      
      void calc_fitnesses() {
        for(int i=0; i<m_population.size(); i++ ) {
          int tmp = get_fitness(m_population[i]);
          m_gen2fitness[&m_population[i]] = tmp;
          m_fitness2gen[tmp]=&m_population[i];
          //fixme need comparator
          if ( tmp < m_current_fitness ) m_current_fitness = tmp;
        }
      }

      bool is_done(int i) {
        return ( i > m_max_generations || m_current_fitness <= m_perfect_fitness );
      }
    
      void make_selection() {
          typename std::map<int,T*>::reverse_iterator it = m_fitness2gen.rbegin();
          //assert(m_fitness2gen)
          std::vector<T> tmp;  
          for( int i=0; i<3 && it!=m_fitness2gen.rend() ; i++, it++) tmp.push_back(*it->second);
          m_population.clear();
          m_fitness2gen.clear();
          typename std::vector<T>::iterator it2;
         
          for( int i=0; i<3; i++) m_population.push_back(tmp[i]);
          //std::erase(m_population.begin(),m_population.begin())
      }

      void make_new_generation() {
          make_selection();
          //make_crossover();
          //make_mutation();
          //m_logic->add
      }
      
      void make_crossover() {
          // select good and...
          //std::max()
      }

      void make_mutation() {
          // sslec some and change
          //std::max()
      }

      void create_first_generation() {
          //m_current_population
      }
      
      int get_fitness(const T&) {
         assert(0&&"default implementation has no fitness function");
      }
      
private:
      std::vector<T> m_population;
      std::map<T*,int> m_gen2fitness;
      std::map<int,T*> m_fitness2gen;
   
      int m_max_generations;
      int m_perfect_fitness;
      
      int m_current_fitness;
};



#endif