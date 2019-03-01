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
#include "../renderer/rendering_controller_impl_base.h"
	
class JManager 
{
  
  public:  
   JManager(LeRenderingControllerImplBase* r);
   
    void set_data(std::vector< std::vector<JInstance*> > r) {
        m_layers = r;
    }
      
    class ay_qez_ban 
    {
        public:
            ay_qez_ban(int v):m_v(v) {}
      
            bool operator()(int a) {
                return (a > m_v);
            }
            
            int m_v;
    };

    //int get_fitness(const std::vector<std::vector<JInstance*> >& m);
 
    std::pair<int,int> get_id_by_inst(JInstance* inst);
    //std::vector<int> get_real_vect(const std::vector<JInstance*>& iv);
    std::multiset<int> get_real_vect(const std::vector<JInstance*>& iv, bool dbg);
    void print_dbg();
    int calc_intersections();
    int calc_intersection(int i);
    int count_intersections(std::multiset<int>& seen, const std::vector<JInstance*>& v1);
    std::vector<JInstance*> get_insts(JInstance* i);

    void add_change();
    bool permute_two_rand_instances_in_layer(int ln);
    void undo_permute();
    void init_data();
    
    void draw();
    
    std::vector< std::vector<JInstance*> >& get_data() { return m_layers; }

private:
    std::vector< std::pair<JInstance*,JInstance*> > m_permuted;
    std::vector< std::pair< std::pair<int,int>, int > > m_fixme_permuted;

    std::multimap<JInstance*,JInstance*> m_connections;
    std::vector< std::vector<JInstance*> > m_layers;
    
    int m_max_per_clm;
    int m_layers_cnt;
    int m_conn_density;
    
    int m_start_res;
    int m_last_res;

    int m_offsset1;
    int m_offsset2;
    int m_radius;
    
    LeRenderingControllerImplBase* m_renderer;
        
};

#endif
