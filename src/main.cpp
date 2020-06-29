/*
 * main.cpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#include <iostream>
#include "../include/neuron.hpp"

void test() {
	auto n(std::make_shared<neuron>(neuron::rand([](float x) {
		return x;
	})));

	auto n0(std::make_shared<neuron>(neuron::rand([](float x) {
		return x;
	})));

	auto n1(std::make_shared<neuron>(neuron::rand([](float x) {
		return x;
	})));

	auto n2(std::make_shared<neuron>(neuron::rand([](float x) {
		return x;
	})));

	auto n3(std::make_shared<neuron>(neuron::rand([](float x) {
		return x;
	})));

	auto testmap = std::vector<std::pair<std::weak_ptr<neuron>, float>>();
	testmap.push_back(std::pair<std::weak_ptr<neuron>, float>(n1, 1.7f));

	n->set_dendrites(testmap);
	testmap.clear();

	n0->push_dendrite(n1, 1.234f);
	n1->push_dendrite(n2, 0.3f);
	n2->push_dendrite(n1, -0.3f);
	n2->push_dendrite(n3, 4.1f);

	n2->delete_dendrite(n3);

	n->input(3.2f);

	std::cout << n->to_string() << "\n";
	std::cout << n0->to_string() << "\n";
	std::cout << n1->to_string() << "\n";
	std::cout << n2->to_string() << "\n";
	std::cout << n3->to_string() << "\n\n";

	for (int i = 0; i < 10; ++i) {

		auto funcs = std::vector<std::function<void()>>();

		funcs.push_back(n->fire());
		funcs.push_back(n0->fire());
		funcs.push_back(n1->fire());
		funcs.push_back(n2->fire());
		funcs.push_back(n3->fire());

		std::for_each(funcs.begin(), funcs.end(), [](auto f) {
			f();
		});

		funcs.clear();

		std::cout << n->to_string() << "\n";
		std::cout << n0->to_string() << "\n";
		std::cout << n1->to_string() << "\n";
		std::cout << n2->to_string() << "\n";
		std::cout << n3->to_string() << "\n\n----------\n\n";
	}
}

int main() {
	test();

	return 0;
}

