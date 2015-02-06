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

#ifndef INCLUDED_I_CALOWTHRESHOLD_LOCUSTINTERNEURON_CA2011_HPP
#define INCLUDED_I_CALOWTHRESHOLD_LOCUSTINTERNEURON_CA2011_HPP

#include "core/engine.hpp"

namespace insilico{

  class I_CaLowThreshold_LocustInterneuron_CA2011{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double eca = 140.0; //(milliVolts)
      double gca = 2.0; //(milliSiemens)

      int v_index = engine::neuron_index(index, "v_LocustInterneuron_CA2011");
      int n_index = engine::neuron_index(index,"n_CaLowThreshold_LocustInterneuron_CA2011");

      double v = variable[v_index];
      double m = variable[m_index];
      double h = variable[h_index];

      //current 
      engine::current_value(index,"I_CaLowThreshold_LocustInterneuron_CA2011", gca*m*m*h*(v - eca));

      double m_inf = 1/(1 + exp(-(v + 20.0)/6.5));
      double h_inf = 1/(1 + exp((v + 25.0)/12.0));;
      double tau_m = 1.5;
      double tau_h = 0.3*exp((v - 40.0)/13.0) + 0.002*exp(-(v - 60.0)/29.0);

      //ode
      dxdt[m_index] = -1/tau_m*(m - m_inf);
      dxdt[h_index] = -1/tau_h*(h - h_inf);

    }//function current
  };//class I_CaLowThreshold_LocustInterneuron_CA2011
}//insilico
