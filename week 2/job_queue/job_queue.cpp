#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;

class Worker {
	public:
		int id;
        long long nextFreeTime;
	    Worker (int id) {
            this->id = id;
            nextFreeTime = 0;
        }
};

struct WorkerCompare {
	bool operator()(const Worker &w1, const Worker &w2) const {
		if(w1.nextFreeTime == w2.nextFreeTime)
			return w1.id > w2.id;
		else
            return w1.nextFreeTime > w2.nextFreeTime;
	}
};

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;

  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_workers_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_worker = 0;
      for (int j = 0; j < num_workers_; ++j) {
        if (next_free_time[j] < next_free_time[next_worker])
          next_worker = j;
      }
      assigned_workers_[i] = next_worker;
      start_times_[i] = next_free_time[next_worker];
      next_free_time[next_worker] += duration;
    }
  }
  
  void FastAssignJobs() {
	assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
	priority_queue<Worker, vector<Worker>, WorkerCompare> pq;
	for(int i = 0; i < num_workers_; i++) {
		pq.push(Worker(i));

	}
	for (int i = 0; i < jobs_.size(); i++) {
		Worker freeThread = pq.top();
		pq.pop();
		assigned_workers_[i] = freeThread.id;
		start_times_[i] = freeThread.nextFreeTime;
		freeThread.nextFreeTime += jobs_[i];
		pq.push(freeThread);
	}
  }
  
 public:
  void Solve() {
    ReadData();
    // AssignJobs();
	FastAssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
