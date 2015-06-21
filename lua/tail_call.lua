--
-- tail call elimination 
--     implement goto
--     implement state machine
--     do not cause stack overflow
function foo(n)
    if n> 0 then 
        print(n)
        return foo(n-1) 
    end
end

foo(1000)