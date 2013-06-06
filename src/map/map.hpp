#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>
#include <random>

#include <map/utils/tile.hpp>

#include <entities/entity.hpp>
#include <entities/item.hpp>
#include <entities/building.hpp>
#include <entities/person.hpp>

namespace sf { class Texture; class RenderWindow; }
class EntityBox;
class Position;

class Map {
    public:
        Map(int,int);
        
        void displayMap(sf::RenderWindow &, unsigned);

        std::vector<Person> & getPeople();

        void addItem(Position);
        void addPerson(Position);

        void removeItem(EntityBox);
        void removePerson(EntityBox);

        // This function sets an entity on the map and updates eventual grid properties
        void setEntityPosition(Entity &, Position);

        bool isThereFood() const;
        // Can return nullptr if there's no food!
        EntityBox getNearestFood(Position) const;

    private:
        // Randoms for this map
        std::default_random_engine generator_;

        // The map grid. Contains walkable properties and other ones.
        std::vector<std::vector<Tile>> grid_;

        void applyEntityToGrid(const Entity &);
        void unapplyEntityFromGrid(const Entity &);

        // People
        std::vector<Person> people_;
        // Buildings
        std::vector<Building> buildings_;
        // Items
        std::vector<Item> items_;
};

#endif
