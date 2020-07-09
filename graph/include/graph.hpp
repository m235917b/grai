/*
 * graph.hpp
 *
 *  Created on: 04.07.2020
 *      Author: Marvin Bergmann
 */

#ifndef graph_INCLUDE_graph_HPP_
#define graph_INCLUDE_graph_HPP_

#include <vector>
#include <functional>

template<class V, class W>
class graph {
private:
	std::vector<V> vertices;
	std::vector<std::vector<std::pair<std::size_t, W> > > edges;

	graph() :
			vertices(std::vector<V>()), edges(
					std::vector<std::vector<std::pair<std::size_t, W> > >()) {
	}

	graph(const std::vector<V> &vertices,
			const std::vector<std::vector<std::pair<std::size_t, W> > > &edges) :
			vertices(vertices), edges(edges) {
	}

protected:

public:
	~graph() noexcept = default;

	graph(const graph<V, W> &that) = default;

	graph(graph<V, W> &&that) noexcept = default;

	graph<V, W>& operator=(const graph<V, W> &that) = default;

	graph<V, W>& operator=(graph<V, W> &&that) noexcept = default;

	bool operator==(const graph<V, W> &that);

	bool operator!=(const graph<V, W> &that);

	void swap(graph<V, W> &that) noexcept {
		std::swap(vertices, that.vertices);
		std::swap(edges, that.edges);
	}

	static graph<V, W> empty() {
		return graph<V, W>();
	}

	static graph<V, W> from_vertices(std::vector<V> &vertices) {
		return graph<V, W>(vertices,
				std::vector<std::vector<std::pair<std::size_t, W> > >(
						vertices.size()));
	}

	std::pair<std::reference_wrapper<V>,
			std::reference_wrapper<std::vector<std::pair<std::size_t, W>>>> operator[](
			std::size_t index) {
		return std::make_pair(std::ref(vertices[index]), std::ref(edges[index]));
	}

	V& get_vertex(std::size_t index) {
		return vertices[index];
	}

	std::vector<std::pair<std::size_t, W>>& get_edges(std::size_t index) {
		return edges[index];
	}

	bool insert(const V &vertex,
			const std::vector<std::pair<std::size_t, W>> &edges = { });

	bool erase(std::size_t index);

	bool add_edge(std::size_t from, std::size_t to, W weight);

	bool remove_edge(std::size_t from, std::size_t to);

	bool is_empty() {
		return vertices.empty();
	}

	auto begin() {
		return vertices.begin();
	}

	auto end() {
		return vertices.end();
	}

	auto begin_edges() {
		return edges.begin();
	}

	auto end_edges() {
		return edges.end();
	}

	std::size_t size() {
		return vertices.size();
	}

	void for_each_edge(std::function<void(V &from, V &to, W &weight)> f);

	void for_each_vert(std::function<void(V &vertex)> f);

	void for_each(
			std::function<
					void(V &n, std::vector<std::pair<std::size_t, W> > &edges)>);
};

template<class V, class W>
void swap(graph<V, W> &g1, graph<V, W> &g2) {
	std::swap(g1.vertices, g2.vertices);
	std::swap(g2.edges, g2.edges);
}

template<class V, class W>
bool graph<V, W>::operator==(const graph<V, W> &that) {
	return vertices == that.vertices && edges == that.edges;
}

template<class V, class W>
bool graph<V, W>::operator!=(const graph<V, W> &that) {
	return vertices != that.vertices || edges != that.edges;
}

template<class V, class W>
bool graph<V, W>::insert(const V &vertex,
		const std::vector<std::pair<std::size_t, W>> &edges) {
	for (auto &e : edges) {
		if (e.first > vertices.size()) {
			return false;
		}
	}

	vertices.push_back(vertex);
	this->edges.push_back(edges);

	return false;
}

template<class V, class W>
bool graph<V, W>::erase(std::size_t index) {
	if (index < vertices.size()) {
		//erase vertex
		vertices.erase(vertices.begin() + index);
		edges.erase(edges.begin() + index);

		for (auto &e : edges) {
			//remove edges to index
			e.erase(std::remove_if(e.begin(), e.end(), [&](auto &p) {
				return p.first == index;
			}), e.end());

			//correct indices from other edges
			for (auto &p : e) {
				if (p.first > index) {
					p.first -= 1;
				}
			}
		}

		return true;
	}

	return false;
}

template<class V, class W>
bool graph<V, W>::add_edge(std::size_t from, std::size_t to, W weight) {
	if (from < vertices.size() && to < vertices.size()) {
		edges[from].push_back(std::pair<std::size_t, W> { to, weight });

		return true;
	}

	return false;
}

template<class V, class W>
bool graph<V, W>::remove_edge(std::size_t from, std::size_t to) {
	if (from < vertices.size() && to < vertices.size()) {
		edges[from].erase(
				std::remove_if(edges[from].begin(), edges[from].end(),
						[&](auto &p) {
							return p.first == to;
						}));

		return true;
	}

	return false;
}

template<class V, class W>
void graph<V, W>::for_each_edge(
		std::function<void(V &from, V &to, W &weight)> f) {
	for (auto i = edges.begin(); i != edges.end(); ++i) {
		for (auto j = i->begin(); j != i->end(); ++j) {
			f(vertices[std::distance(edges.begin(), i)], vertices[j->first],
					j->second);
		}
	}
}

template<class V, class W>
void graph<V, W>::for_each_vert(std::function<void(V &vertex)> f) {
	for (auto &i : vertices) {
		f(i);
	}
}

template<class V, class W>
void graph<V, W>::for_each(
		std::function<void(V &n, std::vector<std::pair<std::size_t, W> > &edges)> f) {
	for (int i = vertices.size() - 1; i >= 0; --i) {
		f(vertices[i], edges[i]);
	}
}

#endif /* graph_INCLUDE_graph_HPP_ */
