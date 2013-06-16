
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
        end
        myMem["action"] = {} 
    end

    -- base action
    local action = {}
    action["type"] = "none"

    if myMem["globals"]["woodCounter"] == 5 then
        if myMem["globals"]["building"] == true then
            print "LUA: Validating"
            action["type"] = "validate"
        else
            print "LUA: Building"
            action["type"] = "build"
        end

    -- try to eat food
    elseif mapHub:isThereFood() then
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
    elseif mapHub:isThereWood() then
        action["type"] = "pick_up"
        action["target"] = "wood"
        if myMem["action"]["target"] ~= "wood" then
            action["targetId"] = mapHub:getNearestWood(myId);
        else
            action["targetId"] = mapHub:getNearestWood(myId, myMem["action"]["targetId"]); 
        end
    else
        if myMem["action"]["target"] == "wood" then
            action["type"] = "pick_up"
            action["target"] = "wood"
            action["targetId"] = myMem["action"]["targetId"];
        end
    end

    myMem["action"] = action;

    memory[entityHub:getId()] = myMem;

    actionHub:setAction(action);
end
