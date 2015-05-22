/*
 current/I_Na_LocustAL_PN_Bazhenov2001.hpp -  (Na) conductance. (Bazhenov et. al. Neuron 2001)

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
#ifndef INCLUDED_I_KA_LOCUSTAL_PN_BAZHENOV2001_HPP
#define INCLUDED_I_KA_LOCUSTAL_PN_BAZHENOV2001_HPP

#include insilico/core/engine.hpp

namespace insilico{
  class I_KA_LocustAL_PN_Bazhenov2001{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){

      double gka = 10.0;
      double eka = -95.0;
      double cels = 36.0;
      double tad = pow(3.0,((cels - 23.0)/10.0));

      int v_index = engine::neuron_index(index,"v");
      int m_index = engine::neuron_index(index,"m_KA");
      int h_index = engine::neuron_index(index,"h_KA");

      double v = variables[v_index];
      double m = variables[m_index];
      double h = variables[h_index];

      double tau_m = (1.0/( exp(( v + 35.82 ) / 19.69 )+exp( - ( v + 79.69 ) / 12.7 ) ) + 0.37) / tad;
      double m_inf = 1.0 / ( 1.0 +exp ( - ( v + 60.0 ) / 8.5));
      double tau_h = 1.0 / ( ( exp ( ( v + 46.05 ) / 5.0 ) + exp( - ( v + 238.4 ) / 37.45 ) ) ) / tad;
      if(v >= -63.0){
	tau_h = 19.0/tad;
      }//if
      double h_inf =  1.0/( 1.0 + exp ( ( v + 78.0 ) / 6.0 ) );

      //ODE
      dxdt[m_index] = -(1.0/tau_m)*(m - m_inf);
      dxdt[h_index] = -(1.0/tau_h)*(h - h_inf);

      //Current
      engine::neuron_value(index, "I_KA_LocustAL_PN_Bazhenov2001", ( gka * pow ( m , 4.0 ) * h * ( v - eka ) ))

    }//current
  };//class I_KA_LocustAL_PN_Bazhenov2001
}//namespace insilico
#endif
