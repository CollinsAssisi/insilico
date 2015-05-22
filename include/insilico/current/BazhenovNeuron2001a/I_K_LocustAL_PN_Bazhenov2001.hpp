/*
 current/I_K_LocustAL_PN_Bazhenov2001.hpp -  (K) conductance. (Bazhenov et. al. Neuron 2001)

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
#ifndef INCLUDED_I_K_LOCUSTAL_PN_BAZHENOV2001_HPP
#define INCLUDED_I_K_LOCUSTAL_PN_BAZHENOV2001_HPP

#include "insilico/core/engine.hpp"

namespace insilico {

  class I_K_LocustAL_PN_Bazhenov2001{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double gk = 10.0; //muS max conductance
      double ek = -95.0;//mV reversal potential
      double cels = 22.0; //degree C
      double phi = pow(3,((cels-36)/10.0));//temperature based correction factor
      double vtr = -50.0; //shift of membrane potential

      int v_index = engine::neuron_index(index,"v");
      int n_index = engine::neuron_index(index,"n_K");

      double v = variables[v_index];
      double v_shifted = v -vtr;
      double n = variables[n_index];


      double alpha_n = 0.02*(15.0 - v_shifted)/(exp((15.0 - vtr)/5.0) - 1.0);
      double beta_n = 0.5*exp((10.0 - v_shifted)/40.0);
      double tau_n = 1/(alpha_n + beta_n)/phi;
      double n_inf = alpha_n/(alpha_n + beta_n);

      //ODE
      dxdx[n_index] = -(n - n_inf)/tau_n;

      //Current
      engine::neuron_value(index, "I_K_LocustAL_PN_Bazhenov2001", gk*pow(n,4)*(v - ek))

    }
  };
}
#endif
