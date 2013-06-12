#include "map.hpp"

#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <map/utils/position.hpp>

Map::Map(int x, int y) {
    // getTexture MAY THROW! 
    const sf::Texture & texture = Graphics::getTexture("src/resources/green.png", false);

    std::vector<Tile> dummy;
    // Reserve space in advance
    dummy.reserve(x);
    grid_.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(AnimatedSprite(texture));
            dummy.back().getOwnSprite().setPosition(j*Graphics::TILE_EDGE_SIZE, i*Graphics::TILE_EDGE_SIZE);
        }
        grid_.push_back(dummy);
        dummy.clear();
    }

    people_.reserve(1000);
    items_.reserve(1000);
    buildings_.reserve(1000);

    addPerson({1,1});
    addPerson({10,10});
}

std::vector<Person> & Map::getPeople() {
    return people_;
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell.getOwnSprite());
    
    for ( auto & i : items_ ) {
        if ( i.getOwnSprite().getToRender() ) {
            window.draw(i.getOwnSprite());
            i.graphicalUpdate(elapsedMs);
        }
    }
    for ( auto & p : people_ ) {
        if ( p.getOwnSprite().getToRender() ) {
            window.draw(p.getOwnSprite());
            p.graphicalUpdate(elapsedMs);
        }
    }
    for ( auto & b : buildings_ ) {
        if ( b.getOwnSprite().getToRender() ) {
            window.draw(b.getOwnSprite());
            b.graphicalUpdate(elapsedMs);
        }
    }

}

void Map::addPerson(Position pos) {
    std::uniform_int_distribution<int> distribution(0,1);
    // Randomizes man females
    people_.emplace_back(distribution(generator_));
    Person & p = people_.back();

    setEntityPosition(p, pos);
    p.refresh();

    // Save in index
    peopleIndex_[p.getId()] = people_.size() - 1;
}

void Map::addItem(Position pos, ItemType type) {
    items_.emplace_back(type);
    Item & i = items_.back();

    setEntityPosition(i, pos);
    i.refresh();

    // Save in index
    itemsIndex_[i.getId()] = items_.size() - 1;
}

void Map::addBuilding(Position pos, Area a, BuildingType type) {
    buildings_.emplace_back(a,type);
    Building & b = buildings_.back();

    setEntityPosition(b, pos);
    b.refresh();

    // Save in index
    buildingsIndex_[b.getId()] = buildings_.size() - 1;
}

Person & Map::getPerson(ID_t id) {
    auto it = peopleIndex_.find(id);
    if ( it != end(peopleIndex_) ) {
        return people_[it->second];
    }
    throw std::runtime_error("Person id not valid.\n");
}

const Person & Map::getPerson(ID_t id) const {
    auto it = peopleIndex_.find(id);
    if ( it != end(peopleIndex_) ) {
        return people_[it->second];
    }
    throw std::runtime_error("Person id not valid.\n");
}

Item & Map::getItem(ID_t id) {
    auto it = itemsIndex_.find(id);
    if ( it != end(itemsIndex_) ) {
        return items_[it->second];
    }
    throw std::runtime_error("Item id not valid.\n");
}

const Item & Map::getItem(ID_t id) const {
    auto it = itemsIndex_.find(id);
    if ( it != end(itemsIndex_) ) {
        return items_[it->second];
    }
    throw std::runtime_error("Item id not valid.\n");
}

Building & Map::getBuilding(ID_t id) {
    auto it = buildingsIndex_.find(id);
    if ( it != end(buildingsIndex_) ) {
        return buildings_[it->second];
    }
    throw std::runtime_error("Building id not valid.\n");
}

const Building & Map::getBuilding(ID_t id) const {
    auto it = buildingsIndex_.find(id);
    if ( it != end(buildingsIndex_) ) {
        return buildings_[it->second];
    }
    throw std::runtime_error("Building id not valid.\n");
}

void Map::removePerson(ID_t id) {
    auto it = peopleIndex_.find(id);
    if ( it != end(peopleIndex_) ) {
        auto index = it->second;
        unapplyEntityFromGrid(people_[index]);
        // Efficient removal
        if ( people_.size() > 1 )
            std::swap(people_[index], people_.back());
        people_.pop_back();

        // Update other guy index
        peopleIndex_[people_[index].getId()] = index;
        // Remove old guy index
        peopleIndex_.erase(it);
    }
    else
        throw std::runtime_error("Person id not valid.\n");
}

