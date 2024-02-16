#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <utility>
#include <vector>

/*void insert_edge(std::array<std::vector<int>, 50>& adj_list, int u, int v);

std::vector<std::array<std::vector<int>, 50>> read_graphs(std::istringstream& input) {
  std::vector<std::array<std::vector<int>, 50>> graphs;

  auto n_verts = 0;
  input >> n_verts;

  while (n_verts > 0) {
    auto n_edges = 0;
    input >> n_edges;
    std::array<std::vector<int>, 50> adj_list;

    for (auto edge = 0; edge < n_edges; ++edge) {
      auto u = 0;
      auto v = 0;

      input >> u;
      input >> v;

      insert_edge(adj_list, u, v);
    }

    graphs.push_back(adj_list);
    input >> n_verts;
  }

  return graphs;
}

void insert_edge(std::array<std::vector<int>, 50>& adj_list, int u, int v) {
  adj_list[u].push_back(v);
  adj_list[v].push_back(u);
}

int get_next_color() {
  static int next_color = 1;
  next_color = (next_color % 2) + 1;
  return next_color;
}

bool is_colorable(const std::array<std::vector<int>, 50> graph, int vertex, int colors[], int color) {
  for (const auto child : graph[vertex]) {
    if (color == colors[child]) {
      return false;
    }
  }

  return true;
}

void colorize(int colors[], int color, int vertex) {
  colors[vertex] = color;
}

void push_undiscovered(std::queue<int>& vertices, int vertex, bool discovered[], const std::array<std::vector<int>, 50>& graph) {
  const auto children = graph[vertex];
  for (const auto child : children) {
    if (!discovered[child]) {
      vertices.push(child);
      discovered[child] = true;
    }
  }
}

bool is_bicolor(const std::array<std::vector<int>, 50>& graph, int size) {

  int colors[50] = {0};
  bool discovered[50] = {false};

  std::queue<int> vertices;
  vertices.push(0);
  discovered[0] = true;

  while (!vertices.empty()) {
    auto curr = vertices.front();
    vertices.pop();

    auto color = get_next_color();
    if (is_colorable(graph, curr, colors, color)) {
       colorize(colors, color, curr);
    } else {
      return false;
     }

    push_undiscovered(vertices, curr, discovered, graph);
  }

  return true;
}

bool is_valid(const std::set<std::string>& discovered, const std::string& vertex) {
  return discovered.find(vertex) == discovered.end();
}

std::string digit_rotate_left(std::string n_str, int digit) {
  --n_str[digit];

  if (n_str[digit] < '0') {
    n_str[digit] = '9';
  }
  
  return n_str;
}

std::string digit_rotate_right(std::string n_str, int digit) {
  ++n_str[digit];

  if (n_str[digit] > '9') {
    n_str[digit] = '0';
  }
  
  return n_str;
}

int min_presses_transform(const std::string& init, const std::string& tgt) {
  std::set<std::string> discovered;
  std::unordered_map<std::string, int> presses;

  std::queue<std::string> vertices;
  vertices.push(init);
  presses[init] = 0;

  while (!vertices.empty()) {
    const auto curr = vertices.front();
    vertices.pop();

    if (curr == tgt) {
      return presses[curr];
    } else {
      for (auto digit = 0; digit <= 3; ++digit) {
        const auto rotations = {digit_rotate_left, digit_rotate_right};

        for (const auto rotation : rotations) {
          const auto rotated_digit = rotation(curr, digit);

          if (is_valid(discovered, rotated_digit)) {
            discovered.insert(rotated_digit);
            vertices.push(rotated_digit);
            presses[rotated_digit] = presses[curr] + 1;
          }
        }
      }
    }
  }

  return -1;
}

using Vertex = std::string;

struct Edge {
  Vertex u;
  Vertex v;
  int weight;
};

using Graph = std::unordered_map<Vertex, std::vector<Edge>>;

void insert_edge(Graph& graph, const Vertex& u, const Vertex& v, int weight) {
  if (graph.find(u) == graph.end()) {
    graph.insert({u, {}});
  }

  if (graph.find(v) == graph.end()) {
    graph.insert({v, {}});
  }

  Edge edge {u, v, weight};
  Edge recip_edge {v, u, weight};

  graph[u].push_back(edge);
  graph[v].push_back(recip_edge);
}

int compute_max_cost(const Graph& graph, const Vertex& u, const Vertex& v) {
  std::unordered_map<Vertex, int> costs;
  std::unordered_set<Vertex> discovered;
  
  std::stack<Vertex> vertices;

  vertices.push(u);
  discovered.insert(u);
  costs.insert({u, std::numeric_limits<int>::max()});

  while (!vertices.empty()) {
    const auto curr = vertices.top();
    vertices.pop();

    if (curr == v)
      continue;

    for (const auto& edge : graph.find(curr)->second) {
      // update even if not pushing
      if (costs.find(edge.v) == costs.end()) {
        costs.insert({edge.v, 0});
      }

      auto& v_cost = costs.find(edge.v)->second;
      const auto parent_cost = costs.find(edge.u)->second;
      const auto tmp = std::min(parent_cost, edge.weight);

      if (discovered.find(edge.v) == discovered.end() || (tmp > v_cost)) {
        vertices.push(edge.v);
        discovered.insert(edge.v);
      }

      v_cost = std::max(tmp, v_cost);
    }

  }

  return costs[v];
}

int min_num_trips(const Graph& graph, const Vertex& u, const Vertex& v, int total_pax) {
  const auto max_cost = compute_max_cost(graph, u, v);
  const auto max_pax_trip = max_cost - 1;
  const auto num_trips = (total_pax / max_pax_trip) + 1;

  return num_trips;
}

template<typename T>
struct Vertex {
  std::string name;
  T data;

  bool operator==(const Vertex& v) const {
    return name == v.name;
  }
};

template<>
struct std::hash<Vertex<Face>> {
  std::size_t operator()(const Vertex<Face>& v) const noexcept {
    std::size_t h1 = std::hash<std::string>{}(v.data.id);
    return h1;
  }
};

template<typename T>
struct Edge {
  Vertex<T> u;
  Vertex<T> v;
};

template<typename T>
class Graph {
 public:

  void AddVertex(const Vertex<T>& u);
  void AddEdge(const Vertex<T>& u, const Vertex<T>& v);

  std::vector<Vertex<T>> GetAllVertices() const;

 private:
  std::unordered_map<Vertex<T>, std::vector<Edge<T>>> m_graph;
};

template<typename T>
void Graph<T>::AddVertex(const Vertex<T>& u) {
  m_graph.insert({u, {}});
}

template<typename T>
void Graph<T>::AddEdge(const Vertex<T>& u, const Vertex<T>& v) {
  const auto u_it = m_graph.find(u);
  const auto v_it = m_graph.find(v);

  u_it->second.push_back({u, v});
  v_it->second.push_back({v, u});
}

template<typename T>
std::vector<Vertex<T>> Graph<T>::GetAllVertices() const {
  std::vector<Vertex<T>> vertices;

  for (const auto& pair : m_graph) {
    vertices.push_back(pair.first);
  }

  return vertices;
}
*/

