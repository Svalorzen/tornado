#include "map.hpp"

#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <map/utils/position.hpp>

Map::Map(int x, int y) {
    // getTexture MAY THROW! 
    const sf::Texture & texture = Graphics::getTexture("src/resources/green.png");

    std::vector<Tile> dummy;
    // Reserve space in advance
    dummy.reserve(x);
    grid_.reserve(y);

    for ( int i = 0; i < y; i++ ) {
        for ( int j = 0; j < x; j++) {
            dummy.emplace_back(texture);
            dummy.back().setPosition(j*Graphics::TILE_EDGE_SIZE, i*Graphics::TILE_EDGE_SIZE);
        }
        grid_.push_back(dummy);
        dummy.clear();
    }

    people_.reserve(1000);
    items_.reserve(1000);

    addPerson({1,1});
    addPerson({10,10});
}

std::vector<Person> & Map::getPeople() {
    return people_;
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell);
    
    for ( auto & i : items_ ) {
        window.draw(i.getOwnSprite());
        i.graphicalUpdate(elapsedMs);
    }
    for ( auto & p : people_ ) {
        window.draw(p.getOwnSprite());
        p.graphicalUpdate(elapsedMs);
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

void Map::addItem(Position pos) {
    items_.emplace_back(ItemType::FOOD);
    Item & i = items_.back();

    setEntityPosition(i, pos);
    i.refresh();

    // Save in index
    itemsIndex_[i.getId()] = items_.size() - 1;
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
        return;
    }
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
        return;
    }
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
    for ( auto & i : items_ )
        if ( i.getType() == ItemType::FOOD && ! i.isLocked() ) 
            return true;

    return false;
}

const Item & Map::getNearestFood(Position p) const {
    int it = -1;
    Distance distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == ItemType::FOOD && ! item.isLocked() ) {
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
        try {
            grid_.at(p.getX()).at(p.getY()).rmEntity(&e); 
        } catch(...){}
    }
}

void Map::applyEntityToGrid(const Entity& e) {
    std::vector<Position> finalTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : finalTiles ) {
        try {
            grid_.at(p.getX()).at(p.getY()).addEntity(&e); 
        } catch(...) {}
    }
}
