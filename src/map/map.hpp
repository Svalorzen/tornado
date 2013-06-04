#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>
#include <memory>
#include <unordered_map>
#include <utility>
#include <list>
#include <random>

#include <map/utils/tile.hpp>
#include <map/utils/position.hpp>

class Entity;
class Item;
class Building;
class Person;

namespace sf { class Texture; class RenderWindow; }

class Map {
    public:
        Map(int,int);
        
        void runStep();
        void displayMap(sf::RenderWindow &, unsigned);

        void addItem(Position);
        void addPerson(Position);

        bool isThereFood() const;
        // Can return nullptr if there's no food!
        const Item * getNearestFood(Position) const;

    private:
        void removeItem(const Item *);
        void removePerson(const Person *);

        // Randoms for this map
        std::default_random_engine generator_;

        // The map grid. Contains walkable properties and other ones.
        std::vector<std::vector<Tile>> grid_;

        // All the objects in the map
        std::vector<std::shared_ptr<Entity>> entities_;

        // This function sets an entity on the map and updates eventual grid properties
        void setEntityPosition(Entity *, Position);
        void applyEntityToGrid(const Entity*);
        void unapplyEntityFromGrid(const Entity*);

        // People
        std::vector<std::shared_ptr<Person>> people_;
        // Buildings
        std::vector<std::shared_ptr<Building>> buildings_;
        // Items
        std::vector<std::shared_ptr<Item>> items_;

        // Pathing (A*...)
        Position computeSingleMove(const Entity &, Position); 

        // PATHING CACHE
        static constexpr unsigned MAX_PATH_CACHE = 1000;
        // This map links a pair <Entity*,Position> with our last known pathfinding for it.
        // In addition, there is an iterator to the list containing the history, so that if
        // the cache is full we can remove the most old entries.
        std::unordered_map<std::pair<const Entity*, Position>,
                           std::pair<std::vector<Position>,
                                     std::list<std::pair<const Entity*,Position>>::iterator>> cachedPaths_;
        std::list<std::pair<const Entity*,Position>> cachedPathsHistory_;
};

#endif
