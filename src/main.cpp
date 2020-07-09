/*
 * main.cpp
 *
 *  Created on: 28.06.2020
 *      Author: Marvin Bergmann
 */

#include <iostream>
#include <chrono>
#include <memory>
#include <neuron.hpp>
#include <graph.hpp>
#include <test.hpp>

void speed_test_graph() {
	int it = 100000000;

	auto neurons = std::vector<neuron>();

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	auto net = graph<neuron, float>::from_vertices(neurons);

	net.add_edge(0, 1, 0.22f);
	net.add_edge(0, 2, 0.37f);
	net.add_edge(1, 3, -2.25f);
	net.add_edge(1, 4, 2.123f);
	net.add_edge(2, 5, -0.24f);
	net.add_edge(2, 6, 1.212f);

	auto start = std::chrono::high_resolution_clock::now();

	std::cout << "----- Speed Test Network -----\n";
	std::cout << net.get_vertex(0).to_string() << "\n";
	std::cout << net.get_vertex(1).to_string() << "\n";
	std::cout << net.get_vertex(2).to_string() << "\n";
	std::cout << net.get_vertex(3).to_string() << "\n";
	std::cout << net.get_vertex(4).to_string() << "\n";
	std::cout << net.get_vertex(5).to_string() << "\n";
	std::cout << net.get_vertex(6).to_string() << "\n";
	std::cout << "->\n";

	for (int i = 0; i < it; ++i) {

		net.get_vertex(0).input(3.2f);

		net.for_each(
				[&](neuron &n,
						std::vector<std::pair<std::size_t, float> > &edges) {
					if (n.fire()) {
						std::for_each(edges.begin(), edges.end(), [&](auto &p) {
							net.get_vertex(p.first).input(p.second);
						});
					}
				});

		net.for_each_vert([](neuron &n) {
			n.swap_inputs();
		});
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = finish - start;

	std::cout << net.get_vertex(0).to_string() << "\n";
	std::cout << net.get_vertex(1).to_string() << "\n";
	std::cout << net.get_vertex(2).to_string() << "\n";
	std::cout << net.get_vertex(3).to_string() << "\n";
	std::cout << net.get_vertex(4).to_string() << "\n";
	std::cout << net.get_vertex(5).to_string() << "\n";
	std::cout << net.get_vertex(6).to_string() << "\n\n";
	std::cout << "Elapsed time for " << it << " iterations: "
			<< elapsed.count() / 1000000 << " seconds\n\n";
}

void test_graph() {
	auto neurons = std::vector<neuron>();

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	neurons.push_back(neuron::rand([](float x) {
		return x;
	}));

	auto net = graph<neuron, float>::from_vertices(neurons);

	net.add_edge(0, 1, 0.22f);
	net.add_edge(1, 2, 0.37f);
	net.add_edge(2, 3, -2.25f);
	net.add_edge(2, 1, 2.123f);
	net.add_edge(3, 4, -0.24f);
	net.add_edge(3, 5, 1.212f);

	std::cout << "----- Start Network Test -----\n";

	for (int i = 0; i < 10; ++i) {

		net.get_vertex(0).input(3.2f);

		net.for_each(
				[&](neuron &n,
						std::vector<std::pair<std::size_t, float> > &edges) {
					if (n.fire()) {
						std::for_each(edges.begin(), edges.end(), [&](auto &p) {
							net.get_vertex(p.first).input(p.second);
						});
					}
				});

		std::cout << net.get_vertex(0).to_string() << "\n";
		std::cout << net.get_vertex(1).to_string() << "\n";
		std::cout << net.get_vertex(2).to_string() << "\n";
		std::cout << net.get_vertex(3).to_string() << "\n";
		std::cout << net.get_vertex(4).to_string() << "\n";
		std::cout << net.get_vertex(5).to_string() << "\n";
		std::cout << "->\n";

		net.for_each_vert([](neuron &n) {
			n.swap_inputs();
		});

		std::cout << net.get_vertex(0).to_string() << "\n";
		std::cout << net.get_vertex(1).to_string() << "\n";
		std::cout << net.get_vertex(2).to_string() << "\n";
		std::cout << net.get_vertex(3).to_string() << "\n";
		std::cout << net.get_vertex(4).to_string() << "\n";
		std::cout << net.get_vertex(5).to_string() << "\n";
		std::cout << "----------\n";
	}

	std::cout << "\n";
}

int main() {
	speed_test_graph();
	run_tests();
	test_graph();

	return 0;
}

