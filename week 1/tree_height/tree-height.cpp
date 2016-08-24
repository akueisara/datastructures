#include <iostream>
#include <vector>
#include <algorithm>

class TreeHeight {
  int n;             
  std::vector<int> parent;

public:
  void read() {
    std::cin >> n;
    parent.resize(n);
    for (int i = 0; i < n; i++)
      std::cin >> parent[i];
  }
  
  int compute_height() {
	int maxHeight = 0;
	std::vector<int> heights;
	for (int i=0; i<parent.size(); i++) 
		heights.push_back(0);
	for (int vertex = 0; vertex < n; vertex++) {
		if (heights[vertex] != 0)
			continue;
		int height = 0;
		for (int i = vertex; i != -1; i = parent[i]) {
			if (heights[i] != 0) {
				height += heights[i];   
				break;
			}
			height++;
		}
		maxHeight = std::max(maxHeight, height);
		for (int i = vertex; i != -1; i = parent[i]) {
			if (heights[i] != 0)
				break;
			heights[i] = height--;
		}
	}
	return maxHeight;
  }

  int old_compute_height() {
    int maxHeight = 0;
    for (int vertex = 0; vertex < n; vertex++) {
      int height = 0;
      for (int i = vertex; i != -1; i = parent[i])
        height++;
      maxHeight = std::max(maxHeight, height);
    }
    return maxHeight;
  }
};

int main() {
  std::ios_base::sync_with_stdio(0);
  TreeHeight tree;
  tree.read();
  std::cout << tree.compute_height() << std::endl;
}
