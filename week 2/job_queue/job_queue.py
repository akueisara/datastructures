import Queue as Q

class JobQueue:
    def read_data(self):
        self.num_workers, m = map(int, raw_input().split())
        self.jobs = list(map(int, raw_input().split()))
        assert m == len(self.jobs)

    def write_response(self):
        for i in range(len(self.jobs)):
          print(self.assigned_workers[i], self.start_times[i]) 

    def assign_jobs(self):
        # TODO: replace this code with a faster algorithm.
        self.assigned_workers = [None] * len(self.jobs)
        self.start_times = [None] * len(self.jobs)
        next_free_time = [0] * self.num_workers
        for i in range(len(self.jobs)):
          next_worker = 0
          for j in range(self.num_workers):
            if next_free_time[j] < next_free_time[next_worker]:
              next_worker = j
          self.assigned_workers[i] = next_worker
          self.start_times[i] = next_free_time[next_worker]
          next_free_time[next_worker] += self.jobs[i]
          
    def fast_assign_jobs(self):
        self.assigned_workers = [None] * len(self.jobs)
        self.start_times = [None] * len(self.jobs)
        pq = Q.PriorityQueue()
        for i in range(self.num_workers):
            pq.put(self.Worker(i))
        for i in range(len(self.jobs)):
            freeThread = pq.get()
            self.assigned_workers[i] = freeThread.id
            self.start_times[i] = freeThread.nextFreeTime
            freeThread.nextFreeTime += self.jobs[i]
            pq.put(freeThread);

    class Worker(object):
        def __init__(self, id):
            self.id = id
            self.nextFreeTime = 0
        def __cmp__(self, other):
            if(self.nextFreeTime == other.nextFreeTime):
                return cmp(self.id, other.id)
            else:
                return cmp(self.nextFreeTime, other.nextFreeTime)

    def solve(self):
        self.read_data()
        # self.assign_jobs()
        self.fast_assign_jobs()
        self.write_response()

if __name__ == '__main__':
    job_queue = JobQueue()
    job_queue.solve()

