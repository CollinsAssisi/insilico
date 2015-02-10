/*
 current/I_Leak_LocustInterneuron_CA2011.hpp - Leak current used in simulating a network of inhibitory interneurons in Assisi et. al. Neuron 2011

 (C) 2014 Collins Assisi Lab, IISER, Pune <kolya.a@gmail.com>

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 Brief:
 Leak current flow across neuronal membrane. (Assisi, Stopfer, Bazhenov, Neuron 2011)
*/

#ifndef INCLUDED_I_LEAK_LOCUSTINTERNEURON_CA2011
#define INCLUDED_I_LEAK_LOCUSTINTERNEURON_CA2011

#include "core/engine.hpp"

namespace insilico {

  class I_Leak_LocustInterneuron_CA2011 {
  public: 
    
    static void current(const state_type &variables, state_type &dxdt, const double t, int index){
    
      double gl = 0.15, el = -55;
      int v_index = engine::neuron_index(index, "v_LocustInterneuron_CA2011");
      double v = variables[v_index];

      //Current
      engine::current_value(index,"I_Leak_LocustInterneuron_CA2011",-gl*(v-el));


    } //function current
  };//class I_Leak_LocustInterneuron_CA2011
}//insilico
