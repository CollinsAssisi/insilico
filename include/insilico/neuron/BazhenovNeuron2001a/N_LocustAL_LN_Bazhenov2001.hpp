/*
 neuron/BazhenovNeuron2001a/N_LocustAL_LN_Bazenov2001.hpp - Model of a Locust Antennal lobe inhibitory interneuron. From Bazhenov et. al. Neuron 2001a

 Copyright (C) 2015 Collins Assisi, Pune <collins@iiserpune.ac.in>

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

#ifndef N_LOCUSTAL_LN_BAZHENOV2001_HPP
#define N_LOCUSTAL_LN_BAZHENOV2001_HPP
#include "insilico/core/engine.hpp"
#include "insilico/neuron/helper/spike_list.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_Ca_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_KCA_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_Kv_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_LTCA_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_Leak_LocustAL_LN_Bazhenov2001.hpp"
#include "insilico/current/BazhenovNeuron2001a/I_KLeak_LocustAL_LN_Bazhenov2001.hpp"

namespace insilico {
  class N_LocustAL_LN_Bazhenov2001: public Neuron{
  public:
    void ode_set(state_type &variables, state_type &dxdt, const double t, unsigned index){
      std::vector<unsigned> g1_indices;
      std::vector<double> esyn_values;

      unsigned v_index = engine::neuron_index(index,"v");
      double v = variables[v_index];

      //note the time of the last spike
      double last_spiked = engine::neuron_value(index,"last_spike");
      double spike_duration = engine::neuron_value(index, "spike_duration"); //make this a private neuron property
      double thresh = engine::neuron_value(index,"thresh");//make this a private neuron property

      //absolute refractory
      if ((v > thresh) && (t - last_spiked) > spike_duration){
	engine::neuron_value(index,"last_spike", t);
      }//if

      //incoming synaptic currents
      double I_Syn = 0;
      g1_indices = engine::get_pre_neuron_indices(index,"g1");
      esyn_values = engine::get_pre_neuron_values(index,"esyn");

      for(unsigned iterator = 0; iterator < g1_indices.size(); ++iterator){
	I_Syn += variables[g1_indices[iterator]]*(v - esyn_values[iterator]);
      }//for

      //odeset
      I_KCA_LocustAL_LN_Bazhenov2001::current(variables, dxdt, t, index);
      I_Kv_LocustAL_LN_Bazhenov2001::current(variables, dxdt, t, index);
      I_LTCA_LocustAL_LN_Bazhenov2001::current(variables, dxdt, t, index);
      I_Leak_LocustAL_LN_Bazhenov2001::current(variables,dxdt, t, index);
      I_KLeak_LocustAL_LN_Bazhenov2001::current(variables,dxdt, t, index);

      double I_KCA = engine::neuron_value(index,"I_KCA_LocustAL_LN_Bazhenov2001");
      double I_Kv = engine::neuron_value(index,"I_Kv_LocustAL_LN_Bazhenov2001");
      double I_LTCA = engine::neuron_value(index,"I_LTCA_LocustAL_LN_Bazhenov2001");
      double I_Leak = engine::neuron_value(index,"I_Leak_LocustAL_LN_Bazhenov2001");
      double I_KLeak = engine::neuron_value(index,"I_KLeak_LocustAL_LN_Bazhenov2001");
      double I_Ext = engine::neuron_value(index,"I_Ext");
      dxdt[v_index] = I_Ext - I_KCA - I_Kv - I_LTCA - I_Leak -  I_KLeak - I_Syn;
    }//ode_set
  };//class N_LocustAL_LN_Bazhenov2001
}//namespace insilico
#endif
