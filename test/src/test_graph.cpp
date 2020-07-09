/*
 * test_graph.cpp
 *
 *  Created on: 10.07.2020
 *      Author: Marvin Bergmann
 */

#include <iostream>
#include <vector>
#include <functional>
#include <graph.hpp>

std::vector<int> v = { 1, 2, 3 };
auto g = graph<int, int>::from_vertices(v);
std::vector<int> v1 = { 1, 2, 5, 7 };
auto g1 = graph<int, int>::from_vertices(v1);

bool test_init() {
	return g.get_vertex(0) == 1 && g.get_vertex(1) == 2 && g.get_vertex(2) == 3;
}

bool test_add_edge() {
	g.add_edge(0, 1, 1);
	g.add_edge(1, 2, 2);
	g.add_edge(2, 0, 3);
	g.add_edge(2, 1, 4);

	return g.get_edges(0)[0] == std::make_pair<std::size_t, int>(1, 1)
			&& g.get_edges(1)[0] == std::make_pair<std::size_t, int>(2, 2)
			&& g.get_edges(2)[0] == std::make_pair<std::size_t, int>(0, 3)
			&& g.get_edges(2)[1] == std::make_pair<std::size_t, int>(1, 4);
}

bool test_insert_vert() {
	g.insert(4);

	return g.get_vertex(3) == 4 && g.size() == 4;
}

bool test_remove_vert() {
	g.erase(3);

	return g.size() == 3 && test_init();
}

bool test_remove_edge() {
	g.remove_edge(2, 1);

	return g.get_edges(0)[0] == std::make_pair<std::size_t, int>(1, 1)
			&& g.get_edges(1)[0] == std::make_pair<std::size_t, int>(2, 2)
			&& g.get_edges(2)[0] == std::make_pair<std::size_t, int>(0, 3)
			&& g.get_edges(2).size() == 1 && !g.remove_edge(3, 1)
			&& !g.remove_edge(1, 3) && !g.remove_edge(3, 3);
}

bool test_brace_operator() {
	std::vector<std::pair<std::size_t, int>> v = { std::make_pair<std::size_t,
			int>(1, 1) };
	return g[0].first.get() == 1 && g[0].second.get() == v;
}

bool test_empty() {
	return graph<int, int>::empty().is_empty();
}

bool test_for_each_edge() {
	g.for_each_edge([](int &from, int &to, int &weight) {
		weight = 4;
		to = 0;
	});

	return g.get_edges(0)[0] == std::make_pair<std::size_t, int>(1, 4)
			&& g.get_edges(1)[0] == std::make_pair<std::size_t, int>(2, 4)
			&& g.get_edges(2)[0] == std::make_pair<std::size_t, int>(0, 4)
			&& g.get_vertex(0) == 0 && g.get_vertex(1) == 0
			&& g.get_vertex(2) == 0;
}

bool test_for_each_vert() {
	g.for_each_vert([](int &v) {
		v = 10;
	});

	return g.get_vertex(0) == 10 && g.get_vertex(1) == 10
			&& g.get_vertex(2) == 10;
}

bool test_for_each() {
	g.for_each([](int &v, std::vector<std::pair<std::size_t, int>> &e) {
		v = 5;

		for (auto &p : e) {
			p.first = 1;
			p.second = 7;
		}
	});

	return g.get_edges(0)[0] == std::make_pair<std::size_t, int>(1, 7)
			&& g.get_edges(1)[0] == std::make_pair<std::size_t, int>(1, 7)
			&& g.get_edges(2)[0] == std::make_pair<std::size_t, int>(1, 7)
			&& g.get_vertex(0) == 5 && g.get_vertex(1) == 5
			&& g.get_vertex(2) == 5;
}

bool test_equal() {
	return g == g && !(g == g1);
}

bool test_unequal() {
	return g != g1 && !(g != g);
}

bool test_assign() {
	g1 = g;

	return g == g1;
}

bool test_begin() {
	g.get_vertex(1) = -3;

	return *(++g.begin()) == -3;
}

bool test_end() {
	g.get_vertex(2) = -3;

	return *(--g.end()) == -3;
}

bool test_begin_edges() {
	(*(++g.begin_edges()))[0].second = -5;

	return g.get_edges(1)[0].second == -5;
}

bool test_end_edges() {
	(*(--g.end_edges()))[0].second = -4;

	return g.get_edges(2)[0].second == -4;
}

bool test_swap() {
	std::swap(g, g1);

	return g.get_edges(2)[0].second != -4 && g1.get_edges(2)[0].second == -4;
}

// ----------

void run_test(std::string name, std::function<bool()> f) {
	std::cout << name << ": ";
	if (f()) {
		std::cout << "passed!\n";
	} else {
		std::cout << "failed!\n";
	}
}

void run_tests_graph() {
	std::cout << "----- Test Graph -----\n";

	run_test("test_init", test_init);
	run_test("test_add_edge", test_add_edge);
	run_test("test_remove_edge", test_remove_edge);
	run_test("test_insert_vert", test_insert_vert);
	run_test("test_remove_vert", test_remove_vert);
	run_test("test_brace_operator", test_brace_operator);
	run_test("test_empty", test_empty);
	run_test("test_for_each_edge", test_for_each_edge);
	run_test("test_for_each_vert", test_for_each_vert);
	run_test("test_for_each", test_for_each);
	run_test("test_equal", test_equal);
	run_test("test_unequal", test_unequal);
	run_test("test_assign", test_assign);
	run_test("test_begin", test_begin);
	run_test("test_end", test_end);
	run_test("test_begin_edges", test_begin_edges);
	run_test("test_end_edges", test_end_edges);
	run_test("test_swap", test_swap);

	std::cout << "\n";
}
