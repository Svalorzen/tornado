
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

    -- base action
    print ( "Setting base action" );
    local result = {}
    result["type"] = "none"
    
    -- try to eat food
    if mapHub:isThereFood() then
        print( "There is food" );
        result["type"] = "pick_up"
        result["target"] = "food"
        if myMem["target"] ~= "food" then
            print( "No old target, try get food");
            result["targetId"] = mapHub:getNearestFood(myId);
            if result["targetId"] == nil then
                print "WTF NO ID";
            else
                print ("FOOD ID IS "..result["targetId"]);
            end
        else
            print( "We have old target, try get food");
            result["targetId"] = mapHub:getNearestFood(myId, myMem["targetId"]); 
        end
        print ( "Saving food result" );
        myMem["target"] = "food";
        myMem["targetId"] = result["targetId"];
    else
        if myMem["target"] == "food" then
            print ("We have old results");
            result["type"] = "pick_up"
            result["target"] = "food"
            result["targetId"] = myMem["targetId"];
            if result["targetId"] == nil then
                print "WTF NO ID";
            else
                print ("FOOD ID IS "..result["targetId"]);
            end
        end
    end

    -- if mapHub:isThereFood() && mapHub:getNearestFood(myOldFood);
    ---

    if result["target"] == "food" then
        if result["targetId"] == nil then
            print "WTF NO ID";
        else
            print ("FOOD ID IS "..result["targetId"]);
        end
    end
    -- print(entityHub:getId())

    memory[entityHub:getId()] = myMem;

    actionHub:setAction(result);
end
