/*
  examples/LocustAntennalLobe/main.cpp - insilico's example using neuron

  Copyright (C) 2015 Pranav Kulkarni, Collins Assisi Lab,
                     IISER, Pune <pranavcode@gmail.com>

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

#include "insilico/core.hpp"
#include "insilico/neuron/BazhenovNeuron2001a/N_LocustAL_LN_Bazhenov2001.hpp"
#include <boost/numeric/odeint.hpp>
#include <iostream>
#include <string>
#include <vector>

using namespace insilico;
using namespace std;

int main(int argc, char **argv){
  
  configuration::initialize(argc,argv);
  configuration::observe("v");

  engine::generate_neuron<N_LocustAL_LN_Bazhenov2001>(1);
engine::spike_list.resize(1);

  state_type variables = engine::get_variables();
  integrate_const(boost::numeric::odeint::runge_kutta4<state_type>(),
		  engine::driver(),variables,
		  0.0,100.0,0.05, configuration::observer());

  configuration::finalize();

}//main
