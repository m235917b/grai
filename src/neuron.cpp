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

std::minstd_rand random_generator(
		std::chrono::system_clock::now().time_since_epoch().count());

// non-member functions

void swap(neuron &n1, neuron &n2) {
	n1.swap(n2);
}

float random(float max) {
	return (static_cast<float>(random_generator() - random_generator.min())
			/ random_generator.max() - 0.5f) * 2 * max;
}

// member functions

neuron::neuron() :
		activation([](float x) {
			return 0.0f;
		}), recover_time(0), bias(0.0f), dendrites(
				std::vector<std::pair<std::weak_ptr<neuron>, float>>()) {
}

neuron::neuron(int recover_time, float bias,
		std::vector<std::pair<std::weak_ptr<neuron>, float>> &dendrites,
		std::function<float(float)> activation) :
		activation(activation), recover_time(recover_time), bias(bias), dendrites(
				std::vector<std::pair<std::weak_ptr<neuron>, float>>()) {
	neuron::dendrites = dendrites;
}

neuron::neuron(int recover_time, float bias,
		std::function<float(float)> activation) :
		activation(activation), recover_time(recover_time), bias(bias) {
}

neuron::neuron(const neuron &owner) :
		activation(owner.activation), recover_time(owner.recover_time), bias(
				owner.bias), dendrites(owner.dendrites) {
}

neuron::neuron(neuron &&owner) noexcept {
	std::swap(input_val, owner.input_val);
	std::swap(recover, owner.recover);
	std::swap(activation, owner.activation);
	std::swap(recover_time, owner.recover_time);
	std::swap(bias, owner.bias);
	std::swap(dendrites, owner.dendrites);
}

neuron::~neuron() {
}

neuron& neuron::operator=(const neuron &that) {
	if (this != &that) {
		input_val = that.input_val;
		recover = that.recover;
		activation = that.activation;
		recover_time = that.recover_time;
		bias = that.bias;
		dendrites = that.dendrites;
	}

	return *this;
}

neuron& neuron::operator=(neuron &&that) {
	std::swap(input_val, that.input_val);
	std::swap(recover, that.recover);
	std::swap(activation, that.activation);
	std::swap(recover_time, that.recover_time);
	std::swap(bias, that.bias);
	std::swap(dendrites, that.dendrites);

	return *this;
}

void neuron::swap(neuron &other) {
	std::swap(input_val, other.input_val);
	std::swap(recover, other.recover);
	std::swap(activation, other.activation);
	std::swap(recover_time, other.recover_time);
	std::swap(bias, other.bias);
	std::swap(dendrites, other.dendrites);
}

neuron neuron::rand(std::function<float(float)> activation) {
	return neuron(random(2.5f) + 2.5f, random(10.0f), activation);
}

neuron neuron::init_full(int recover_time, float bias,
		std::vector<std::pair<std::weak_ptr<neuron>, float>> &dendrites,
		std::function<float(float)> activation) {
	return neuron(recover_time, bias, dendrites, activation);
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

void neuron::set_dendrites(
		std::vector<std::pair<std::weak_ptr<neuron>, float>> &dendrites) {
	neuron::dendrites = std::vector<std::pair<std::weak_ptr<neuron>, float>>();
	neuron::dendrites = dendrites;
}

void neuron::push_dendrite(std::weak_ptr<neuron> n, float weight) {
	dendrites.push_back(std::pair<std::weak_ptr<neuron>, float>(n, weight));
}

void neuron::delete_dendrite(std::weak_ptr<neuron> n) {
	auto it = std::remove_if(dendrites.begin(), dendrites.end(), [&](auto p) {
		return p.first.lock() == n.lock();
	});
	dendrites.erase(it, dendrites.end());
}

void neuron::input(float value) {
	input_val[1] += value;
}

void neuron::swap_inputs() {
	neuron::input_val[0] = neuron::input_val[1];
	neuron::input_val[1] = 0.0f;
}

void neuron::stack_inputs() {
	neuron::input_val[0] += neuron::input_val[1];
	neuron::input_val[1] = 0.0f;
}

std::function<void()> neuron::fire() {
	if (recover-- == 0) {
		recover = recover_time;

		if (activation(input_val[0]) >= bias) {
			std::for_each(dendrites.begin(), dendrites.end(), [](auto p) {
				p.first.lock()->input(p.second);
			});
		}

		return std::bind(swap_inputs, this);
	}

	return std::bind(stack_inputs, this);
}

std::string neuron::to_string() {
	return std::string("[") + std::to_string(recover_time) + ", "
			+ std::to_string(recover) + ", " + std::to_string(bias) + ", {"
			+ std::to_string(input_val[0]) + ", " + std::to_string(input_val[1])
			+ "}]";
}

