#include "game_engine.hpp"

//#include <boost/heap/d_ary_heap.hpp>
#include <boost/heap/fibonacci_heap.hpp>

#include <map/map.hpp>
#include <iostream>

std::vector<Position<int>> GameEngine::Astar(const Position<int> & from, const Position<int> & to ) {
    std::vector<Position<int>> path;
    auto grid = ownMap_.getGrid();

    //                        F score, G score, Pos,           Parent
    using node_t = std::tuple<int,     int,     Position<int>, Position<int>>;
    enum node_t_fields {
        F_SCORE = 0,
        G_SCORE = 1,
        POSITION = 2,
        PARENT = 3
    };
    // Comparation is only needed based on F score
    struct node_t_comparator {
        bool operator() (const node_t & lhs, const node_t & rhs) const { return std::get<F_SCORE>(lhs) > std::get<F_SCORE>(rhs); }
    };

    // Heap structure to keep nodes we have to examine in order of F score
    // This is for binary heaps
 //   using openSet_t = boost::heap::d_ary_heap<
 //       node_t,
 //       boost::heap::arity<2>,
 //       boost::heap::compare<node_t_comparator>,
 //       boost::heap::mutable_<true>>;

    // This is apparently like 5x faster on long paths
    using openSet_t = boost::heap::fibonacci_heap<
            node_t,
            boost::heap::compare<node_t_comparator>>;

    openSet_t openSet;

    std::unordered_map<Position<int>, node_t> closedSet;
    std::unordered_map<Position<int>, openSet_t::handle_type> openSetHandles;

    openSetHandles[from] = openSet.push(std::make_tuple((to-from).getDistance(), 0, from, Position<int>(-1, -1)));

//    int maxLoop = 20;

    while ( openSet.size() > 0 ) { // && maxLoop ) {
//        maxLoop--;

        Position<int> current, parent;
        int fScore, gScore;

        auto top = openSet.top(); 
        std::tie(fScore, gScore, current, parent) = top;

        openSet.pop();
        openSetHandles.erase(current);

        closedSet[current] = top;

        //std::cout << "ASTAR: Now considering: "; current.print(); std::cout << "\n";

        // Success
        if ( to == current ) {
            while ( current != from ) {
          //      std::cout << "ASTAR: Success -- Adding: "; current.print(); std::cout << "\n"; 
                path.push_back(current);
                current = std::get<PARENT>(closedSet.find(current)->second);
            }
            return path;
        }

        const std::array<Distance<int>, 4> neighbours {{ {0,1}, {0,-1}, {1, 0}, {-1, 0} }};
        int costFromCurrent = gScore + 1;

        for ( auto & n : neighbours ) {
            Position<int> neighbour = current + n;
            // Check walkability/validity of the position
           // std::cout << "ASTAR:     Neighbour: "; neighbour.print(); std::cout << "\n";
           if ( neighbour.getX() < 0 || static_cast<unsigned>(neighbour.getX()) >= grid[0].size() ||
                neighbour.getY() < 0 || static_cast<unsigned>(neighbour.getY()) >= grid.size() ) continue;
           if ( !grid[neighbour.getY()][neighbour.getX()].isWalkable() ) continue;
           // std::cout << "ASTAR:         Neighbour valid.\n";
            {
                auto it = closedSet.find(neighbour);
                // If we processed it already
                if ( it != end(closedSet) ) {
             //       std::cout << "ASTAR:         Neighbour in closedSet.\n";
                    // And this path to it is no good, avoid it
                    if ( costFromCurrent >= std::get<G_SCORE>(it->second) ) continue;
                }
            }
            {
                auto it = openSetHandles.find(neighbour);
                auto tuple = std::make_tuple(costFromCurrent + (to - neighbour).getDistance(), costFromCurrent, neighbour, current);
              //  std::cout << "ASTAR:        Neighbour stats: " << std::get<0>(tuple) << ", " << std::get<1>(tuple) << "\n";
                // Either we make it better, or we create it again
                if ( it != end(openSetHandles) ) {
               //     std::cout << "ASTAR:         Neighbour in openSet.\n";
                    if ( node_t_comparator()(*(it->second), tuple)) {
                //        std::cout << "ASTAR:         Neighbour updated.\n";
                        //openSet.increase(it->second, tuple);
                        //openSet.decrease(it->second, tuple);
                        openSet.increase(it->second, tuple);
                    }
                }
                else
                    openSetHandles[neighbour] = openSet.push(tuple);
            }
        }
    }
    std::cout << "ASTAR: Failed to find path.\n";
    // Failure
    return path;
}
