#include "map.hpp"

#include <iostream>
#include <algorithm>
#include <chrono>

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
            dummy.back().getOwnSprite().setColor(sf::Color(255, 255, 255, 200));
        }
        grid_.push_back(dummy);
        dummy.clear();
    }

    people_.reserve(1000);
    items_.reserve(1000);
    buildings_.reserve(1000);

    addPerson({1,1});

    buildingCentroid_ = {-1, -1};

    // Life bar for everybody
    lifeBar_ = sf::Sprite(Graphics::getTexture("src/resources/lifebar.png", false));
    lifeBarOutline_ = sf::Sprite(Graphics::getTexture("src/resources/lifebar_outline.png", false));
}

std::vector<Person> & Map::getPeople() {
    return people_;
}

std::vector<std::vector<Tile>> & Map::getGrid() {
    return grid_;
}

void Map::displayMap(sf::RenderWindow &window, unsigned elapsedMs) {
    for ( auto & row : grid_ )
        for (auto & cell : row ) 
            window.draw(cell.getOwnSprite());
    
    for ( auto & b : buildings_ ) {
        if ( b.getOwnSprite().getToRender() ) {
            window.draw(b.getOwnSprite());
            b.graphicalUpdate(elapsedMs);
        }
    }
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
    // Render lifebars
    for ( auto & p : people_ ) {
        lifeBar_.setTextureRect(sf::IntRect(30 - 30*(static_cast<float>(p.getNeeds()[value("hunger", Person::NEEDS)])/
                                                     static_cast<float>(Person::NEED_PRIORITIES[2])),0,30,3));
        lifeBar_.setPosition(p.getOwnSprite().getPosition() + sf::Vector2f(1.0f, -10.0f) );
        lifeBarOutline_.setPosition(lifeBar_.getPosition() + sf::Vector2f(-1.0f,-1.0f) );

        window.draw(lifeBarOutline_);
        window.draw(lifeBar_);
    }
}

Person & Map::addPerson(Position<int> pos) {
    std::uniform_int_distribution<int> distribution(0,1);
    // Randomizes man females
    people_.emplace_back(static_cast<bool>(distribution(generator_)));
    Person & p = people_.back();

    setEntityPosition(p, pos);
    p.refresh();

    // Save in index
    peopleIndex_[p.getId()] = people_.size() - 1;
    return p;
}

Item & Map::addItem(Position<int> pos, ItemType type) {
    items_.emplace_back(type);
    Item & i = items_.back();

    setEntityPosition(i, pos);
    i.refresh();

    // Save in index
    itemsIndex_[i.getId()] = items_.size() - 1;
    return i;
}

Building & Map::addBuilding(Position<int> pos, Area a, BuildingType type) {
    if ( ! canBuild(pos, a) )
        throw std::invalid_argument("We can't build there!\n");

    buildings_.emplace_back(a,type);
    Building & b = buildings_.back();

    setEntityPosition(b, pos);
    b.refresh();

    // FIXME: The area should be computed from the original building area, of course
    // Set that nobody can build near this, even if it is unvalidated
    auto aoepos = pos + Distance<int>(-1, 1);
    auto & aoe = addAoE(aoepos, {"1111", "1111", "1111", "1111"});
    aoe.setBuildable(false);
    // Refresh on the grid the property change
    setAoEPosition(aoe, aoepos);
    b.setUnbuildableArea(aoe.getId());

    // Save in index
    buildingsIndex_[b.getId()] = buildings_.size() - 1;
    return b;
}

AoE & Map::addAoE(Position<int> p, Area a) {
    aoes_.emplace_back(a);
    AoE & aoe = aoes_.back();

    setAoEPosition(aoe, p);
    aoe.refresh();

    // Save in index
    aoesIndex_[aoe.getId()] = aoes_.size() - 1;
    return aoe;
}

