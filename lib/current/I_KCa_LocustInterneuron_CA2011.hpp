/*
 current/I_KCa_LocustInterneuron_CA2011.hpp 

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

#ifndef INCLUDED_I_KCA_LOCUSTINTERNEURON_CA2011_HPP
#define INCLUDED_I_KCA_LOCUSTINTERNEURON_CA2011_HPP

#include "core/engine.hpp"

namespace insilico{

  class I_KCa_LocustInterneuron_CA2011{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){

      double g_kca = 0.3;

      int v_index = engine::neuron_index(index,"v_LocustInterneuron_Ca2011");
      int ca_index = engine::neuron_index(index,"I_Ca_LocustInterneuron_CA2011");
      int m_index = engine::neuron_index(index,"m_KCa_LocustInterneuron_CA2011");

      double v = variables[v_index];
      double ca = variables[ca_index];
      double m = variables[m_index];

      double tau_m = 1/(0.01*ca + 0.02);
      double m_inf = 0.01*ca/(0.01*ca + 0.02);

      //ode
      dxdt[ca_index] = 1/tau_m*(m - m_inf);

    }//function current

  };//class I_KCa_LocustInterneuron_CA2011

}//insilico
