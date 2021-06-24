#include "kmeans.h"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <iterator>
#include <mutex>
#include <numeric>
using namespace std;

double Point::Distance(Point& other) {
    return (pow((this->x - other.x), 2) + pow((this->y - other.y), 2));
}

std::istream& operator>>(std::istream& is, Point& pt) {
    is >> pt.x >> pt.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, Point& pt) {
    os << pt.x << " " << pt.y;
    return os;
}
Kmeans::Kmeans(const std::vector<Point>& points,
    const std::vector<Point>& initialCenters) {
    m_numPoints = points.size();
    m_numCenters = initialCenters.size();
    m_points = points;
    m_centers = initialCenters;
}
std::vector<index_t> Kmeans::Run(int maxIterations) {
    using namespace std;
    mutex mymutex;
    // DO NOT MODIFY THESE CODE
    std::vector<index_t> assignment(m_numPoints, 0); // the return vector
    int currIteration = 0;
    std::cout << "Running kmeans with num points = " << m_numPoints
        << ", num centers = " << m_numCenters
        << ", max iterations = " << maxIterations << "...\n";

    for (; currIteration < maxIterations; currIteration++) {
        vector<vector<double>> SUMdistancex(6, move(vector<double>(m_numCenters, 0)));//thread liberated
        vector<vector<double>> SUMdistancey(6, move(vector<double>(m_numCenters, 0)));
        vector<vector<int>> numPointsType(6, move(vector<int>(m_numCenters, 0)));

        // mutlithread
        vector<thread*> threads;
        const int sand = m_numPoints / 6;
        vector<int> startpoints = { 0, sand, sand*2, sand*3,sand*4,sand*5};
        vector<int> endpoints = { sand, sand * 2, sand * 3,sand * 4,sand * 5,sand * 6 };

        for (size_t threadnum = 0; threadnum < 6; threadnum++) {
            threads.push_back(new thread([&, threadnum] {
                for (int index = startpoints[threadnum]; index < endpoints[threadnum];
                    index++) {
                    double least = INFINITY;
                    int type = -1;
                    for (int i = 0; i < m_numCenters; i++) {
                        double distance = m_centers[i].Distance(m_points[index]);
                        if (distance < least) {
                            type = i;
                            least = distance;
                        }
                    }
                    assignment[index] = type;
                    SUMdistancex[threadnum][type] += m_points[index].x;
                    SUMdistancey[threadnum][type] += m_points[index].y;
                    numPointsType[threadnum][type]++;
                    // mymutex.unlock();
                }
                }));
        }
        for (auto t : threads) {
            t->join();
        }

        bool haschanged = false;
        // rearrangeCpoint
        for (int i = 0; i < m_numCenters; i++) {
            int numPoints = 0;
            double newcx=0, newcy=0;
            for (size_t threadid = 0; threadid < 4; threadid++)
            {
                numPoints += numPointsType[threadid][i];
                newcx += SUMdistancex[threadid][i];
                newcy += SUMdistancey[threadid][i];
            }
            newcx /= numPoints, newcy /= numPoints;
            if (numPoints == 0)continue;
            if (!(abs(m_centers[i].x - newcx) < 1e-3 &&
                abs(m_centers[i].y - newcy) < 1e-3))
                haschanged = true;
            // if (!(abs(m_centers[i].x == r1 / corxs[i].size())&& abs(m_centers[i].y
            // == r2 / corys[i].size())))haschanged = true;
            m_centers[i].x = newcx;
            m_centers[i].y = newcy;
        }

        if (!haschanged)
            break;
    }
    // YOUR CODE ENDS HERE
    std::cout << "Finished in " << currIteration << " iterations." << std::endl;
    return assignment;
}