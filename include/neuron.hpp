/*
 * neuron.hpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#ifndef INCLUDE_NEURON_HPP_
#define INCLUDE_NEURON_HPP_

#include <unordered_map>
#include <functional>

#define LINEAR_FUNC_ [](float x) {return x;}

class neuron;

struct ref_wrapper_hash {
	std::size_t operator()(const std::reference_wrapper<neuron> &k) const {
		return std::size_t(std::addressof(k.get()));
	}
};

struct ref_wrapper_equal {
	bool operator()(const std::reference_wrapper<neuron> &k1,
			const std::reference_wrapper<neuron> &k2) const {
		return std::size_t(std::addressof(k1.get()))
				== std::size_t(std::addressof(k2.get()));
	}
};

class neuron {

private:
	std::array<float, 2> input_val = { 0.0f, 0.0f };
	unsigned char recover = 0;
	std::function<float(float)> activation;

protected:
	unsigned char recover_time;
	float bias;
	std::unordered_map<std::reference_wrapper<neuron>, float, ref_wrapper_hash,
			ref_wrapper_equal> dendrites;

	neuron();

	neuron(int recover_time, float bias,
			std::unordered_map<std::reference_wrapper<neuron>, float,
					ref_wrapper_hash, ref_wrapper_equal> &dendrites,
			std::function<float(float)> activation);

	neuron(int recover_time, float bias,
			std::function<float(float)> activation);

	void swap_inputs();

	void stack_inputs();

public:
	neuron(const neuron &owner);

	neuron(neuron &&owner) noexcept;

	~neuron();

	neuron& operator=(const neuron &that);

	neuron& operator=(neuron &&that);

	void swap(neuron &other);

	static neuron rand(std::function<float(float)> activation);

	static neuron init_full(int recover_time, float bias,
			std::unordered_map<std::reference_wrapper<neuron>, float,
					ref_wrapper_hash, ref_wrapper_equal> &dendrites,
			std::function<float(float)> activation);

	static neuron init(int recover_time, float bias,
			std::function<float(float)> activation);

	void set_recover_time(int time);

	void set_bias(float value);

	void set_dendrites(
			std::unordered_map<std::reference_wrapper<neuron>, float,
					ref_wrapper_hash, ref_wrapper_equal> &dendrites);

	void push_dendrite(neuron &n, float weight);

	void delete_dendrite(neuron &n);

	void input(float value);

	std::function<void()> fire();

	std::string to_string();

};

void swap(neuron &n1, neuron &n2);

#endif /* INCLUDE_NEURON_HPP_ */
