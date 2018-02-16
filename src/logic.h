#ifndef logic_h
#define logic_h


#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <ctime>

#include <iostream>
#include <algorithm>
#include <sstream>
#include <functional>

#include "instance.h"
#include "algo.h"
#include "renderer.h"
	
class JManager {
  
  public:  
   
	 class ay_qez_ban {
	      public:
		  ay_qez_ban(int v):m_v(v) {}
	      public:
		    bool operator()(int a) {
			return (a > m_v);
		    }
		    
		    int m_v;
	   };
    
	JManager(JRenderer* r):m_renderer(r),m_layers_cnt(9),m_max_per_clm(9),m_conn_density(1),m_last_res(0) {
	  
                    m_offsset1=50;
          m_offsset2=10;
          m_radius=5;

          
	  m_layers.resize(m_layers_cnt);
	  srand(time(0));
	  init_data();
          
          m_start_res = calc_intersections();
	  
	  //m_last_fitness;
          //print_dbg();
	  draw();
          std::cout << "BEGIN: " <<  m_start_res << std::endl;
		  m_last_winner = m_layers; 
	}

	    
        void action();
	void revert();
        int change();
	
        int get_fitness(const std::vector<std::vector<JInstance*> >& m);
        void set_winner(const std::vector<std::vector<JInstance*> >& m);
        std::vector<std::vector<JInstance*> > add_change(std::vector<std::vector<JInstance*> > m);
        std::vector<std::vector<JInstance*> > get_new_state();
        std::vector<std::vector<JInstance*> > get_current_winner();
        std::pair<int,int> get_id_by_inst(JInstance* inst);
        //std::vector<int> get_real_vect(const std::vector<JInstance*>& iv);
        std::multiset<int> get_real_vect(const std::vector<JInstance*>& iv, bool dbg);
        void print_dbg();
        int calc_intersections();
        int calc_intersection(int i);
        int count_intersections(std::multiset<int>& seen, const std::vector<JInstance*>& v1);
        std::vector<JInstance*> get_insts(JInstance* i);
        void do_and_draw();
        void add_change();
        bool permute_two_rand_instances_in_layer(int ln);
        void undo_permute();
	void init_data();
	void draw();

  private:
	std::vector< std::pair<JInstance*,JInstance*> > m_permuted;
        std::vector< std::pair< std::pair<int,int>, int > > m_fixme_permuted;
        
        std::vector< std::vector<JInstance*> > m_layers;
		std::vector<std::vector<JInstance*> > m_last_winner;
	std::multimap<JInstance*,JInstance*> m_connections;
	
	int m_max_per_clm;
	int m_layers_cnt;
	int m_conn_density;
        
	int m_start_res;
	int m_last_res;

	JRenderer* m_renderer;
        
        
               
        int m_offsset1;
        int m_offsset2;
        int m_radius;
        
};

template<typename T>
class JGeneticAlgoMyImpl: public JGeneticAlgoDefaultImpl<T> 
{

    typedef std::vector<JInstance*> PCLM; 
    typedef std::vector<PCLM> JGen;

    public:
          JGeneticAlgoMyImpl(int initial_fitness,JManager* logic):JGeneticAlgoDefaultImpl<T>(initial_fitness)
          {
			m_logic = logic; 
	  }


    public:
          int get_fitness(const T& f) {
              return m_logic->get_fitness(f);
          }
          
          JGen make_crossover(const JGen& g0,const JGen& g1) {
              return merge(g0,g1);
          }

          JGen make_mutation(JGen& g) {
             return m_logic->add_change(g);
          }
          
          void post_process() {
            m_logic->set_winner(JGeneticAlgoDefaultImpl<T>::get_winner());
          }
          
          void create_first_generation() {            
            //assert(0);
			JGeneticAlgoDefaultImpl<T>::create_or_set_inital_state(m_logic->get_current_winner());
			for(int i=0;i<JGeneticAlgoDefaultImpl<T>::get_population_size();i++) 
              JGeneticAlgoDefaultImpl<T>::add_gen(m_logic->get_new_state()); 
          }

    private:
          JGen merge(const JGen& g0,const JGen& g1) {
              JGen z;
              for(int i=0;i<g0.size();i++) z.push_back(merge_columns(g0[i],g1[i]));
              
              return z; 
          }

          PCLM merge_columns(const PCLM& f, const PCLM& s) {
              PCLM z;
			  //if (f.size()
              //std::cout << f.size() << std::endl;
		      
              for(int i=0;i<f.size()/2;i++) z.push_back(f[i]);
                for(int i=0;i<s.size();i++) 
                  if ( std::find(z.begin(),z.end(),s[i]) == z.end() ) 
                    z.push_back(s[i]);
              return z;
          }
          
    public:
          JManager* m_logic;
};



#endif