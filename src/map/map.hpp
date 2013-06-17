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
#include <entities/aoe.hpp>

namespace sf { class Texture; class RenderWindow; }
class EntityBox;
template <typename T> class Position;
class Area;

class Map {
    public:
        Map(int,int);
        
        void displayMap(sf::RenderWindow &, unsigned);

        std::vector<Person> & getPeople();
        std::vector<std::vector<Tile>> & getGrid();
        
        Person & getPerson(ID_t);
        const Person & getPerson(ID_t) const;

        Item & getItem(ID_t);
        const Item & getItem(ID_t) const;

        Building & getBuilding(ID_t);
        const Building & getBuilding(ID_t) const;

        AoE & getAoE(ID_t);
        const AoE & getAoE(ID_t) const;
        
        Item & addItem(Position<int>, ItemType);
        Person & addPerson(Position<int>);
        Building & addBuilding(Position<int>, Area, BuildingType);
        AoE & addAoE(Position<int>, Area);

        void validateBuilding(ID_t);

        void removeItem(ID_t);
        void removePerson(ID_t);
        void removeBuilding(ID_t);
        void removeAoE(ID_t);

        void stashItem(ID_t);

        // This function sets an entity on the map and updates eventual grid properties
        void setEntityPosition(Entity &, Position<int>);
        void setAoEPosition(AoE &, Position<int>);

        // ################ AI FUNCTIONS #########################

        bool isThereFood() const;
        bool isThereWood() const;
        // Can return nullptr if there's no food!
        const Item & getNearestFood(Position<int>) const;
        const Item & getNearestFood(Position<int>, ID_t) const;
        const Item & getNearestWood(Position<int>) const;
        const Item & getNearestWood(Position<int>, ID_t) const;

        bool isThereItem(ItemType) const;
        const Item & getNearestItem(ItemType, Position<int>) const;
        const Item & getNearestItem(ItemType, Position<int>, ID_t) const;

        Position<int> findBuildSpot(const Position<int>&, const Area &) const;
        bool canBuild(const Position<int>&, const Area&) const;

    private:
        // Randoms for this map
        mutable std::default_random_engine generator_;

        // The map grid. Contains walkable properties and other ones.
        std::vector<std::vector<Tile>> grid_;

        void applyEntityToGrid(const Entity &);
        void unapplyEntityFromGrid(const Entity &);

        void applyAoEToGrid(const AoE &);
        void unapplyAoEFromGrid(const AoE &);

        // People
        std::vector<Person> people_;
        std::unordered_map<ID_t, size_t> peopleIndex_;
        // Buildings
        std::vector<Building> buildings_;
        std::unordered_map<ID_t, size_t> buildingsIndex_;
        Position<float> buildingCentroid_;
        // Items
        std::vector<Item> items_;
        std::unordered_map<ID_t, size_t> itemsIndex_;
        // AoE
        std::vector<AoE> aoes_;
        std::unordered_map<ID_t, size_t> aoesIndex_;

        sf::Sprite lifeBar_;
        sf::Sprite lifeBarOutline_;
};

#endif
