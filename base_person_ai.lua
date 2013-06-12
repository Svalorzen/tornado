
function base_person_ai()
    result = {}
    -- entityHub
    
    --if mapHub:isThereFood() then
    --    result["type"] = "pick_up"
    --    result["target"] = "food"
    --    actionHub:setAction(result); 
    --
    --elseif mapHub:isThereWood() then
    --    result["type"] = "pick_up"
    --    result["target"] = "wood"
    --    actionHub:setAction(result); 
    --end
    
    -- print(entityHub:getId())

    first = true;
    if first then
        result["type"] = "build"
        actionHub:setAction(result);
        first = false
    end

    result["type"] = "none"
    actionHub:setAction(result);
end
