#include "map.hpp"

#include <iostream>
#include <algorithm>

#include <SFML/Graphics.hpp>

#include <graphics/globals.hpp>
#include <graphics/textures.hpp>

#include <map/utils/position.hpp>

#include <entities/utils/entity_box.hpp>

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
}

void Map::removePerson(EntityBox b) {
    size_t i = b.getEntityIndex();
    unapplyEntityFromGrid(people_[i]);
    people_.erase(begin(people_)+i);
}

void Map::addItem(Position pos) {
    items_.emplace_back(ItemType::FOOD);
    Item & i = items_.back();

    setEntityPosition(i, pos);
    i.refresh();
}

void Map::removeItem(EntityBox b) {
    size_t i = b.getEntityIndex();
    unapplyEntityFromGrid(items_[i]);
    items_.erase(begin(items_)+i);
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

EntityBox Map::getNearestFood(Position p) const {
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

    return EntityBox(items_[it], static_cast<size_t>(it));
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
