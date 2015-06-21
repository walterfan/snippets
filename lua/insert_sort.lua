-----------------------------------------------------------------------------
--  This is a test program when I learn Lua.
--
--  (c) 2013 Walter Fan
--
--  License: MIT
-----------------------------------------------------------------------------

MIN_ARR_IDX = 1

-----------------------------------------------------------------------------
-- sort a table as insertion sort method
--
-- @param arr       the table that unsorted
--
-- @return  sorted table
-----------------------------------------------------------------------------
function insert_sort(arr, isDesc)
  local i,j,k
  local nLen = #arr

  if nLen == 1 then
    return arr
  end

  for i = MIN_ARR_IDX + 1, nLen do
    local tmp = arr[i]

    for j = i, MIN_ARR_IDX + 1, -1 do
        if isDesc then
		  if tmp < arr[j - 1] then break end
		else
		  if tmp > arr[j - 1] then break end
		end
        arr[j] = arr[j-1]
        arr[j-1] = tmp
    end

	--for k = 1, nLen  do
    --   print(arr[k])
    --end
  end
  return arr
end

-----------------------------------------------------------------------------
--
-- test method of insertion sort method
--
-----------------------------------------------------------------------------
function insert_sort_test()
    local i = MIN_ARR_IDX
    local arr = {34,8,64,51,32,21}
	local nLen = #arr
    print('--- unsorted table ---')
	for i = MIN_ARR_IDX, nLen  do
       print(arr[i])
    end
	insert_sort(arr)

	print('--- sorted table asc---')
    for i = MIN_ARR_IDX, nLen  do
       print(arr[i])
    end

	insert_sort(arr, true)
	print('--- sorted table desc---')
    for i = MIN_ARR_IDX, nLen  do
       print(arr[i])
    end
end

insert_sort_test()