void Map::removeItem(ID_t id) {
    auto it = itemsIndex_.find(id);
    if ( it != end(itemsIndex_) ) {
        auto index = it->second;
        unapplyEntityFromGrid(items_[index]);
        // Efficient removal
        if ( items_.size() > 1 )
            std::swap(items_[index], items_.back());
        items_.pop_back();

        // Update other guy index
        itemsIndex_[items_[index].getId()] = index;
        // Remove old guy index
        itemsIndex_.erase(it);
    }
    else
        throw std::runtime_error("Item id not valid.\n");
}

void Map::removeBuilding(ID_t id) {
    auto it = buildingsIndex_.find(id);
    if ( it != end(buildingsIndex_) ) {
        auto index = it->second;
        unapplyEntityFromGrid(buildings_[index]);
        // Efficient removal
        if ( buildings_.size() > 1 )
            std::swap(buildings_[index], buildings_.back());
        buildings_.pop_back();

        // Update other guy index
        buildingsIndex_[buildings_[index].getId()] = index;
        // Remove old guy index
        buildingsIndex_.erase(it);
    }
    else
        throw std::runtime_error("Building id not valid.\n");
}

void Map::stashItem(ID_t id) {
    auto it = itemsIndex_.find(id);
    if ( it != end(itemsIndex_) ) {
        auto index = it->second;
        unapplyEntityFromGrid(items_[index]);
        items_[index].getOwnSprite().setToRender(false);
    }
    else
        throw std::runtime_error("Item id not valid.\n");
}

// This function updates tile links, it is called only when we are actually
// sure the guy will move here
void Map::setEntityPosition(Entity & e, Position p) {
    unapplyEntityFromGrid(e);
    e.setPosition(p);
    applyEntityToGrid(e);
}

bool Map::isThereFood() const {
    return isThereItem(ItemType::FOOD);
}

bool Map::isThereWood() const {
    return isThereItem(ItemType::WOOD);
}

bool Map::isThereItem(ItemType type) const {
    for ( auto & i : items_ )
        if ( i.getType() == type && ! i.isLocked() ) 
            return true;

    return false;
}

const Item & Map::getNearestFood(Position p) const {
    return getNearestItem(ItemType::FOOD, p);
}

const Item & Map::getNearestWood(Position p) const {
    return getNearestItem(ItemType::WOOD, p);
}

const Item & Map::getNearestItem(ItemType type, Position p) const {
    int it = -1;
    Distance distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == type && ! item.isLocked() ) {
            Distance distanceDiff = p - item.getPosition();

            if ( it == -1 || distance > distanceDiff ) {
                it = i;
                distance = distanceDiff;
            }
        }
    }

    return items_[it];
}

const Item & Map::getNearestFood(Position p, ID_t id) const {
    return getNearestItem(ItemType::FOOD, p, id);
}

const Item & Map::getNearestWood(Position p, ID_t id) const {
    return getNearestItem(ItemType::WOOD, p, id);
}

const Item & Map::getNearestItem(ItemType type, Position p, ID_t id) const {
    int it = -1;
    Distance distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == type && ( ! item.isLocked() || item.getId() == id ) ) {
            Distance distanceDiff = p - item.getPosition();

            if ( it == -1 || distance > distanceDiff ) {
                it = i;
                distance = distanceDiff;
            }
        }
    }

    return items_[it];
}

void Map::unapplyEntityFromGrid(const Entity& e) {
    std::vector<Position> initialTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : initialTiles ) {
        // This is because applying an area could go outside the map ( maybe hotness of fire )
        // and in general I guess we want to go on. We should check beforehand if this is important
        // ( e.g. when building houses )
        try {
            grid_.at(p.getX()).at(p.getY()).rmEntity(e); 
        } catch(...){}
    }
}

void Map::applyEntityToGrid(const Entity& e) {
    std::vector<Position> finalTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : finalTiles ) {
        try {
            grid_.at(p.getX()).at(p.getY()).addEntity(e); 
        } catch(...) {}
    }
}
