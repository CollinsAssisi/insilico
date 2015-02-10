/*
 current/I_KFast_LocustInterneuron_CA2011.hpp 

 Copyright (C) 2015 Collins Assisi, Collins Assisi Lab, IISER, Pune <kolya.a@gmail.com>

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
*/

#ifndef INCLUDED_I_CA_LOCUSTINTERNEURON_CA2011_HPP
#define INCLUDED_I_CA_LOCUSTINTERNEURON_CA2011_HPP

#include "core/engine.hpp"

namespace insilico{

  class I_Ca_LocustInterneuron_CA2011{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double ca_inf = 2.4e-4;
      double tau_r = 5.0;
      double d = 0.1;

      int ca_index = engine::neuron_index(index, "I_Ca_LocustInterneuron_CA2011");
      int ltca_index = engine::neuron_index(index, "I_CaLowThreshold_LocustInterneuron_CA2011");

      double ca = variable[ca_index];
      double ltca = variable[ltca_index];
      double drive = -ltca*10.0/(2.0*96489.0*0.1);

      if(drive < 0.0){
	drive = 0.0;
      }//if

      //ode
      dxdt[ca_index] = drive + (ca_inf - ca)/tau_r;

    }//function current
  };//class I_Ca_LocustInterneuron_CA2011

}//insilico
