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

void test() {
	/*auto n(std::make_shared<neuron>(neuron::rand([](float x) {
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

	 n->push_dendrite(*n1, 1.7f);
	 n0->push_dendrite(*n1, 1.234f);
	 n1->push_dendrite(*n2, 0.3f);
	 n2->push_dendrite(*n1, -0.3f);
	 n2->push_dendrite(*n3, 4.1f);

	 n2->delete_dendrite(*n3);

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
	 }*/
}

void speed_test() {
	/*auto n0(std::make_shared<neuron>(neuron::rand([](float x) {
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

	 auto n4(std::make_shared<neuron>(neuron::rand([](float x) {
	 return x;
	 })));

	 auto n5(std::make_shared<neuron>(neuron::rand([](float x) {
	 return x;
	 })));

	 auto n6(std::make_shared<neuron>(neuron::rand([](float x) {
	 return x;
	 })));

	 std::vector<std::shared_ptr<neuron>> net = { n0, n1, n2, n3, n4, n5, n6 };

	 n0->push_dendrite(*n1, 2);
	 n0->push_dendrite(*n2, 3);
	 n1->push_dendrite(*n3, -2);
	 n1->push_dendrite(*n4, 21);
	 n2->push_dendrite(*n5, -20);
	 n2->push_dendrite(*n6, 12);

	 auto start = std::chrono::high_resolution_clock::now();

	 for (int i = 0; i < 1000000; ++i) {

	 n0->input(32);

	 std::for_each(net.begin(), net.end(), [&](auto ptr) {
	 ptr->fire();
	 });

	 std::for_each(net.begin(), net.end(), [&](auto ptr) {
	 ptr->swap_inputs();
	 });
	 }

	 auto finish = std::chrono::high_resolution_clock::now();
	 std::chrono::duration<double, std::micro> elapsed = finish - start;

	 std::cout << n0->to_string() << "\n";
	 std::cout << n1->to_string() << "\n";
	 std::cout << n2->to_string() << "\n";
	 std::cout << n3->to_string() << "\n";
	 std::cout << n4->to_string() << "\n";
	 std::cout << n5->to_string() << "\n";
	 std::cout << n6->to_string() << "\n";
	 std::cout << elapsed.count() << "\n\n----------\n\n";*/
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

	for (int i = 0; i < 10000000000; ++i) {

		net.get_vertex(0).input(3.2f);

		net.for_each_by_vert(
				[&](neuron &n, std::vector<std::pair<int, float> > &edges) {
					if (n.fire()) {
						std::for_each(edges.begin(), edges.end(), [&](auto &p) {
							net.get_vertex(p.first).input(p.second);
						});
					}
				});

//		std::cout << net.get_vertex(0).to_string() << "\n";
//		std::cout << net.get_vertex(1).to_string() << "\n";
//		std::cout << net.get_vertex(2).to_string() << "\n";
//		std::cout << net.get_vertex(3).to_string() << "\n";
//		std::cout << net.get_vertex(4).to_string() << "\n";
//		std::cout << net.get_vertex(5).to_string() << "\n";
//		std::cout << net.get_vertex(6).to_string() << "\n";
//		std::cout << "->\n";

		net.for_each_vert([](neuron &n) {
			n.swap_inputs();
		});

//		std::cout << net.get_vertex(0).to_string() << "\n";
//		std::cout << net.get_vertex(1).to_string() << "\n";
//		std::cout << net.get_vertex(2).to_string() << "\n";
//		std::cout << net.get_vertex(3).to_string() << "\n";
//		std::cout << net.get_vertex(4).to_string() << "\n";
//		std::cout << net.get_vertex(5).to_string() << "\n";
//		std::cout << net.get_vertex(6).to_string() << "\n";
//		std::cout << "----------\n";
	}

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> elapsed = finish - start;

	std::cout << net.get_vertex(0).to_string() << "\n";
	std::cout << net.get_vertex(1).to_string() << "\n";
	std::cout << net.get_vertex(2).to_string() << "\n";
	std::cout << net.get_vertex(3).to_string() << "\n";
	std::cout << net.get_vertex(4).to_string() << "\n";
	std::cout << net.get_vertex(5).to_string() << "\n";
	std::cout << net.get_vertex(6).to_string() << "\n";
	std::cout << elapsed.count() << "\n\n----------\n\n";
}

int main() {
	test();
	speed_test();
	run_tests();
	test_graph();

	return 0;
}

