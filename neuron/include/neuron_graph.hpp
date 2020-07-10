/*
 * neuron_graph.hpp
 *
 *  Created on: 10.07.2020
 *      Author: Marvin Bergmann
 */

#ifndef neuron_graph_INCLUDE_NEURON_GRAPH_HPP_
#define neuron_graph_INCLUDE_NEURON_GRAPH_HPP_

#include <vector>
#include <functional>

#define LINEAR_FUNC_ [](float x) {return x;}

class neuron_graph {

private:
	std::array<float, 2> input_val = { 0.0f, 0.0f };
	unsigned char recover = 0;
	std::function<float(float)> activation;

protected:
	unsigned char recover_time;
	float bias;
	std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> dendrites;

	neuron_graph();

	neuron_graph(int recover_time, float bias,
			std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites,
			std::function<float(float)> activation);

	neuron_graph(int recover_time, float bias,
			std::function<float(float)> activation);

public:
	~neuron_graph() noexcept = default;

	// !WARNING! : copies are only shallow copies!

	neuron_graph(const neuron_graph &owner) = default;

	neuron_graph(neuron_graph &&owner) noexcept = default;

	neuron_graph& operator=(const neuron_graph &that) = default;

	neuron_graph& operator=(neuron_graph &&that) noexcept = default;

	// since the network is defined by references, equality is defined by address

	bool operator==(neuron_graph &that);

	bool operator!=(neuron_graph &that);

	void swap(neuron_graph &other);

	static neuron_graph rand(std::function<float(float)> activation);

	static neuron_graph init_full(int recover_time, float bias,
			std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites,
			std::function<float(float)> activation);

	static neuron_graph init(int recover_time, float bias,
			std::function<float(float)> activation);

	void set_recover_time(int time);

	void set_bias(float value);

	void set_dendrites(
			std::vector<std::pair<std::reference_wrapper<neuron_graph>, float>> &dendrites);

	void push_dendrite(neuron_graph &n, float weight);

	void delete_dendrite(neuron_graph &n);

	void input(float value);

	void swap_inputs();

	void fire();

	std::string to_string();

};

void swap(neuron_graph &n1, neuron_graph &n2);

#endif /* neuron_graph_INCLUDE_NEURON_GRAPH_HPP_ */
