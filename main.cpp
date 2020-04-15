#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <utility>

const int inf = 1e9;

struct Way {
    int period;
    std::vector<int> lonely_stations;
    std::map<int, std::pair<std::pair<int, int>, std::pair<int, int>>>;
};

class UndergroundMap {
public:
    void SetWaysNumber(int number);
    void AddEdge(int way_number, int from, int to, int time);
    std::vector<int> CountPaths(int station);
    int GetMaxStationNumber() { return max_station_number_; };
    int GetWayNumber(int first_station, int second_station);
    int GetWayPeriod(int way_number);
    void GetNextVertices(int vertex, std::vector<std::pair<int, int>>& nextVertices) const;

private:
    std::vector<Way> ways_;
    int max_station_number_ = -1; // update value in AddEdge
};

void UndergroundMap::SetWaysNumber(int number) {
    ways_.resize(number);
}

void UndergroundMap::AddEdge(int way_number, int from, int to, int time) {
    // realisation
}

std::vector<int> UndergroundMap::CountPaths(int station) { // count ways which consist 'station'
    // realisation
}

int UndergroundMap::GetWayNumber(int first_station, int second_station) { // search the number which consists the edge between first_station and second_station
    // realisation
}

int UndergroundMap::GetWayPeriod(int way_number) {
    return ways_[way_number].period;
}

void UndergroundMap::GetNextVertices(int vertex, std::vector<std::pair<int, int>> &nextVertices) const { // get neighbours of the current station
    // realisation
}

class Dijkstra {
public:
    Dijkstra(UndergroundMap* curr_map) : curr_map_(curr_map) {};
    int Solve(int from, int to, int time_begin);

private:
    UndergroundMap* curr_map_;
    std::set<std::pair<int, int>> nearest_vertices_;
    std::vector<int> min_ways_;
    std::vector<bool> visited;

    int CountTimeFromTo(int from, int to, int way_number);
    int CountWaitingTime(int curr_time, int time_from_to, int period);
};

int Dijkstra::CountTimeFromTo(int from, int to, int way_number) { // count time which train needs to achieve 'to' starting from 'from' on the way 'way_number'
    // realisation
}

int Dijkstra::CountWaitingTime(int curr_time, int time_from_to, int period) {
    return (time_from_to > curr_time ? time_from_to - curr_time : (curr_time - time_from_to) % period);
}

int Dijkstra::Solve(int from, int to, int curr_time) {
    for (int i = 0; i < curr_map_ -> GetMaxStationNumber(); ++i) {
        min_ways_.push_back(inf);
        visited.push_back(false);
    }
    min_ways_[from] = 0;
    nearest_vertices_.insert(std::make_pair(0, from));
    while (nearest_vertices_.empty() == false) {
        std::pair<int, int> currVertex = *nearest_vertices_.begin();
        nearest_vertices_.erase(nearest_vertices_.begin());
        visited[currVertex.second] = true;
        std::vector<std::pair<int, int>> nextGeneration;
        curr_map_ -> GetNextVertices(currVertex.second, nextGeneration);
        for (int i = 0; i < nextGeneration.size(); ++i) {
            if (visited[nextGeneration[i].second] == false) {
                int way_number = curr_map_ -> GetWayNumber(currVertex.second, nextGeneration[i].second);
                int time_from_to = CountTimeFromTo(currVertex.second, nextGeneration[i].second, way_number); // t1 and t2 in README
                int additional_time = CountWaitingTime(curr_time, time_from_to, curr_map_ -> GetWayPeriod(way_number));
                if (min_ways_[nextGeneration[i].second] > min_ways_[currVertex.second] + nextGeneration[i].first + additional_time) {
                    if (min_ways_[nextGeneration[i].second] != inf) {
                        nearest_vertices_.erase(std::make_pair(min_ways_[nextGeneration[i].second], nextGeneration[i].second));
                    }
                    min_ways_[nextGeneration[i].second] = min_ways_[currVertex.second] + nextGeneration[i].first + additional_time;
                    nearest_vertices_.insert(std::make_pair(min_ways_[nextGeneration[i].second], nextGeneration[i].second));
                }
            }
        }
    }
    return min_ways_[to];
}

void MakeMap(UndergroundMap& curr_map) {
    //making map
    //curr_map.SetWaysNumber(...);
    //curr_map.AddEdge(...);
}

int main() {
    UndergroundMap curr_map;
    MakeMap(curr_map);
    Dijkstra FindShortestWay(&curr_map);
    //std::cout << FindShortestWay.Solve(...);
    return 0;
}