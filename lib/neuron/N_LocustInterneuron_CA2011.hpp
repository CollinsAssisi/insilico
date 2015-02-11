/*
 neuron/N_LocustInterneuron_CA2011.hpp - Single compartment model of the an inhibitory interneuron in the locust antennal lobe. The parameters are from Assisi et. al. Neuron 2011. The model is based on Bazhenov et. al. Neuron 200?

 (C) 2014 Collins Assisi, Collins Assisi Lab, IISER, Pune <kolya.a@gmail.com>

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

#ifndef INCLUDED_N_LOCUSTINTERNEURON_CA2011_HPP
#define INCLUDED_N_LOCUSTINTERNEURON_CA2011_HPP

#include "core/engine.hpp"

#include "current/I_Leak_LocustInterneuron_CA2011.hpp"
#include "current/I_KLeak_LocustInterneuron_CA2011.hpp"
#include "current/I_KFast_LocustInterneuron_CA2011.hpp"
#include "current/I_CaLowThreshold_LocustInterneuron_CA2011.hpp"
#include "current/I_KCa_LocustInterneuron_CA2011.hpp"
#include "current/I_Ca_LocustInterneuron_CA2011.hpp"

namespace insilico{

  class N_LocustInterneuron_CA2011{
  public:
    static void odeset(state_type &variables, state_type &dxdt, const double i, int index){

      int v_index = engine::neuron_index(index,"v_LocustInterneuron_CA2011");
      double v = variables[v_index];

      double last_spiked = engine::neuron_value(index, "last_spike");       //time from last spike
      double spike_duration = engine::neuron_value(index,"spike_duration"); //absolute refractory
      double thresh = engine::neuron_value(index,"thresh");                 //threshold

      /// Warning: Check on this condition. Unless spike_duration is set correctly, last_spike may pick a value other than the first one exceeding threshold on the rising phase of the action potential
      ((v > thresh) && (t - last_spiked) > spike_duration){
	engine::neuron_value("last_spike", t);
      }

      //incoming synaptic inputs
      double I_syn = 0;
      vector <int> g1_indices = engine::get_pre_neuron_indices(index,"g1");
      vector <double> esyn_values = engine::get_pre_neuron_values(index,"esyn");

      for(vector<int>::size_type iterator = 0; iterator < g1_indices.size(); ++iterator){
	I_syn = I_syn + variables[g1_indices[iterator]]*(v - esyn_values[iterator]);
      }

      //ode

      I_Leak_LocustInterneuron_CA2011::current(variables,dxdt,t,index);
      I_KLeak_LocustInterneuron_CA2011::current(variables,dxdt,t,index);
      I_KFast_LocustInterneuron_CA2011::current(variables,dxdt,t,index);
      I_CaLowThreshold_LocustInterneuron_CA2011::current(variables,dxdt,t,index);
      I_KCa_LocustInterneuron_CA2011::current(variables,dxdt,t,index);
      
      double I_Leak = engine::current_value(index,"I_Leak_LocustInterneuron_CA2011");
      double I_KLeak = engine::current_value(index,"I_KLeak_LocustInterneuron_CA2011");
      double I_KFast = engine::current_value(index,"I_KFast_LocustInterneuron_CA2011");
      double I_CaLowThreshold = engine::current_value(index,"I_CaLowThreshold_LocustInterneuron_CA2011");
      double I_KCa = engine::current_value(index,"I_KCa_LocustInterneuron_CA2011");
      double I_Ext = engine::neuron_value(index,"iext");
      dxdt[v_index] = I_Ext - I_Leak - I_KLeak - I_KFast - I_CaLowThreshold - I_KCa - I_syn;


    }//function odeset
  };//class N_LocustInterneuron_CA2011
}//insilico
