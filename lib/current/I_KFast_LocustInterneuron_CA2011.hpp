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

#ifndef INCLUDED_I_KFAST_LOCUSTINTERNEURON_CA2011_HPP
#define INCLUDED_I_KFAST_LOCUSTINTERNEURON_CA2011_HPP

#include "core/engine.hpp"

namespace insilico {

  class I_KFast_LocustInterneuron_CA2011{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double gk = 10.0; //(microSiemens)
      double ek = -95.0; //(milliVolt)
      double temperature = 22.0; //(celsius)
      double phi = pow(3,(temperature - 36.0)/10.0); //temperature correction factor

      int v_index = engine::neuron_index(index,"v_LocustInterneuron_CA2011");
      int n_index = engine::neuron_index(index,"n_KFast_LocustInterneuron_CA2011");

      double v = variables[v_index];
      double n = variables[n_index];
      
      //current
      engine::current_value(index,"I_KFast_LocustInterneuron_CA2011", gk*pow(n,4)*(v-ek));

      double v_shift = v + 50.0; //shifted voltage
      double alpha_n = 0.02*(15.0 - v_shift)/(exp((15.0 - v_shift)/5.0) - 1.0);
      double beta_n = 0.5*exp((10.0 - v_shift)/40.0);
      double n_inf = alpha/(alpha_n + beta_n);
      double tau_n = 1/((alpha_n + beta_n)*phi);

      //ODE
      dxdt[n_index] = -(n - n_inf)/tau_n;


    }//function current
  };//class I_KFast_LocustInterneuron_CA2011{
}//insilico
