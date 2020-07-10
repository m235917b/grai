/*
 * neuron.hpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#ifndef INCLUDE_NEURON_HPP_
#define INCLUDE_NEURON_HPP_

#include <array>
#include <functional>

class neuron {

private:
	std::array<float, 2> input_val = { 0.0f, 0.0f };
	unsigned char recover = 0;
	std::function<float(float)> activation;

protected:
	unsigned char recover_time;
	float bias;

	neuron();

	neuron(int recover_time, float bias,
			std::function<float(float)> activation);

public:
	~neuron() noexcept = default;

	neuron(const neuron &owner) = default;

	neuron(neuron &&owner) noexcept = default;

	neuron& operator=(const neuron &that) = default;

	neuron& operator=(neuron &&that) noexcept = default;

	static neuron rand(std::function<float(float)> activation);

	static neuron init(int recover_time, float bias,
			std::function<float(float)> activation);

	void set_recover_time(int time);

	void set_bias(float value);

	void input(float value);

	void swap_inputs();

	bool fire();

	std::string to_string();

};

#endif /* INCLUDE_NEURON_HPP_ */
