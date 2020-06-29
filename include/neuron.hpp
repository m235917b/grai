/*
 * neuron.hpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#ifndef INCLUDE_NEURON_HPP_
#define INCLUDE_NEURON_HPP_

#include <unordered_map>
#include <vector>
#include <functional>

// TODO: check for possible pass by reference arguments

class neuron {

private:
	float input_val;
	std::function<float(float)> activation;

protected:
	int recover_time;
	float bias;
	std::unordered_map<neuron*, float> dendrites;

	neuron();

	neuron(int recover_time, float bias,
			std::unordered_map<neuron*, float> dendrites,
			std::function<float(float)> activation);

public:
	neuron(const neuron &owner);

	neuron(neuron &&owner) noexcept;

	~neuron();

	neuron& operator=(const neuron &that);

	neuron& operator=(neuron &&that);

	void swap(neuron &other);

	static neuron empty();

	static neuron rand(std::vector<neuron*> network,
			std::function<float(float)> activation);

	static neuron init_full(int recover_time, float bias,
			std::unordered_map<neuron*, float> dendrites,
			std::function<float(float)> activation);

	static neuron init(int recover_time, float bias,
			std::function<float(float)> activation);

	void set_activation(std::function<float(float)>);

	void set_recover_time(int time);

	void set_bias(float value);

	void set_dendrites(std::unordered_map<neuron*, float> dendrites);

	void mutate();

	void mutate(std::vector<neuron*> network);

	void mutate(std::vector<std::function<float(float)>> activation_functions);

	void mutate(std::vector<neuron*> network,
			std::vector<std::function<float(float)>> activation_functions);

	void input(float value);

	void fire();

	std::string to_string();

};

void swap(neuron &n1, neuron &n2);

#endif /* INCLUDE_NEURON_HPP_ */
