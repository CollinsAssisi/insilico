/*
 current/I_KLeak_LocustInterneuron_CA2011.hpp - Hodgkin-Huxley Squid Axon experiment (Hodgkin-Huxley, 1952)

 Copyright (C) 2014 Pranav Kulkarni, Collins Assisi Lab, IISER, Pune <pranavcode@gmail.com>
 Copyright (C) 2014 Nishant Singh, Suhita Nadkarni Lab, IISER, Pune <nishant.singh@students.iiserpune.ac.in>

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

#ifndef INCLUDED_I_KLEAK_LOCUSTINTERNEURON_CA2011
#define INCLUDED_I_KLEAK_LOCUSTINTERNEURON_CA2011

#include "core/engine.hpp"

namespace insilico{

  class I_KLeak_LocustInterneuron_CA2011 {
  public:
    static void current(const state_type &variables, state_type &dxdt, const double t, int index) {
      double gkl = 0.02, ekl = -95;
      int v_index = engine::neuron_index(index,"v_LocustInterneuron_CA2011");
      double v = variables(v_index);

      //current
      engine::current_value(index,"I_KLeak_LocustInterneuron_CA2011",-gkl*(v-ekl));
    }//current
  }//class I_KLeak_LocustInterneuron_CA2011
}//insilico
