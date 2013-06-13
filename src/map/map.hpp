#ifndef MAP_HEADER_FILE
#define MAP_HEADER_FILE

#include <vector>
#include <unordered_map>
#include <random>

#include <utils/types.hpp>

#include <map/utils/tile.hpp>

#include <entities/entity.hpp>
#include <entities/item.hpp>
#include <entities/building.hpp>
#include <entities/person.hpp>

namespace sf { class Texture; class RenderWindow; }
class EntityBox;
class Position;
class Area;

class Map {
    public:
        Map(int,int);
        
        void displayMap(sf::RenderWindow &, unsigned);

        std::vector<Person> & getPeople();
        
        Person & getPerson(ID_t);
        const Person & getPerson(ID_t) const;

        Item & getItem(ID_t);
        const Item & getItem(ID_t) const;

        Building & getBuilding(ID_t);
        const Building & getBuilding(ID_t) const;
        
        Item & addItem(Position, ItemType);
        Person & addPerson(Position);
        Building & addBuilding(Position, Area, BuildingType);

        void removeItem(ID_t);
        void removePerson(ID_t);
        void removeBuilding(ID_t);

        void stashItem(ID_t);

        // This function sets an entity on the map and updates eventual grid properties
        void setEntityPosition(Entity &, Position);

        // ################ AI FUNCTIONS #########################

        bool isThereFood() const;
        bool isThereWood() const;
        // Can return nullptr if there's no food!
        const Item & getNearestFood(Position) const;
        const Item & getNearestFood(Position, ID_t) const;
        const Item & getNearestWood(Position) const;
        const Item & getNearestWood(Position, ID_t) const;

        bool isThereItem(ItemType) const;
        const Item & getNearestItem(ItemType, Position) const;
        const Item & getNearestItem(ItemType, Position, ID_t) const;

    private:
        // Randoms for this map
        std::default_random_engine generator_;

        // The map grid. Contains walkable properties and other ones.
        std::vector<std::vector<Tile>> grid_;

        void applyEntityToGrid(const Entity &);
        void unapplyEntityFromGrid(const Entity &);

        // People
        std::vector<Person> people_;
        std::unordered_map<ID_t, size_t> peopleIndex_;
        // Buildings
        std::vector<Building> buildings_;
        std::unordered_map<ID_t, size_t> buildingsIndex_;
        // Items
        std::vector<Item> items_;
        std::unordered_map<ID_t, size_t> itemsIndex_;

};

#endif
