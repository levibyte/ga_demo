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
        JGeneticAlgoImpl(int initial_fitness){
	  
	}
	
	virtual void make_new_generation()=0;
        virtual void calc_fitnesses()=0;
        virtual void create_first_generation()=0;
        virtual bool is_done(int)=0;
        virtual void add_gen(const T&)=0;
        virtual int get_fitness(const T&)=0;
        
        virtual T make_crossover(const T&, const T&)=0;
        virtual T make_mutation(T&)=0;
        virtual void post_process()=0;
        virtual T get_winner() = 0;
};

  
    
template<typename T>    
class JGeneticAlgo {
    public:  
        JGeneticAlgo(JGeneticAlgoImpl<T>* i):m_impl(i) {}
        
        void run() {
              //std::cout << 
	      //std::cout << "creating initial generation" << std::endl;
	      //std::cout << m_impl << std::endl;
              m_impl->create_first_generation();
              //std::cout << "calc fitness..." << std::endl;
              m_impl->calc_fitnesses();
              //std::cout << std::endl;
	      //std::cout << std::endl;
            //*
              int gen_num=0;
              while ( ! m_impl->is_done(gen_num) ) {
                  std::cout << std::endl;
		  std::cout << "new generation " << gen_num << std::endl;
                  m_impl->make_new_generation();
                  
		  std::cout << std::endl;
		  std::cout << "calc fitenss... " << std::endl;
                  m_impl->calc_fitnesses();
                  gen_num++;
              }
		/**/
			  
              m_impl->post_process();
          }
        
     private:  
        JGeneticAlgoImpl<T>* m_impl;
};



template<typename T>
class JGeneticAlgoDefaultImpl: public JGeneticAlgoImpl<T> {

public:
      JGeneticAlgoDefaultImpl(int initial_fitness):JGeneticAlgoImpl<T>(initial_fitness),m_max_generations(1000),m_perfect_fitness(0),m_current_fitness(initial_fitness) {
          
          m_population_size = 100;
          //m_population.resize(m_population_size);
          
          m_elit_survivors_num = m_population_size/10;
	  //std::cout << m_current_fitness << std::endl;
      }
      
public:
  
      void add_gen(const T& m) {
          //assert(0);
          //fixme assert not to overdo.
          //std::cout << "---Add new gen" << std::endl;
          m_population.push_back(m);
      }
      
      void calc_fitnesses() {
		std::cout << "*********************************************MIN FITNESS" << m_current_fitness << std::endl;
        std::cout << "CALC FITNES FOR POPULATION SIZE  " << m_population.size() << std::endl;
        int tmp;
		for(int i=0; i<m_population.size(); i++ ) {
          tmp = get_fitness(m_population[i]);
          m_gen2fitness[&m_population[i]] = tmp;
          m_fitness2gen[tmp]=&m_population[i];
          //fixme need comparator
          if ( tmp < m_current_fitness ) { 
            m_current_fitness = tmp;
            //m_winner = m_population[i];
			std::cout << "         Found fitness:" << m_current_fitness << std::endl;
			std::cout << "         !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Found fitness:" << get_fitness(m_winner) << std::endl;
			//assert(0);
		
          }
        }
		 m_winner = *m_fitness2gen[m_current_fitness];
		std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!MIN FITNESS" << m_current_fitness << std::endl;
		//std::cout << "ELEN JANIK" <<  get_fitness(m_winner) << std::endl;
		get_winner();
      }

      bool is_done(int i) {
          return ( i > m_max_generations || m_current_fitness <= m_perfect_fitness );
      }

      void make_selection() {
          make_selection_dflt();
      }
      
      void make_new_generation() {
          std::cout << "  Processing selection..." << std::endl;
          make_selection_dflt();
          
          std::cout << "  Processing crossover..." << std::endl;
          make_crossover_dflt();
          
          std::cout << "  Processing mutation..." << std::endl;
          make_mutation_dflt();
      }


