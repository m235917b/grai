/*
 * main.cpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#include <iostream>
#include "../include/neuron.hpp"

int main() {
	std::cout << neuron::rand(std::vector<neuron*>(), [](float x) {
		return x;
	}).to_string() << "\n";

	return 0;
}

