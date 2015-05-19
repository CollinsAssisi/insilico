/*
 current/I_LTCA_LocustAL_LN_Bazhenov2001.hpp -  (Low threshold calcium) conductance. (Bazhenov et. al. Neuron 2001)

 Copyright (C) 2014 Pranav Kulkarni, Collins Assisi Lab, IISER, Pune <pranavcode@gmail.com>

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
#ifndef INCLUDED_I_LTCA_LOCUSTAL_LN_BAZHENOV2001_HPP
#define INCLUDED_I_LTCA_LOCUSTAL_LN_BAZHENOV2001_HPP

#include "insilico/core/engine.hpp"

namespace insilico{
  class I_LTCA_LocustAL_LN_Bazhenov2001{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double eca = 140.0; //mV
      double gca = 2.0; //muS

      int v_index = engine::neuron_index(index,"v_LocustAL_LN_Bazhenov2001");
      int m_index = engine::neuron_index(index,"m_LTCA_LocustAL_LN_Bazhenov2001");
      int h_index = engine::neuron_index(index,"h_LTCA_LocustAL_LN_Bazhenov2001");


      double v = variable[v_index];
      double m = variable[m_index];
      double h = variable[m_index];

      double m_inf = 1.0/(1.0 + exp(-(v + 20.0)/6.5));
      double h_inf = 1.0/(1.0 + exp((v + 25.0)/12.0));
      double tau_m = 1.5;
      double tau_h = 0.3*exp((v - 40.0)/13.0) + 0.002*exp(-(v - 60.0)/29.0);

      //ODE 
      dxdt[m_index] = -1/tau_m*(m - m_inf);
      dxdt[h_index] = -1/tau_h*(h - h_inf);

      //Current
      engine::current_value(index,"I_LTCA_LocustAL_LN_Bazhenov2001",(gca * pow ( m , 2) * h * ( v - eca ) ));

    }
  }
}
