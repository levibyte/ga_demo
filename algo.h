#ifndef algo_h
#define algo_h

#include <cmath>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>

#include "instance.h"


typedef std::vector<JInstance*> PCLM; 
typedef std::vector<PCLM> GEN;

class JGeneticAlgo {
  public:  
    void add(GEN g) { gens.push_back(g); }
    
    GEN merge() {
        GEN g0 = gens[0];
        GEN g1 = gens[1];
        GEN z;
        
        std::cout << g0.size() << std::endl;
        for(int i=0;i<g0.size();i++) z.push_back(merge_columns(g0[i],g1[i]));
        
       return z; 
        
    }
    
    PCLM merge_columns(PCLM f, PCLM s) {
      PCLM z;
      std::cout << f.size() << std::endl;
      for(int i=0;i<f.size()/2;i++) z.push_back(f[i]);
      for(int i=0;i<s.size();i++)  {
        if ( std::find(z.begin(),z.end(),s[i]) == z.end() ) 
          z.push_back(s[i]);
        else
          std::cout << "***" << s[i] << std::endl;
      }
      
      return z;
    }
  
    std::vector<GEN> gens;
};
#endif