enum FaceType {
  FRONT,
  BACK,
  LEFT,
  RIGHT,
  TOP,
  BOTTOM
};

struct Face {
  FaceType type;
  int value;
};

struct Cube {
  int id;
  std::vector<Face> faces;
};

std::string faceTypeToString(FaceType type) {
  switch (type) {
    case 0:
      return "front";
      break;
    case 1:
      return "back";
      break;
    case 2:
      return "left";
      break;
    case 3:
      return "right";
      break;
    case 4:
      return "top";
      break;
    case 5:
      return "bottom";
      break;
  };

  return "ERROR";
}


FaceType opposite(FaceType face) {
  switch (face) {
    case FRONT:
      return BACK;
      break;
    case BACK:
      return FRONT;
      break;
    case LEFT:
      return RIGHT;
      break;
    case RIGHT:
      return LEFT;
      break;
    case TOP:
      return BOTTOM;
      break;
    case BOTTOM:
      return TOP;
      break;
  };

  return FRONT;
}

static int best = 0;
static std::vector<std::pair<Cube, Face>> bestTower;

bool isValid(const Face& bottomCubeFace, const Cube& topCube, const Face& topCubeFace) {
  const auto opp = topCube.faces[opposite(topCubeFace.type)];
  return bottomCubeFace.value == opp.value;
}

