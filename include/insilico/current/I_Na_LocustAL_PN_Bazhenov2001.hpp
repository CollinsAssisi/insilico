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
#ifndef INCLUDED_I_Na_LOCUSTAL_PN_BAZHENOV2001_HPP
#define INCLUDED_I_Na_LOCUSTAL_PN_BAZHENOV2001_HPP

#include "insilico/core/engine.hpp"

namespace insilico {

  class I_Na_LocustAL_PN_Bazhenov2001{
  public:
    static void current(state_type &variables, state_type &dxdt, const double t, int index){
      double gna = 100.0; //muS max conductance
      double ena = 50.0;//mV reversal potential
      double cels = 22.0; //degree C
      double phi = pow(3,((cels-36)/10.0));//temperature based correction factor
      double vtr = -50.0; //shift of membrane potential

      int v_index = engine::neuron_index(index,"v_LocustAL_PN_Bazhenov2001");
      int m_index = engine::neuron_index(index,"m_LocustAL_PN_Bazhenov2001");
      int h_index = engine::neuron_index(index,"h_LocustAL_PN_Bazhenov2001");

      double v = variables[v_index];
      double v_shifted = v -vtr;
      double m = variables[m_index];
      double h = variables[h_index];

      double alpha_m = 0.32*(13.0 - v_shifted)/(exp((13.0 - v_shifted)/4.0) - 1.0);
      double beta_m = 0.28*(v_shifted - 40.0)/(exp((v_shifted - 40.0)/5.0) - 1.0);
      double tau_m = 1/(alpha_m + neta_m)/phi;
      double m_inf = alpha_m/(alpha_m + beta_m);

      double alpha_h = 0.128*exp((17.0 - v_shifted)/18.0);
      double beta_h = 4.0/(exp((40.0 - v_shifted)/5.0) + 1.0);
      double tau_h = 1/(alpha_h + beta_h)/phi;
      double h_inf = alpha_h/(alpha_h + beta_h)/phi;

      //ODEs
      dxdx[m_index] = -(m - m_inf)/tau_m;
      dxdx[m_index] = -(h - h_inf)/tau_h;
      //Current
      engine::neuron_value(index, "I_Na_LocustAL_PN_Bazhenov2001", gna*pow(m,3)*h*(v - ena))

    }
  }
}
