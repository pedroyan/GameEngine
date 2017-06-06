#pragma once
#include <list>
#include <unordered_map>
#include <iostream>
#include "PriorityQueue.h"
#include "Vec2.h"

using namespace std;

list<Vec2> FindNeighbors(Vec2 node, int tileWidth, int tileHeight) {
	list<Vec2> neighbors;
	neighbors.push_back(Vec2(node.X + tileWidth, node.Y));
	if (node.X - tileWidth >= 0) {
		neighbors.push_back(Vec2(node.X - tileWidth, node.Y));
	}

	neighbors.push_back(Vec2(node.X, node.Y + tileHeight));
	if (node.Y - tileHeight >= 0) {
		neighbors.push_back(Vec2(node.X, node.Y - tileHeight));
	}

	return neighbors;
}

inline double heuristic(Vec2 a, Vec2 b) {
	return a.GetDistance1(b);
}

struct Vec2Hasher {
	std::size_t operator()(const Vec2& k) const {
		using std::size_t;
		using std::hash;
		using std::string;

		return (53 + hash<int>()(k.X)) * 53 + hash<int>()(k.Y);
	}
};

std::ostream &operator<<(std::ostream &os, Vec2 const &m) {
	return os << "X: " << m.X << " Y: " << m.Y;
}

Vec2 Run(Vec2 start, Vec2 destination, unordered_map<Vec2, Vec2, Vec2Hasher> came_from, unordered_map<Vec2, int, Vec2Hasher> cost_so_far){
	auto current = destination;
	while (current != start) {
		if (came_from[current] == start) {
			return current;
		}

		current = came_from[current];
	}
}

Vec2 Pathfinding(Vec2 start, Vec2 destination) {
	PriorityQueue<Vec2, double> frontier;
	frontier.put(start, 0);
	unordered_map<Vec2, Vec2, Vec2Hasher> came_from;
	unordered_map<Vec2, int, Vec2Hasher> cost_so_far;
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) {
		Vec2 current = frontier.get();

		if (current == destination) {
			break;
		}

		for (auto next : FindNeighbors(current, 1, 1)) {
			double new_cost = cost_so_far[current];
			if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
				cost_so_far[next] = new_cost;
				double priority = new_cost + heuristic(destination, next);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	auto next = Run(start, destination, came_from, cost_so_far);
	cout << next << endl;

	return next;
}

Vec2 NextMove(Vec2 start, Vec2 destination) {
	cout << start << "->" << destination << endl;
	PriorityQueue<Vec2, double> frontier;

	unordered_map<Vec2, Vec2, Vec2Hasher> came_from;
	unordered_map<Vec2, int, Vec2Hasher> cost_so_far;

	for (auto next : FindNeighbors(start, 1, 1)) {
		double new_cost = cost_so_far[start];
		if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
			cost_so_far[next] = new_cost;
			double priority = new_cost + heuristic(destination, next);
			frontier.put(next, priority);
			came_from[next] = start;
		}
	}

	return frontier.get();
}