// Network simplex wrapper
//   calling integer version:
//   so all costs are multiplied by a multiplier

#include <lemon/maps.h>
#include <lemon/network_simplex.h>
#include <lemon/list_graph.h>

#include <chrono>
#include <iostream>
#include <random>
#include <cassert>

#include <cmath>

const double MULTIPLIER = 1000.0; //so we can work with ints,
//even when capacities/costs are doubles

int n, m;
double temp;

int main() {
	int case_number = 0;
	double total_solve_time = 0;
	while(scanf("%d%d", &n, &m) == 2) {
		case_number++;

		lemon::ListDigraph network;
		auto source = network.addNode();
		auto target = network.addNode();

		std::vector<lemon::ListDigraph::Node> leftNodes(n);
		std::vector<lemon::ListDigraph::Arc> leftArcs(n);
		for (int i = 0; i < n; ++i) {
			leftNodes[i] = network.addNode();
			leftArcs[i] = network.addArc(source, leftNodes[i]);
		}

		std::vector<lemon::ListDigraph::Node> rightNodes(m);
		std::vector<lemon::ListDigraph::Arc> rightArcs(m);
		for (int j = 0; j < m; ++j) {
			rightNodes[j] = network.addNode();
			rightArcs[j] = network.addArc(rightNodes[j], target);
		}

		std::vector<std::vector<lemon::ListDigraph::Arc>> middleArcs(n, std::vector<lemon::ListDigraph::Arc>(m));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				middleArcs[i][j] = network.addArc(leftNodes[i], rightNodes[j]);
			}
		}

//	lemon::ConstMap<lemon::ListDigraph::Arc, int64_t> capacities(1);
		lemon::ListDigraph::ArcMap<int64_t> capacities(network);
		lemon::ListDigraph::ArcMap<int64_t> costs(network);
		for (int i = 0; i < n; ++i) {
			assert(scanf("%lf", &temp) == 1);
			temp *= MULTIPLIER;
			capacities[leftArcs[i]] = static_cast<int64_t>(temp);
		}	
		for (int j = 0; j < m; ++j) {
			assert(scanf("%lf", &temp) == 1);
			temp *= MULTIPLIER;
			capacities[rightArcs[j]] = static_cast<int64_t>(temp);
		}	
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				assert(scanf("%lf", &temp) == 1);
				//if(temp > (1LL << 20)) printf("%d %d %lf\n", i, j, temp);
				temp *= MULTIPLIER;
//if(temp == 0) printf("%d %d\n", i, j);
				costs[middleArcs[i][j]] = static_cast<int64_t>(temp);
//printf("%d\n", costs[middleArcs[i][j]]);
				capacities[middleArcs[i][j]] = 1LL << 60;
			}
		}

		lemon::NetworkSimplex<lemon::ListDigraph, int64_t, int64_t> solver(network);
		solver.upperMap(capacities);
		solver.costMap(costs);
		solver.stSupply(source, target, 1LL << 50);

		auto t1 = std::chrono::high_resolution_clock::now();
		solver.run();
		auto t2 = std::chrono::high_resolution_clock::now();

		double solve_time = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1).count();
		total_solve_time += solve_time;

		double total_flow = 0;
//for(int i = 0; i < n; ++i) printf("left: %d/%d\n", solver.flow(leftArcs[i]), capacities[leftArcs[i]]);
//for(int j = 0; j < m; ++j) printf("right: %d/%d\n", solver.flow(rightArcs[j]), capacities[rightArcs[j]]);
		for (int i = 0; i < n; ++i) {
			total_flow += solver.flow(leftArcs[i]);
		}
		total_flow /= MULTIPLIER;

		double total_cost = double(solver.totalCost()) / MULTIPLIER / MULTIPLIER;
		//printf("%d: Flow = %lf, Cost = %lf, Network Simplex solve time = %lf\n", case_number, total_flow, total_cost, solve_time);
		printf("%lf  %lf\n", total_cost, solve_time);
	}
	printf("Total Network Simplex solve time = %lf\n", total_solve_time);
 	return 0;
}

