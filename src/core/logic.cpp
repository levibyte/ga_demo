#include "../renderer/rendering_controller_impl_base.h"

#include "logic.h"
#include "instance.h" 

#include <set>
#include <map>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <functional>

JManager::JManager(LeRenderingControllerImplBase* r):m_renderer(r),m_layers_cnt(10),m_max_per_clm(10),m_conn_density(1),m_last_res(0) {
    
    m_offsset1=50;
    m_offsset2=10;
    m_radius=5;

    
    m_layers.resize(m_layers_cnt);
    //srand(time(0));
    init_data();
    
    //m_start_res = calc_intersections();
    
    //m_last_winner = m_layers; 
}

/*    
int JManager::get_fitness(const std::vector<std::vector<JInstance*> >& m) {
    m_layers = m;
    return calc_intersections();
}

std::vector<std::vector<JInstance*> > JManager::add_change(std::vector<std::vector<JInstance*> > m) {
    m_layers = m;
    add_change();
    return m_layers;
}

std::vector<std::vector<JInstance*> > JManager::get_new_state() {
    add_change();
    return m_layers;
    //return calc_intersections();
}
*/
     
/*
void JManager::revert() {
    undo_permute();
    //return calc_intersections(); 
}

int JManager::change() {
    add_change();
    return calc_intersections(); 
}
*/

std::multiset<int> JManager::get_real_vect(const std::vector<JInstance*>& iv, bool dbg=true) {
    std::multiset<int> ov;
    if (iv.empty()) return ov;
    assert(iv.size());
    for(int i=0;i<iv.size();i++) {
        if(dbg)  std::cout << "               name:" << iv[i]->get_name() << " pos:" << iv[i]->get_rownum() << std::endl;
        ov.insert(iv[i]->get_rownum());
    }
    //if (dbg) std::cout << std::endl;
    
    return ov;
}

int JManager::calc_intersections() {
    int r = 0;
    for(unsigned int i=0; i<m_layers_cnt-1; i++ ) r = r + calc_intersection(i);
    
    std::cout << "FI: " << r << std::endl;
    std::cout << "************************\n\n" << std::endl;
    m_last_res = r;
    return r;
}

int JManager::calc_intersection(int i) {
    std::multiset<int> seen;
    int count = 0;
    
    std::multiset<int> real_v = get_real_vect(m_layers[i]);

    //std::cout << "\n\n\n\n****intersections for " << i << "->" << i + 1 << "\n" ;

    for (unsigned int j=0; j<real_v.size(); j++ ) {
    // std::cout << "  ." << i << " "  << j <<" looking by the name of" << m_layers[i][j]->get_name() << std::endl;
        count = count + count_intersections(seen,get_insts(m_layers[i][j]));
    }
    //std::cout << "intersections for " << i << "->" << i + 1 << " ***"<< count  << "*** \n \n" ;
    return count;
}


int JManager::count_intersections(std::multiset<int>& seen, const std::vector<JInstance*>& v1) {
        std::multiset<int> v = get_real_vect(v1,true);
    
        int res = 0;
        for(std::multiset<int>::const_iterator i=v.begin();i!=v.end();++i) {
        
        res = res + std::count_if(seen.begin(), seen.end(), ay_qez_ban(*i));
        seen.insert(*i);
        }

    return res;
}


//FIXME!
std::vector<JInstance*> JManager::get_insts(JInstance* i) {
        std::vector<JInstance*> v;//, v2;
        //std::cout << "      " << i->get_name() << " get_inst:" << std::endl;
        std::multimap<JInstance*,JInstance*>::iterator itlow = m_connections.lower_bound(i);  
        std::multimap<JInstance*,JInstance*>::iterator itup = m_connections.upper_bound(i);   
        std::multimap<JInstance*,JInstance*>::iterator it;

        for (it=itlow; it!=itup; ++it) { 
        v.push_back((*it).second);
        //std::cout << "       " << (*it).second->get_name() << std::endl;
        
        
        }
        
        //std::cout << "   " << i->get_namae() << " get_inst:" << std::endl;
        
        return v;
}



void JManager::add_change() {
    //std::cout << m_layers_cnt << std::endl; 
    while ( ! permute_two_rand_instances_in_layer(rand()%m_layers_cnt) );
}

