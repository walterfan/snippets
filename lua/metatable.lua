local user = { name='tom'}
function user:getName() return 'user_'..self.name end  
guest = {name='jerry'}
setmetatable(guest, {__index=user})
print(guest.getName(user) .. ", " ..guest:getName())