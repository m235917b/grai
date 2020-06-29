/*
 * neuron.cpp
 *
 *  Created on: 29.06.2020
 *      Author: Marvin Bergmann
 */

#include <utility>
#include <random>
#include <chrono>
#include "../include/neuron.hpp"

// non-member functions

float random(float max) {
	std::minstd_rand g(
			std::chrono::system_clock::now().time_since_epoch().count());

	return (static_cast<float>(g() - g.min()) / g.max() - 0.5f) * 2 * max;
}

// member functions

neuron::neuron() {
	recover_time = 0;
	input_val = 0.0f;
	bias = 0.0f;
	activation = [](float x) {
		return 0.0f;
	};
	dendrites = std::unordered_map<neuron*, float>();
}

neuron::neuron(int recover_time, float bias,
		std::unordered_map<neuron*, float> dendrites,
		std::function<float(float)> activation) {
	neuron::recover_time = recover_time;
	neuron::input_val = 0.0f;
	neuron::bias = bias;
	neuron::activation = activation;
	neuron::dendrites = dendrites;
}

neuron::neuron(const neuron &owner) {
	recover_time = owner.recover_time;
	input_val = owner.input_val;
	bias = owner.bias;
	activation = owner.activation;
	dendrites = owner.dendrites;
}

neuron::neuron(neuron &&owner) noexcept {
	std::swap(recover_time, owner.recover_time);
	std::swap(input_val, owner.input_val);
	std::swap(bias, owner.bias);
	std::swap(activation, owner.activation);
	std::swap(dendrites, owner.dendrites);
}

neuron::~neuron() {
	// TODO: delete pointers in map
}

neuron& neuron::operator=(const neuron &that) {
	if (this != &that) {
		recover_time = that.recover_time;
		input_val = that.input_val;
		bias = that.bias;
		activation = that.activation;
		dendrites = that.dendrites;
	}

	return *this;
}

neuron& neuron::operator=(neuron &&that) {
	std::swap(recover_time, that.recover_time);
	std::swap(input_val, that.input_val);
	std::swap(bias, that.bias);
	std::swap(activation, that.activation);
	std::swap(dendrites, that.dendrites);

	return *this;
}

void swap(neuron &n1, neuron &n2) {
	n1.swap(n2);
}

void neuron::swap(neuron &other) {
	const int recover_time = neuron::recover_time;
	const float input_val = neuron::input_val;
	const float bias = neuron::bias;

	neuron::recover_time = other.recover_time;
	neuron::input_val = other.input_val;
	neuron::bias = other.bias;

	other.recover_time = recover_time;
	other.input_val = input_val;
	other.bias = bias;

	std::swap(activation, other.activation);
	std::swap(dendrites, other.dendrites);
}

neuron neuron::empty() {
	return neuron();
}

neuron neuron::rand(std::vector<neuron*> network,
		std::function<float(float)> activation) {
	// TODO: randomly distribute connections
	return neuron(random(2.5f) + 2.5f, random(10.0f),
			std::unordered_map<neuron*, float>(), activation);
}

neuron neuron::init_full(int recover_time, float bias,
		std::unordered_map<neuron*, float> dendrites,
		std::function<float(float)> activation) {
	return neuron(recover_time, bias, dendrites, activation);
}

neuron neuron::init(int recover_time, float bias,
		std::function<float(float)> activation) {
	return neuron(recover_time, bias, std::unordered_map<neuron*, float>(),
			activation);
}

void neuron::set_activation(std::function<float(float)> activation) {
	neuron::activation = activation;
}

void neuron::set_recover_time(int time) {
	recover_time = time;
}

void neuron::set_bias(float value) {
	bias = value;
}

void neuron::set_dendrites(std::unordered_map<neuron*, float> dendrites) {
	neuron::dendrites = dendrites;
}

void neuron::mutate() {
	recover_time = random(2.5f) + 2.5f;
	bias = random(10.0f);
}

void neuron::mutate(std::vector<neuron*> network) {
	// TODO: implement
}

void neuron::mutate(
		std::vector<std::function<float(float)>> activation_functions) {
	activation = activation_functions.at(
			random(static_cast<float>(activation_functions.size()) / 2)
					+ static_cast<float>(activation_functions.size()) / 2);
}

void neuron::mutate(std::vector<neuron*> network,
		std::vector<std::function<float(float)>> activation_functions) {
	// TODO: implement
}

void neuron::input(float value) {
	// TODO: implement
}

void neuron::fire() {
	// TODO: implement
}

std::string neuron::to_string() {
	return std::string("[") + std::to_string(recover_time) + ", "
			+ std::to_string(bias) + ", " + std::to_string(input_val) + "]";
}

