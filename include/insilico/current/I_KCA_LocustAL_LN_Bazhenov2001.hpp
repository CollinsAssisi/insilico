/*
 current/I_KCa_LocustAL_LN_Bazhenov2001.hpp - Calcium dependent Potassium current

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
#ifndef I_KCA_LOCUSTAL_LN_BAZHENOV2001
#define I_KCA_LOCUSTAL_LN_BAZHENOV2001

#include "insilico/core/engine.hpp"

namespace insilico{
  class I_KCa_LocustAL_LN_Bazhenov2011{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      
      double gkca = 0.3;
      double ekca = -90.0;
      double Q = 2.3;
      double Ra = 0.01;
      double Rb = 0.02;
      double cels = 23;
      double Tad = pow(Q,((Cels -23.0)/10.0))

      int v_index = engine::neuron_index(index,"v_LocustAL_LN_Bazhenov2001");
      int m_index = engine::neuron_index(index,"m_I_KCa__LocustAL_LN_Bazhenov2001");
      int ca_index = engine::neuron_index(index,"I_Ca_LocustAL_LN_Bazhenov2001")

      double v = variables[v_index];
      double m = variables[m_index];
      double ca = variables[ca_index];

      double a = Ra*ca;
      double b = Rb;
      double tau_m = (1/(a + b))/Tad;
      double m_inf = a/(a + b);

      //ODE
      dxdt[m_index] = -(1/tau_m)*(m - m_inf);

      //Current
      engine::current_value(index,"I_KCa_LocustAL_LN_Bazhenov2001",(Tad * gkca * m * ( v - ekca )) )


    }//current
  }//class I_KCa_LocustAL_LN_Bazhenov2001
}//namespace insilico