      void delete_generation() {
            std::cout << "            ! deleting all generation" << std::endl;
            m_population.clear();
            //m_fitness2gen.clear();
            m_gen2fitness.clear();
      }

///////
      void make_selection_dflt() {
         
          typename std::map<int,T*>::iterator it = m_fitness2gen.begin();
          typename std::vector<T>::iterator it2;
          //assert(m_fitness2gen)
          std::vector<T> tmp;  
          for( int i=0; i<m_elit_survivors_num && it!=m_fitness2gen.end() ; i++, it++) {
            std::cout << "            !elit no: " << i << ", Fitness = " << (*it).first<< std::endl;
            tmp.push_back(*it->second);
          }
         
          delete_generation();
          
          std::cout << "            !adding remainging " << tmp.size() << " " << m_population.size() << std::endl;
          //m_population.resize(m_elit_survivors_num);
          
          
          for( int i=0; i<m_elit_survivors_num; i++) {
            //std::cout << "g" << i << std::endl;
            m_population.push_back(tmp[i]);
            
          }
          
          std::cout << "ENDOFTHE DAY: " << m_population.size() << std::endl;
          //return tmp;
          //std::erase(m_population.begin(),m_population.begin())
      }

      void make_crossover_dflt() {
            //std::vector<T> t = make_crossover(m_population[0],m_population[1]);
            //for( int i=0; i<t.size(); i++) m_population.push_back(t[i]);
            
            //m_population.push_back(make_crossover(m_population[0],m_population[1]));
            //m_population.push_back(make_crossover(*m_fitness2gen.begin()->second,*(m_fitness2gen.begin()++)->second));
           std::vector<T> tmp;  
            for( int i=0; i<m_population.size(); i++) {
              for( int j=0; j<m_population.size(); j++) {
                tmp.push_back(make_crossover(m_population[i],m_population[j]));
                if ( tmp.size() > m_population.size() ) break;
              }
              if ( tmp.size() > m_population.size() ) break;
            }
           
            ///m_population.resize(m_popu) 
            //td::cout << tmp.size() << std::endl;
            //assert(0);
            for( int i=0; i<tmp.size(); i++) m_population.push_back(tmp[i]);
            //std::cout << m_population.size() << std::endl;
            //assert(0);
                 
      }
      
      
      void make_mutation_dflt() {
          int diff =  m_population_size-m_elit_survivors_num-1;
          std::cout << "DIFF " << diff << std::endl;
          std::cout << "SIZE " << m_population.size()<< std::endl;
         
          //assert(0);
          for( int i=m_elit_survivors_num; i<diff + m_elit_survivors_num + 1; i++) {
            //std::cout << i << " NUMBERRRRRRR m_population[" << i-1 << "]" << std::endl;
              m_population.push_back(make_mutation(m_population[i-1]));
            //make_mutation(*m_fitness2gen.begin()->second);
          }
          
          std::cout << "AFTER SIZE " << m_population.size()<< std::endl;
          //assert(m_population.size() == m_population_size );
            
      }
      
      
      int get_fitness(const T&) {
            assert(0&&"default implementation has no fitness function");
      }
      
      
     T make_crossover(const T&, const T&) {
          // select good and...
          //std::max()
      }

      T make_mutation(T& t) {
          // sslec some and change
          //std::max()
      }

      void create_first_generation() {
          assert(0&&"default implementation can't create first generation ");
      }
      
      
      void post_process() {
	  assert(0);
        
      }

  
      T get_winner() {
		std::cout << "CALLED WINNER: "  << get_fitness(m_winner) << std::endl;
			//m_winner
          return m_winner;
	  //std::cout << "----------" << m_fitness2gen.size() << std::endl;
	  //std::cout << m_fitness2gen.begin()->first << std::endl;
          //return *m_fitness2gen.begin()->second;
        
      }
      
      int get_population_size() {
          return m_population_size;
      }

private:
      T m_winner;
      
      std::vector<T> m_population;
      std::map<T*,int> m_gen2fitness;
      std::map<int,T*> m_fitness2gen;
   
      int m_max_generations;
      int m_perfect_fitness;
      
      int m_current_fitness;
      
      int m_elit_survivors_num;
      int m_population_size;
};



#endif