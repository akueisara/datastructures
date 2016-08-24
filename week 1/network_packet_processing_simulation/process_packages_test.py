class Request:
    def __init__(self, arrival_time, process_time):
        self.arrival_time = arrival_time
        self.process_time = process_time

class Response:
    def __init__(self, dropped, start_time):
        self.dropped = dropped
        self.start_time = start_time

class Buffer:
    def __init__(self, size):
        self.size = size
        self.finish_time_ = []

    def Process(self, request):
        # write your code here
        while self.finish_time_:
            if self.finish_time_[0] <= request.arrival_time:
                self.finish_time_.pop(0)
            else:
                break
        if len(self.finish_time_) == self.size:
            return Response(True, -1)
        if not self.finish_time_:
            self.finish_time_ = [request.arrival_time + request.process_time]
            return Response(False, request.arrival_time)
        last_element = self.finish_time_[-1]
        self.finish_time_.append(last_element + request.process_time)
        return Response(False, last_element)

def ReadRequests(count, reader):
    requests = []
    for i in range(count):
        arrival_time, process_time = map(int, reader.readline().strip().split())
        requests.append(Request(arrival_time, process_time))
    return requests

def ProcessRequests(requests, buffer):
    responses = []
    for request in requests:
        responses.append(buffer.Process(request))
    return responses

def PrintResponses(responses):
    for response in responses:
        print(response.start_time if not response.dropped else -1)

def Compare(responses, result_responses):
    for i in range(len(responses)):
        if(responses[i].start_time != result_responses[i].start_time):
            return False
    return True

if __name__ == "__main__":
    for i in range(1,23):
        if i < 10:
            fo = open("./tests/0" + str(i), "r")
            fo2 = open("./tests/0" + str(i) + ".a", "r")
        else:
            fo = open("./tests/" + str(i), "r")
            fo2 = open("./tests/" + str(i) + ".a", "r")

        size, count = map(int, fo.readline().strip().split())
        requests = ReadRequests(count, fo)
        fo.close()
        buffer = Buffer(size)
        responses = ProcessRequests(requests, buffer)
		
        result_responses = []
        for j in range(count):
            line = map(int, fo2.readline().strip().split())
            if(line[0] == -1):
                result_responses.append(Response(True, -1))
            else:
                result_responses.append(Response(False, line[0]))
        fo2.close()

        if Compare(responses, result_responses):
            print str(i) + " Pass"
