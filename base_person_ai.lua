
function base_person_ai()
    result = {}
    -- entityHub
    if mapHub:isThereFood() then
        result["type"] = "pick_up"
        result["target"] = "food"
        actionHub:setAction(result); 
    end

    result["type"] = "none"
    actionHub:setAction(result);
end
