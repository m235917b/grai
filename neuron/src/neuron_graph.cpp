/*
 * neuron_graph.cpp
 *
 *  Created on: 10.07.2020
 *      Author: Marvin Bergmann
 */

#include <utility>
#include <random>
#include <chrono>
#include <neuron_graph.hpp>

static std::minstd_rand random_generator(
		std::chrono::system_clock::now().time_since_epoch().count());

// non-member functions

void swap(neuron_graph &n1, neuron_graph &n2) {
	n1.swap(n2);
}

float static random(float max) {
	return (static_cast<float>(random_generator() - random_generator.min())
			/ random_generator.max() - 0.5f) * 2 * max;
}

// member functions

neuron_graph::neuron_graph() :
		activation([](float x) {
			return 0.0f;
		}), recover_time(0), bias(0.0f), dendrites(
				std::vector<
						std::pair<std::reference_wrapper<neuron_graph>, float>>()) {
}

neuron_graph::neuron_graph(int recover_time, float bias,
		std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites,
		std::function<float(float)> activation) :
		activation(activation), recover_time(recover_time), bias(bias), dendrites(
				dendrites) {
}

neuron_graph::neuron_graph(int recover_time, float bias,
		std::function<float(float)> activation) :
		activation(activation), recover_time(recover_time), bias(bias), dendrites(
				std::vector<
						std::pair<std::reference_wrapper<neuron_graph>, float>>()) {
}

bool neuron_graph::operator==(neuron_graph &that) {
	return this == &that;
}

bool neuron_graph::operator!=(neuron_graph &that) {
	return this != &that;
}

void neuron_graph::swap(neuron_graph &other) {
	if (this != &other) {
		std::swap(input_val, other.input_val);
		std::swap(recover, other.recover);
		std::swap(activation, other.activation);
		std::swap(recover_time, other.recover_time);
		std::swap(bias, other.bias);
		std::swap(dendrites, other.dendrites);
	}
}

neuron_graph neuron_graph::rand(std::function<float(float)> activation) {
	return neuron_graph(random(2.5f) + 2.5f, random(10.0f), activation);
}

neuron_graph neuron_graph::init_full(int recover_time, float bias,
		std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites,
		std::function<float(float)> activation) {
	return neuron_graph(recover_time, bias, dendrites, activation);
}

neuron_graph neuron_graph::init(int recover_time, float bias,
		std::function<float(float)> activation) {
	return neuron_graph(recover_time, bias, activation);
}

void neuron_graph::set_recover_time(int time) {
	recover_time = time;
}

void neuron_graph::set_bias(float value) {
	bias = value;
}

void neuron_graph::set_dendrites(
		std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites) {
	neuron_graph::dendrites = dendrites;
}

void neuron_graph::push_dendrite(neuron_graph &n, float weight) {
	dendrites.push_back(
			std::pair<std::reference_wrapper<neuron_graph>, float>(std::ref(n),
					weight));
}

void neuron_graph::delete_dendrite(neuron_graph &n) {
	dendrites.erase(
			std::remove_if(dendrites.begin(), dendrites.end(), [&](auto &p) {
				return p.first.get() == n;
			}), dendrites.end());
}

void neuron_graph::input(float value) {
	input_val[1] += value;
}

void neuron_graph::swap_inputs() {
	if (recover-- == 0) {
		recover = recover_time;

		input_val[0] = input_val[1];
		input_val[1] = 0.0f;

		return;
	}

	input_val[0] += input_val[1];
	input_val[1] = 0.0f;
}

void neuron_graph::fire() {
	if (recover == 0) {
		if (activation(input_val[0]) >= bias) {
			std::for_each(dendrites.begin(), dendrites.end(), [](auto &p) {
				p.first.get().input(p.second);
			});
		}
	}
}

std::string neuron_graph::to_string() {
	return std::string("[") + std::to_string(recover_time) + ", "
			+ std::to_string(recover) + ", " + std::to_string(bias) + ", {"
			+ std::to_string(input_val[0]) + ", " + std::to_string(input_val[1])
			+ "}]";
}

