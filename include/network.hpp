/*
 * network.hpp
 *
 *  Created on: 06.07.2020
 *      Author: Marvin Bergmann
 */

#ifndef INCLUDE_NETWORK_HPP_
#define INCLUDE_NETWORK_HPP_

#include <graph.hpp>
#include <neuron.hpp>
#include <vector>

class network {
private:
	graph<neuron, float> net;
	std::vector<neuron&> input_neurons;
	std::vector<neuron&> output_neurons;

	network();

protected:

public:
	~network() noexcept = default;

};

#endif /* INCLUDE_NETWORK_HPP_ */
