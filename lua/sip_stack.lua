--[[
	simple SIP stack of Lua for testing
	
--]]

-- Method constants
SIP_Method = {
 	ACK = "ACK",
	INVITE = "INVITE",
	OPTIONS = "OPTIONS",
	REGISTER = "REGISTER",
}

-- SIP Response code constants
SIP_Response = {
	TRYING = 100,
	RING = 180,
	TIMEOUT = 408,
	BUSY = 486,
	DECLINE = 603,
	OK = 200,
	UNAUTHORIZED = 401,
	FORBIDDEN = 403,
	NOTFOUND = 404,
	PROXY_AUTH_REQUIRED = 407,
}