void Map::validateBuilding(ID_t id) {
    Building & b = getBuilding(id);

    b.validate();
    setEntityPosition(b, b.getPosition());
    b.refresh();

    // Move the village centroid
    {
        Position<float> newBuildingCentroid = static_cast<Position<float>>(b.getPosition()) + b.getArea().getCentroid();
        if ( buildingCentroid_ == Position<float>(-1,-1) )
            buildingCentroid_ = newBuildingCentroid;
        else
            buildingCentroid_ -= ( buildingCentroid_ - newBuildingCentroid ) / buildings_.size();
    }
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

AoE & Map::getAoE(ID_t id) {
    auto it = aoesIndex_.find(id);
    if ( it != end(aoesIndex_) ) {
        return aoes_[it->second];
    }
    throw std::runtime_error("Building id not valid.\n");
}

const AoE & Map::getAoE(ID_t id) const {
    auto it = aoesIndex_.find(id);
    if ( it != end(aoesIndex_) ) {
        return aoes_[it->second];
    }
    throw std::runtime_error("Building id not valid.\n");
}

void Map::removePerson(ID_t id) {
    auto it = peopleIndex_.find(id);
    if ( it != end(peopleIndex_) ) {
        auto index = it->second;
        unapplyEntityFromGrid(people_[index]);

        // Delete inventory
        auto & inv = people_[index].getInventory();
        for ( auto i : inv )
            removeItem(i);

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

        removeAoE(buildings_[index].getUnbuildableArea());

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

void Map::removeAoE(ID_t id) {
    auto it = aoesIndex_.find(id);
    if ( it != end(aoesIndex_) ) {
        auto index = it->second;
        unapplyAoEFromGrid(aoes_[index]);

        // Efficient removal
        if ( aoes_.size() > 1 )
            std::swap(aoes_[index], aoes_.back());
        aoes_.pop_back();

        // Update other guy index
        aoesIndex_[aoes_[index].getId()] = index;
        // Remove old guy index
        aoesIndex_.erase(it);
    }
    else
        throw std::runtime_error("AoE id not valid.\n");
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
void Map::setEntityPosition(Entity & e, Position<int> p) {
    unapplyEntityFromGrid(e);
    e.setPosition(p);
    applyEntityToGrid(e);
}

void Map::setAoEPosition(AoE & e, Position<int> p) {
    unapplyAoEFromGrid(e);
    e.setPosition(p);
    applyAoEToGrid(e);
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

const Item & Map::getNearestFood(Position<int> p) const {
    return getNearestItem(ItemType::FOOD, p);
}

const Item & Map::getNearestWood(Position<int> p) const {
    return getNearestItem(ItemType::WOOD, p);
}

const Item & Map::getNearestItem(ItemType type, Position<int> p) const {
    int it = -1;
    Distance<int> distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == type && ! item.isLocked() ) {
            Distance<int> distanceDiff = p - item.getPosition();

            if ( it == -1 || distance > distanceDiff ) {
                it = i;
                distance = distanceDiff;
            }
        }
    }

    return items_[it];
}

const Item & Map::getNearestFood(Position<int> p, ID_t id) const {
    return getNearestItem(ItemType::FOOD, p, id);
}

const Item & Map::getNearestWood(Position<int> p, ID_t id) const {
    return getNearestItem(ItemType::WOOD, p, id);
}

const Item & Map::getNearestItem(ItemType type, Position<int> p, ID_t id) const {
    int it = -1;
    Distance<int> distance;

    for ( size_t i = 0; i < items_.size(); i++ ) {
        const Item & item = items_[i];

        if ( item.getType() == type && ( ! item.isLocked() || item.getId() == id ) ) {
            Distance<int> distanceDiff = p - item.getPosition();

            if ( it == -1 || distance > distanceDiff ) {
                it = i;
                distance = distanceDiff;
            }
        }
    }

    return items_[it];
}

void Map::unapplyEntityFromGrid(const Entity& e) {
    std::vector<Position<int>> initialTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : initialTiles ) {
        // This is because applying an area could go outside the map ( maybe hotness of fire )
        // and in general I guess we want to go on. We should check beforehand if this is important
        // ( e.g. when building houses )
        try {
            grid_.at(p.getY()).at(p.getX()).rmEntity(e); 
        } catch(const std::out_of_range &){}
    }
}

void Map::applyEntityToGrid(const Entity& e) {
    std::vector<Position<int>> finalTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : finalTiles ) {
        try {
            grid_.at(p.getY()).at(p.getX()).addEntity(e); 
        } catch(const std::out_of_range &){}
    }
}

Position<int> Map::findBuildSpot(const Position<int> & pos, const Area& area) const {
    unsigned loops = grid_.size() * grid_[0].size();

    std::uniform_int_distribution<int> distribution(0,1);

    /* BASE HORIZONTAL SEARCH:      BASE VERTICAL SEARCH:
           
           7890                           567
           612                            418
           543                            329  
                                            0
    */
    bool horiz = static_cast<bool>(distribution(generator_));

    // 1 = Yes, -1 = No
    int mirrorX = ( distribution(generator_) * 2 ) - 1;
    int mirrorY = ( distribution(generator_) * 2 ) - 1;

    // 1 = Yes, -1 = No
    int clockwise = static_cast<int>( mirrorX == mirrorY ) * 2 - 1;

    // This sets the starting direction
    Distance<int> dir( (1-horiz) * -mirrorX, horiz * mirrorY );

    // Either we search from the unit position, or from the village centroid
    std::cout << "Centroid is at: "; buildingCentroid_.print();
    Position<int> p = buildingCentroid_ == Position<float>(-1.0f, -1.0f) ?
                        pos : Position<int>(std::round(buildingCentroid_.getX()), std::round(buildingCentroid_.getY()));
    std::cout << "\nStarting position is at: "; p.print(); std::cout << std::endl;
    // This tracks where we are in the spiral
    Distance<int> offset(0,0);
    int offsetXCheck = 0;
    int offsetYCheck = 0;

    // DEBUG
    //int countt = 0;
    //for ( auto & i : grid_ )
    //    for ( auto & j : i )
    //        j.getOwnSprite().setColor(sf::Color(255, 255, 255, 200));

    while ( loops ) {
     //   countt++;
        // Only if it's inside the map
        if ( p.getX() >= 0 && p.getY() >= ( static_cast<int>(area.getMaxH()) - 1 ) && canBuild(p, area) ) 
            return p;
        p.print(); std::cout << "\n";
        // DEBUG
    //    grid_[p.getY()][p.getX()].getOwnSprite().setColor(sf::Color(255 - countt*30, 100, 100));

        offsetXCheck = -mirrorX * offset.getDiffXi();
        offsetYCheck = -mirrorY * offset.getDiffYi();

        if ( !horiz ) {
            int temp = offsetXCheck;
            offsetXCheck = offsetYCheck;
            offsetYCheck = -temp;
        }

        if ( offsetXCheck == offsetYCheck ||
            ((offsetXCheck < 0) && (offsetXCheck == - offsetYCheck)) ||
            ((offsetXCheck > 0) && (offsetXCheck == 1-offsetYCheck)) ) {

            dir = { -clockwise * dir.getDiffYi(), clockwise * dir.getDiffXi()};
        }

        // DEBUG
        // dir.print(); std::cout << "    at    "; offset.print(); std::cout << "\n";
        // try {
        // test.at(offset.getDiffYi()+4)[offset.getDiffXi()+4] = true;
        // } catch(...) {}

        p += dir;
        offset += dir;

        loops--;
    }

    // No space in the whole map
    return Position<int>(-1, -1);
}

bool Map::canBuild(const Position<int> & p, const Area & a) const {
    std::vector<Position<int>> finalTiles = a.applyArea(p);

    for ( auto & p : finalTiles ) {
        try {
            if ( !grid_.at(p.getY()).at(p.getX()).isBuildable() ) return false; 
        } catch(const std::out_of_range &){return false;}
    }
    
    return true;
}

void Map::unapplyAoEFromGrid(const AoE& e) {
    std::vector<Position<int>> initialTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : initialTiles ) {
        // This is because applying an area could go outside the map ( maybe hotness of fire )
        // and in general I guess we want to go on. We should check beforehand if this is important
        // ( e.g. when building houses )
        try {
            grid_.at(p.getY()).at(p.getX()).rmAoE(e); 
        } catch(const std::out_of_range &){}
    }
}

void Map::applyAoEToGrid(const AoE& e) {
    std::vector<Position<int>> finalTiles = e.getArea().applyArea(e.getPosition());
    
    for ( auto & p : finalTiles ) {
        try {
            grid_.at(p.getY()).at(p.getX()).addAoE(e); 
        } catch(const std::out_of_range &){}
    }
}
