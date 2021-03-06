/*
 * neuron.cpp
 *
 *  Created on: 29.06.2020
 *      Author: Marvin Bergmann
 */

#include <utility>
#include <random>
#include <chrono>
#include <neuron.hpp>

static std::minstd_rand random_generator(
		std::chrono::system_clock::now().time_since_epoch().count());

// non-member functions

float static random(float max) {
	return ((static_cast<float>(random_generator() - random_generator.min())
			/ random_generator.max() - 0.5f) * 2 * max);
}

// member functions

neuron::neuron() :
		activation([](float x) {
			return 0.0f;
		}), recover_time(0), bias(0.0f) {
}

neuron::neuron(int recover_time, float bias,
		std::function<float(float)> activation) :
		activation(activation), recover_time(recover_time), bias(bias) {
}

neuron neuron::rand(std::function<float(float)> activation) {
	return neuron(random(2.5f) + 2.5f, random(10.0f), activation);
}

neuron neuron::init(int recover_time, float bias,
		std::function<float(float)> activation) {
	return neuron(recover_time, bias, activation);
}

void neuron::set_recover_time(int time) {
	recover_time = time;
}

void neuron::set_bias(float value) {
	bias = value;
}

void neuron::input(float value) {
	input_val[1] += value;
}

void neuron::swap_inputs() {
	if (recover-- == 0) {
		recover = recover_time;

		neuron::input_val[0] = neuron::input_val[1];
		neuron::input_val[1] = 0.0f;

		return;
	}

	neuron::input_val[0] += neuron::input_val[1];
	neuron::input_val[1] = 0.0f;
}

bool neuron::fire() {
	return recover == 0 && activation(input_val[0]) >= bias;
}

std::string neuron::to_string() {
	return std::string("[") + std::to_string(recover_time) + ", "
			+ std::to_string(recover) + ", " + std::to_string(bias) + ", {"
			+ std::to_string(input_val[0]) + ", " + std::to_string(input_val[1])
			+ "}]";
}
