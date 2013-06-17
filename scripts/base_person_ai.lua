function getFood(myMem, myId) 
    local action = {}
    local result = true

    if mapHub:isThereFood() then
        action["type"] = "pick_up"
        action["target"] = "food"
        if myMem["action"]["target"] ~= "food" then
            action["targetId"] = mapHub:getNearestFood(myId);
        else
            action["targetId"] = mapHub:getNearestFood(myId, myMem["action"]["targetId"]); 
        end
    elseif myMem["action"]["target"] == "food" then
        action["type"] = "pick_up"
        action["target"] = "food"
        action["targetId"] = myMem["action"]["targetId"];
    else
        result = false
    end

    return result, action
end

function getWood(myMem, myId)
    local action = {}
    local result = true

    if mapHub:isThereWood() then
        action["type"] = "pick_up"
        action["target"] = "wood"
        if myMem["action"]["target"] ~= "wood" then
            action["targetId"] = mapHub:getNearestWood(myId);
        else
            action["targetId"] = mapHub:getNearestWood(myId, myMem["action"]["targetId"]); 
        end
    elseif myMem["action"]["target"] == "wood" then
        action["type"] = "pick_up"
        action["target"] = "wood"
        action["targetId"] = myMem["action"]["targetId"];
    else
        result = false
    end

    return result, action
end

function base_person_ai()
    -- load id
    local myId = entityHub:getId();
    -- load memory
    local myMem = memory[myId];
    if ( myMem == nil ) then
        myMem = {}
        myMem["action"] = {}
        myMem["globals"] = {}
        myMem["globals"]["foodCounter"] = 0;
        myMem["globals"]["woodCounter"] = 0;
        myMem["globals"]["building"] = false;
        myMem["globals"]["owner"] = false;
    end

    -- checking old action with result
    local result = entityHub:getResult();
    if result["type"] == myMem["action"]["type"] then
        if result["type"] == "pick_up" then
            if myMem["action"]["target"] == "food" then
                myMem["globals"]["foodCounter"] = myMem["globals"]["foodCounter"] + 1
            elseif myMem["action"]["target"] == "wood" then
                myMem["globals"]["woodCounter"] = myMem["globals"]["woodCounter"] + 1
            end
        elseif result["type"] == "build" then
            myMem["globals"]["building"] = true
        elseif result["type"] == "validate" then
            myMem["globals"]["woodCounter"] = myMem["globals"]["woodCounter"] - 5;
            myMem["globals"]["building"] = false
            myMem["globals"]["owner"] = true
        elseif result["type"] == "reproduce" then
            myMem["globals"]["foodCounter"] = myMem["globals"]["foodCounter"] - 5;
        end
        myMem["action"] = {} 
    -- FAILURES CHECK
    elseif result["type"] == "failure" then
    
    end

    -- base action
    local action = {}
    action["type"] = "none"

    if myMem["globals"]["woodCounter"] >= 5 and not myMem["globals"]["owner"] then
        if myMem["globals"]["building"] == true then
            action["type"] = "validate"
        else
            action["type"] = "build"
        end
    elseif myMem["globals"]["foodCounter"] >= 5 and myMem["globals"]["owner"] then
        action["type"] = "reproduce"
    -- try to eat food
    elseif myMem["globals"]["owner"] then
        result, action = getFood(myMem, myId)
    else
        result, action = getWood(myMem, myId)
        if not result then
            result, action = getFood(myMem, myId)
        end
    end

    if next(action) == nil then
        action["type"] = "none"
    end
    myMem["action"] = action;

    memory[entityHub:getId()] = myMem;

    actionHub:setAction(action);
end