void recurse(const std::vector<Cube>& cubes, int cubeIdx, const Face& bottomCubeFace, std::vector<std::pair<Cube, Face>> currTower, int depth) {
  depth += 1;
  currTower.insert(currTower.begin(), {cubes[cubeIdx], bottomCubeFace});

  if (depth > best) {
    best = depth;
    bestTower = currTower;
  }

  for (auto idx = cubeIdx + 1; idx < cubes.size(); ++idx) {
    for (const auto& topCubeFace : cubes[idx].faces) {
      if (isValid(bottomCubeFace, cubes[idx], topCubeFace)) {
        recurse(cubes, idx, topCubeFace, currTower,depth);
      }
    }
  }

  best = std::max(depth, best);
}

int main(int argv, char** argc) {

  //std::istringstream ss {"3\n2\n0 1\n1 2\n3\n3\n0 1\n1 2\n2 0\n0"};
  //std::istringstream ss {"3\n3\n0 1\n1 2\n2 0\n0"};
  /*const auto graphs = read_graphs(ss);
  for (const auto& graph : graphs) {
    std::cout << is_bicolor(graph, 3) << std::endl;
  }*/

  /*std::cout << min_presses_transform("0000", "0001") << std::endl;
  std::cout << min_presses_transform("0000", "0002") << std::endl;
  std::cout << min_presses_transform("0000", "9999") << std::endl;
  std::cout << min_presses_transform("0000", "5000") << std::endl;*/

  /*Graph g;
  insert_edge(g, "1", "2", 30);
  insert_edge(g, "1", "3", 15);
  insert_edge(g, "1", "4", 10);
  insert_edge(g, "2", "4", 25);
  insert_edge(g, "2", "5", 60);
  insert_edge(g, "3", "4", 40);
  insert_edge(g, "3", "6", 20);
  insert_edge(g, "4", "7", 35);
  insert_edge(g, "5", "7", 20);
  insert_edge(g, "6", "7", 30);

  std::cout << min_num_trips(g, "1", "7", 99) << std::endl;*/

  std::vector<Cube> cubes;

  int nCubes = 0;
  while (std::cin >> nCubes) {
    for (auto cube = 1; cube <= nCubes; ++cube) {
      int faceValue = 0;
      Cube c;
      const auto cubeStr = std::to_string(cube);

      c.id = cube;
      for (auto faceIndex = 0; faceIndex < 6; ++faceIndex) {
        std::cin >> faceValue;
        const auto faceIndexStr = faceTypeToString(static_cast<FaceType>(faceIndex));
        c.faces.push_back({static_cast<FaceType>(faceIndex), faceValue});
      }

      cubes.push_back(c);
    }
  }

  std::reverse(cubes.begin(), cubes.end());

 for (auto i = 0; i < cubes.size(); ++i) {
    for (const auto& f: cubes[i].faces) {
      recurse(cubes, i, f, {}, 0);
    }
  }
  std::cout << "BEST: " << best << std::endl;
  for (const auto& pair : bestTower) {
    std::cout << pair.first.id << " " << faceTypeToString(pair.second.type) << std::endl;
  }

  return 0;
}
