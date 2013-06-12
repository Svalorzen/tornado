
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
        end
        myMem["action"] = {} 
    end

    -- base action
    local result = {}
    result["type"] = "none"

    if myMem["globals"]["woodCounter"] == 5 then
        result["type"] = "build"
        myMem["globals"]["woodCounter"] = 0



    -- try to eat food
    elseif mapHub:isThereFood() then
        result["type"] = "pick_up"
        result["target"] = "food"
        if myMem["action"]["target"] ~= "food" then
            result["targetId"] = mapHub:getNearestFood(myId);
        else
            result["targetId"] = mapHub:getNearestFood(myId, myMem["action"]["targetId"]); 
        end
    elseif myMem["action"]["target"] == "food" then
        result["type"] = "pick_up"
        result["target"] = "food"
        result["targetId"] = myMem["action"]["targetId"];
    elseif mapHub:isThereWood() then
        result["type"] = "pick_up"
        result["target"] = "wood"
        if myMem["action"]["target"] ~= "wood" then
            result["targetId"] = mapHub:getNearestWood(myId);
        else
            result["targetId"] = mapHub:getNearestWood(myId, myMem["action"]["targetId"]); 
        end
    else
        if myMem["action"]["target"] == "wood" then
            result["type"] = "pick_up"
            result["target"] = "wood"
            result["targetId"] = myMem["action"]["targetId"];
        end
    end

    myMem["action"] = result;

    memory[entityHub:getId()] = myMem;

    actionHub:setAction(result);
end
