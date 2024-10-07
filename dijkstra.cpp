#include <iostream>
#include <map>
#include <set>
#include <utility>

using namespace std;

typedef struct graph {
  map<char, map<char, int>> edges;
} graph;

void graph_add_edge(graph * g, char from, char to, int weight) {
  g->edges[from][to] = weight;
  g->edges[to][from] = weight;
}

map<char, pair<int, char>> graph_dijkstra_shortest_paths(graph * g, char start) {
  map<char, pair<int, char>> table;
  set<char> visited;
  set<char> unvisited;

  unvisited.insert(start);
  table[start] = make_pair(0, ' ');

  while (!unvisited.empty()) {
    char current = *unvisited.begin();
    unvisited.erase(unvisited.begin());

    for (pair<char, int> edge : g->edges[current]) {
      char neighbour = edge.first;

      if (visited.find(neighbour) != visited.end()) continue;

      int weight = edge.second;

      unvisited.insert(neighbour);

      if (table.find(neighbour) == table.end()) {
        table[neighbour] = make_pair(
          table[current].first + weight,
          current
        );

        continue;
      } 

      int current_distance = table[neighbour].first;
      int new_distance = table[current].first + weight;

      if (new_distance < current_distance) {
        table[neighbour] = make_pair(
          new_distance,
          current
        );
      }
    }

    visited.insert(current);
  }

  return table;
}

void graph_print_paths(map<char, pair<int, char>> path) {
  char start = ' ';

  for (pair<char, pair<int, char>> p : path) {
    if (p.second.second == ' ') {
      start = p.first;
      break;
    }
  }

  for (pair<char, pair<int, char>> p : path) {
    cout << p.first << ": " << p.second.first;

    if (p.second.second == ' ') {
      cout << " (starting point)";
    } else if (p.second.second == start) {
      cout << " from start";
    } else {
      cout << " through " << p.second.second;
    }
    
    cout << endl;
  }

  cout << endl;
}

void graph_draw(graph * g) {
  for (pair<char, map<char, int>> p : g->edges) {
    cout << p.first << ": ";

    for (pair<char, int> edge : p.second) {
      cout << edge.first << " (" << edge.second << ") ";
    }

    cout << endl;
  }

  cout << endl;
}

int main () {
  graph g;

  graph_add_edge(&g, 'A', 'B', 13);
  graph_add_edge(&g, 'A', 'C', 9);
  graph_add_edge(&g, 'B', 'C', 9);
  graph_add_edge(&g, 'B', 'D', 1);
  graph_add_edge(&g, 'C', 'D', 1);
  graph_add_edge(&g, 'D', 'E', 5);
  graph_add_edge(&g, 'C', 'E', 3);

  graph_draw(&g);


  map<char, pair<int, char>> paths = graph_dijkstra_shortest_paths(&g, 'A');
  graph_print_paths(paths);

  paths = graph_dijkstra_shortest_paths(&g, 'B');
  graph_print_paths(paths);

  paths = graph_dijkstra_shortest_paths(&g, 'C');
  graph_print_paths(paths);

  paths = graph_dijkstra_shortest_paths(&g, 'D');
  graph_print_paths(paths);

  paths = graph_dijkstra_shortest_paths(&g, 'E');
  graph_print_paths(paths);  

  return 0;
}