//FIXME this part need to be rewrited
bool JManager::permute_two_rand_instances_in_layer(int ln) {
        //assert(0);
        int f = rand()%m_layers[ln].size();
        int s = rand()%m_layers[ln].size();
        if ( f == s ) return false;
        
        if ( !m_permuted.empty() ) m_permuted.erase(m_permuted.begin(),m_permuted.begin()+m_permuted.size());
        if ( !m_fixme_permuted.empty() ) m_fixme_permuted.erase(m_fixme_permuted.begin(),m_fixme_permuted.begin()+m_fixme_permuted.size());
        
        std::pair<JInstance*,JInstance*> k;
        //if ( m_layers[ln][f]->get_center().y > m_layers[ln][s]->get_center().y )
        // k = std::make_pair( m_layers[ln][f], m_layers[ln][s] );
        //else
        //k = std::make_pair<JInstance*,JInstance*>(m_layers[ln][s],m_layers[ln][f]);
        
        std::pair<int,int> q1(s,f);
        std::pair<std::pair<int,int>,int> q2(q1,ln);
        
        m_permuted.push_back(k);
        m_fixme_permuted.push_back(q2);
        
        int tmp = m_layers[ln][f]->get_rownum();
        m_layers[ln][f]->set_rownum(m_layers[ln][s]->get_rownum());
        m_layers[ln][s]->set_rownum(tmp);
        
        std::swap(m_layers[ln][f],m_layers[ln][s]);
        
        return true;
}

/*
bool JManager::permute_two_rand_instances_in_layer(int ln) {
        int f = rand()%m_layers[ln].size();
        int s = rand()%m_layers[ln].size();
        if ( f == s ) return false;
        
        
        int tmp1 = m_layers[ln][f]->get_rownum();
        int tmp2 = m_layers[ln][s]->get_rownum();

        std::swap(m_layers[ln][f],m_layers[ln][s]);
        

        m_layers[ln][s]->set_rownum(tmp2);
        m_layers[ln][f]->set_rownum(tmp1);

        return true;
}
*/


void JManager::undo_permute() {
if (m_permuted.empty()) return;

std::vector<std::pair<JInstance*,JInstance*> >::iterator i;

int q = 0;
for (i=m_permuted.begin();i!=m_permuted.end();i++) 
{ 
    //m_renderer->draw_permute_two_instances((*i).second,(*i).first);
    
    //VAYQUARAAAA
    int tmp = m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.second]->get_rownum();
    m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.second]->set_rownum(m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.first]->get_rownum());
    m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.first]->set_rownum(tmp);
    
    
    std::swap(m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.second],m_layers[m_fixme_permuted[q].second][m_fixme_permuted[q].first.first]);
    q++;
}

if ( !m_permuted.empty() ) m_permuted.erase(m_permuted.begin(),m_permuted.begin()+m_permuted.size());
if ( !m_fixme_permuted.empty() ) m_fixme_permuted.erase(m_fixme_permuted.begin(),m_fixme_permuted.begin()+m_fixme_permuted.size());
}



//FIMXE also this part
void JManager::init_data() {
    for (unsigned int i=0; i<m_layers_cnt; i++ ) {
        //int perclm = 1+rand()%m_max_per_clm;
        int perclm = m_max_per_clm;
        m_layers[i].resize(perclm);
        for (unsigned int j=0; j<perclm ; j++ ) {
        //SDL_Point p;
        //p.x = m_offsset1*i+m_offsset2; p.y = m_offsset1*j+m_offsset2;
        JInstance* ii = new JInstance;
        //ii->set_center(p);
        std::stringstream z;
        z << "i" << i << "-" << j;
        ii->set_name(z.str());
        z.str("");
        m_layers[i][j] = ii;
        ii->set_colnum(i);
        ii->set_rownum(j);
            if (i) {
                int k = 1+rand()%m_conn_density; 
                std::set<JInstance*> seen;
                for(unsigned q=0;q<k;q++ ) {
                    JInstance* ri = m_layers[i-1][rand()%(m_layers[i-1].size())];
                    if ( seen.find(ri) == seen.end() ) {
                        std::pair<JInstance*,JInstance*> p(ri,ii);
                        m_connections.insert(p);
                        seen.insert(ri);
                    }
                }
            }
        }
    }
}


void JManager::draw() {
    for(unsigned i=0; i<m_layers_cnt; i++)
        for (unsigned int j=0; j<m_layers[i].size(); j++ ) {
            
            unsigned int x = m_offsset1*i+m_offsset2;
            unsigned int y = m_offsset1*m_layers[i][j]->get_rownum()+m_offsset2;
            
            m_renderer->set_drawing_color(0,255,0);
            m_renderer->draw_circle(x,y,4);  
        
            std::vector<JInstance*> vec = get_insts(m_layers[i][j]);
            std::vector<JInstance*>::iterator it;
        
            for (it=vec.begin(); it!=vec.end(); ++it) { 
                m_renderer->draw_line(m_offsset1*j+m_offsset2,m_offsset1*i+m_offsset2,m_offsset1*(*it)->get_rownum()+m_offsset2,m_offsset1*(*it)->get_colnum()+m_offsset2);
            }
    }
    
    /*
    std::multimap<JInstance*,JInstance*>::iterator i;
    for(i=m_connections.begin();i!=m_connections.end();++i)
    SDL_RenderDrawLine(m_renderer->get(),m_offsset1*(*i).first->get_colnum()+m_offsset2,m_offsset1*(*i).first->get_rownum()+m_offsset2,
                                    m_offsset1*(*i).second->get_colnum()+m_offsset2,m_offsset1*(*i).second->get_rownum()+m_offsset2);
    
    }*/
    
}




