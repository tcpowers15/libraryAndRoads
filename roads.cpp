#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstring>

using namespace std;

void create(int element, vector<int> &parent) {
  parent[element] = element;
}

int findParent(int element, vector<int> &parent) {
  if (element != parent[element]) {
    parent[element] = findParent(parent[element], parent);
  }
  return parent[element];
}

void merge(int x1, int x2, vector<int> &parent, int &count) {
  int p1 = findParent(x1, parent);
  int p2 = findParent(x2, parent);

  if (p1 != p2) {
    count--;
    parent[p1] = parent[p2];
  }
}

void disjoints(vector<int> &parent, vector<vector<int>> graph, int &count) {
  for (int i = 0; i < graph.size(); ++i) {
    for (int j = 0; j < graph[i].size(); ++j) {
      merge(i, graph[i][j], parent, count);
    }
  }
}

int main() {
  int x; cin >> x;

  while (x-- > 0) {
    int roads, c1, c2, cities, libscost, roadcost;
    scanf("%d %d %d %d", &cities, &roads, &libscost, &roadcost);

    if (roadcost >= libscost || roads == 0) {
      printf("%lld\n", (long long int ) libscost*cities);
      while (roads-- > 0) scanf("%d %d", &c1, &c2);
      continue;
    }

    vector<vector<int>> city_map(cities);
    for (int i = 0; i < roads; i++) {
      scanf(" %d %d ", &c1, &c2);
      city_map[c1 - 1].push_back(c2 - 1);
      city_map[c2 - 1].push_back(c1 - 1);
    }

    vector<int> parent(cities);
    for (int i = 0; i < cities; ++i) {
      create(i, parent);
    }

    int count = cities;
    disjoints(parent, city_map, count);

    vector<int> set_lengths(cities);
    for_each(parent.begin(), parent.end(), [&](int val){
      set_lengths[findParent(val, parent)]++;
    });

    long int cost = 0;
    for_each(set_lengths.begin(), set_lengths.end(), [&](int length){
      if (length == 0) return;
      cost += roadcost * (length-1) + libscost;
    });

    cout << cost << endl;
  }
}
