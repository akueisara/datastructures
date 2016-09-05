#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    for (int i = 0; i < data_.size(); ++i)
      for (int j = i + 1; j < data_.size(); ++j) {
        if (data_[i] > data_[j]) {
          swap(data_[i], data_[j]);
          swaps_.push_back(make_pair(i, j));
        }
      }
  }
  
  void FastGenerateSwaps() {
	swaps_.clear();
	for (int i = data_.size()/2; i >= 0; i--) {
		SiftDown(i);
	}
  }
  
  void SiftDown(int i) {
	int minIndex = i;
	int l = 2*i + 1;
	if(l < data_.size() && data_[l] < data_[minIndex])
		minIndex = l;
	int r = 2*i + 2;
	if(r < data_.size() && data_[r] < data_[minIndex])
		minIndex = r;
	if(i!=minIndex) {
		swap(data_[i], data_[minIndex]);
		swaps_.push_back(make_pair(i, minIndex));
		SiftDown(minIndex);
	}
  }

 public:
  void Solve() {
    ReadData();
    // GenerateSwaps();
	FastGenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
