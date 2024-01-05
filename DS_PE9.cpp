#include <iostream>
#include <algorithm>
using namespace std;

struct Result {
    int cost;
    int values[100]; // Assuming a maximum size for the array, adjust as needed
};

int N, C;

pair<int, int> graph[100][100]; // Assuming a maximum size for the graph, adjust as needed
int uniqueWeights[100];         // Assuming a maximum size for the weights, adjust as needed

Result calculateCost(int node, int parent) {
    int maxWeight = 0, totalCost = 0, parentWeight = 0;

    for (int i = 0; i < 100 && graph[node][i].first != 0; i++) {
        int adjNode = graph[node][i].first;
        int weight = graph[node][i].second;

        maxWeight = max(maxWeight, weight);
        if (adjNode == parent) parentWeight = weight;
    }

    if (graph[node][1].first != 0) totalCost += C * 2;

    int childValues[100] = {};

    for (int i = 0; i < 100 && graph[node][i].first != 0; i++) {
        int adjNode = graph[node][i].first;
        int weight = graph[node][i].second;

        if (adjNode != parent) {
            Result result = calculateCost(adjNode, node);
            int childCost = result.cost;
            int* values = result.values;

            for (int j = 0; j < 100 && uniqueWeights[j] != 0; j++) {
                childValues[j] += values[j] + uniqueWeights[j] - weight;
            }

            totalCost += childCost;
        }
    }

    int evenCost = totalCost;

    for (int i = 0; i < 100 && uniqueWeights[i] != 0; i++) {
        if (uniqueWeights[i] >= maxWeight) {
            evenCost = min(evenCost, childValues[i] + (parent ? uniqueWeights[i] - parentWeight : 0));
            childValues[i] = min(childValues[i], totalCost);
        } else {
            childValues[i] = totalCost;
        }
    }

    Result result = {evenCost, {}};
    copy(begin(childValues), end(childValues), begin(result.values));

    return result;
}

int main() {
    while (cin >> N >> C) {
        for (int i = 1; i < N; i++) {
            int U, V, S;
            cin >> U >> V >> S;
            graph[U][0] = {V, S};
            graph[V][0] = {U, S};
            uniqueWeights[i - 1] = S;
        }

        sort(uniqueWeights, uniqueWeights + N - 1);
        uniqueWeights.erase(unique(uniqueWeights, uniqueWeights + N - 1), uniqueWeights + N - 1);

        Result result = calculateCost(1, 0);
        cout << result.cost << endl;
    }

    return 0;
}
