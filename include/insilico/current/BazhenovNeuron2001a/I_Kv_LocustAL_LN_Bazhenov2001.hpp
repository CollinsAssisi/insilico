/*
 current/I_Kv_LocustAL_LN_Bazhenov2001.hpp - Fast Potassium current

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

#ifndef I_KV_LOCUSTAL_LN_BAZHENOV2001
#define I_KV_LOCUSTAL_LN_BAZHENOV2001

#include "insilico/core/engine.hpp"

namespace insilico{
  class I_Kv_LocustAL_LN_Bazhenov2001{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){

      double gkv = 10.0;
      double ekv = -95.0;
      double shift = -50.0;
      double cels = 23.0;
      double phi = pow(3,((cels - 36.0)/10.0));

      int v_index = engine::neuron_index(index,"v_LocustAL_LN_Bazhenov2001");
      int n_index = engine::neuron_index(index,"n_I_Kv_LocustAL_LN_Bazhenov2001");

      double v = variables[v_index];
      double n = variables[n_index];

      double v_shift = v - shift;

      double alpha = 0.02*(15.0 - vshift)/(exp((15.0 - v2)/5.0) - 1.0);
      double beta = 0.5*exp((10.0 - vshift)/40.0);

      double tau_n = 1/(alpha + beta)/phi;
      double n_inf = alpha/(alpha + beta);

      //ODE
      dxdt[n_index] = -(n - n_inf)/tau_n;

      //current
      engine::current_value(index, "I_Kv_LocustAL_LN_Bazhenov2001", ( gkv * pow ( n , 4 ) * ( v - ekv ) ) );

    }//current
  }//class I_Kv_LocustAL_LN_Bazhenov2001  
}//namespace insilico
