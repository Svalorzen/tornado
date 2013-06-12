
function base_person_ai()
    -- load id
    local myId = entityHub:getId();
    -- load memory
    print ( "loading memory" );
    local myMem = memory[myId];
    if ( myMem == nil ) then
        print ( "No old memory" );
        myMem = {}
    end

    -- checking old action with result
    local result = entityHub:getResult();
    if result["action"] == myMem["type"] then
        myMem = {}
    end

    -- base action
    print ( "Setting base action" );
    local result = {}
    result["type"] = "none"
    
    -- try to eat food
    if mapHub:isThereFood() then
        result["type"] = "pick_up"
        result["target"] = "food"
        if myMem["target"] ~= "food" then
            result["targetId"] = mapHub:getNearestFood(myId);
        else
            result["targetId"] = mapHub:getNearestFood(myId, myMem["targetId"]); 
        end
    else
        if myMem["target"] == "food" then
            result["type"] = "pick_up"
            result["target"] = "food"
            result["targetId"] = myMem["targetId"];
        end
    end

    myMem = result;
    -- if mapHub:isThereFood() && mapHub:getNearestFood(myOldFood);
    ---

    -- print(entityHub:getId())

    memory[entityHub:getId()] = myMem;

    actionHub:setAction(result);
end
