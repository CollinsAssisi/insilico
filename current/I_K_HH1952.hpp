/*
 current/I_K_HH1952.hpp - Current flow across neuronal membrane due to
                          Potassium (K) conductance. (Hodgkin-Huxley, 1952)

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

 Current that flows through Potassium (K) channel due to the potential difference
 caused by Potassium (K) conductance across neuronal membrane. (Hodgkin-Huxley, 1952)
*/

#ifndef INCLUDED_I_K_HH9152_HPP
#define INCLUDED_I_K_HH9152_HPP

#include "core/engine.hpp"

namespace insilico {

class I_K_HH1952 {
 public:
  static float current(const state_type &variables, state_type &dxdt, const double t, int index) {
    float gk = 36, ek = -12;

    int v_index = engine::neuron_index(index, "v");
    int n_index = engine::neuron_index(index, "n");

    float v = variables[v_index];
    float n = variables[n_index];

    float alpha_n = (0.1-0.01 * v)/(exp(1-0.1 * v)-1.0);
    float beta_n = 0.125*exp(-v / 80.0);

    // ODE set
    dxdt[n_index]=(alpha_n*(1 - n)-beta_n * n);

    // Current
    return -gk * pow(n,4) * (v - ek);

  } // function current
}; // class I_K_HH1952

} // insilico

#endif