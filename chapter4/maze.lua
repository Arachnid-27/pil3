--[ exercise 4.4 ]--

function room1 ()
    repeat
        local move = io.read()
        if move == 'south' then
            return room3()
        elseif move == 'east' then
            return room2()
        else
            print('invalid room')
        end
    until false
end

function room2 ()
    repeat
        local move = io.read()
        if move == 'south' then
            return room4()
        elseif move == 'west' then
            return room1()
        else
            print('invalid room')
        end
    until false
end

function room3 ()
    repeat
        local move = io.read()
        if move == 'north' then
            return room1()
        elseif move == 'east' then
            return room4()
        else
            print('invalid room')
        end
    until false
end

function room4 ()
    print('you won!')
end

room1()
