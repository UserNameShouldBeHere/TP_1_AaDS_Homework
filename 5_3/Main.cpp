#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "Graph.h"

#define _USE_MATH_DEFINES
#include <math.h>

std::vector<std::pair<float, float>> generate_points(int count) {
    float x, y;

    std::vector<std::pair<float, float>> result;

    for (int i = 0; i < count; i++) {
        float u = rand() * 1.0 / RAND_MAX;
        float v = rand() * 1.0 / RAND_MAX;

        x = std::cos(2.0 * M_PI * u) * std::sqrt(-2.0 * std::log(v));
        y = std::sin(2.0 * M_PI * u) * std::sqrt(-2.0 * std::log(v));
        result.push_back(std::pair<float, float>(x, y));
    }

    return result;
}

float get_optimal_route(std::vector<std::pair<float, float>> points) {
    float route_length = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            route_length += std::sqrt(std::pow(points[j].first - points[i].first, 2) + std::pow(points[j].second - points[i].second, 2));
        }
    }

    return route_length;
}

float count_mst(std::vector<std::pair<float, float>> points) {
    WeightedListGraph* graph = new WeightedListGraph(points.size());

    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            //float tmp = std::sqrt(std::pow(points[j].first - points[i].first, 2) + std::pow(points[j].second - points[i].second, 2));
            //std::cout << tmp << std::endl;
            graph->AddEdge(i, j, std::sqrt(std::pow(points[j].first - points[i].first, 2) + std::pow(points[j].second - points[i].second, 2)));
        }
    }

    float result = graph->Create_mst();

    delete graph;

    return result;
}

float count_p(std::vector<std::pair<float, float>> points) {
    float mst = count_mst(points);
    float optimal_route = get_optimal_route(points);

    //std::cout << "MST: " << mst << std::endl;
    //std::cout << "Optimal route: " << optimal_route << std::endl;

    return std::max(optimal_route / mst, mst / optimal_route);
}

float count_x(std::vector<std::pair<float, float>> points) {
    float x = 0;
    for (int i = 0; i < 10; i++) {
        x += count_p(points);
    }
    
    return x / 10;
}

float count_deviation(std::vector<std::pair<float, float>> points) {
    float x = count_x(points);
    float sum_x = 0;
    float deviation;
    for (int i = 0; i < 10; i++) {
        sum_x += std::pow(count_p(points) - x, 2);
    }

    float tmp = std::sqrt(0.1);
    deviation = tmp * sum_x;

    //std::cout << "X: " << x << std::endl;
    //std::cout << "Deviation: " << deviation << std::endl;
    
    return deviation;
}

int main() {
    srand(time(NULL));

    for (int i = 2; i <= 10; i++) {
        std::vector<std::pair<float, float>> points;
        float optimal_route, mst;
        float approach;
        std::vector<float> xs;
        float x = 0, deviation = 0;
        float multiple_approach = 0;

        std::cout << "======== " << i << " ========" << std::endl;

        for (int j = 0; j < 10; j++) {
            points = generate_points(i);
            optimal_route = get_optimal_route(points);
            mst = count_mst(points);
            approach = std::max(optimal_route / mst, mst / optimal_route);
            multiple_approach += approach;
            xs.push_back(approach);
        }

        std::cout << "Approach: " << multiple_approach / 10 << std::endl;

        for (float val : xs)
            x += val;
        x *= 0.1;

        for (float val : xs)
            deviation += std::pow(val - x, 2);
        deviation *= sqrt(0.1);

        std::cout << "X: " << x << std::endl;
        std::cout << "Deviation: " << deviation << std::endl;
    }
    
    return 0;
}