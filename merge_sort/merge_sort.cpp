#include <iostream>
#include <vector>

using namespace std;

long inversions = 0;

void print_vec(vector<int> vec) {
  for (auto& el : vec) {
    cout << el << ", ";
  }
  cout << "\n";
}

vector<int> merge(vector<int> vec1, vector<int> vec2) {
  const int full_size = vec1.size() + vec2.size();
  vector<int> results(full_size, 0);

  int i = full_size - 1;
  while (vec1.size() > 0 && vec2.size() > 0) {
    if (vec1.back() > vec2.back()) {
      results[i] = vec1.back();
      inversions += vec2.size();
      vec1.pop_back();
    }
    else {
      results[i] = vec2.back();
      vec2.pop_back();
    }
    --i;
  }

  vector<int>& remaining = (vec1.size() == 0) ? vec2 : vec1;
  while (remaining.size() > 0) {
    results[i] = remaining.back();
    remaining.pop_back();
    --i;
  }
  return results;
}

vector<int> sort(vector<int> vec) {
  if (vec.size() >= 2) {
    const int mid = vec.size()/2;
    vector<int> first(vec.begin(), vec.begin() + mid);
    vector<int> last(vec.begin() + mid, vec.end());

    auto sorted_first = sort(first);
    auto sorted_last = sort(last);
    return merge(sorted_first, sorted_last);
  }
  else {
    return vec;
  }
}

int main() {
  vector<int> vec {7, 5, 3 ,1};
  // -> [7, 5] and [3, 1]
  // -> [5, 7] and [1, 3] (2 swaps)
  // -> [5, 1, 7, 3]
  // -> [5, 1, 3, 7]
  // -> [1, 5, 3, 7]
  // -> [1, 3, 5, 7]
  // (4 swaps) -> total 6 swaps
  // -> [1, 3, 5, 7] (need to swap 7 past 1, 3 and 5 past 1, 3)
  print_vec(vec);
  print_vec(sort(vec));

  cout << "n inversions: " << inversions << "\n";
  return 1;
}
