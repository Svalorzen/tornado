
function base_person_ai()
    result = {}
    -- base action
    result["type"] = "none"
    
    -- try to eat food
    if mapHub:isThereFood() then
        result["type"] = "pick_up"
        result["target"] = "food"
    end

    --//
    -- if mapHub:isThereFood() && distance(
    ---

    -- print(entityHub:getId())

    actionHub:setAction(result);
end
