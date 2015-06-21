var a = 1;
function foo()
{
	var b = 2;
	g = 3;
	var f = function() 
	{
		var c = 4;
		return a+b+c;
	};
	f();
}

function foreach(list , func)
{
    while(list)
    {
        func(list.val)
        list=list.next;
    }
}

var list = null;
for(var i=0;i<4;i++)
{
    list = {var: i, next: list}
}

var i=0;
// the inner anonymous function can access the outter variable i
foreach(list, function(n){ console.log("node(" + i + ")=" + n); i++;});

function extent()
{
    var n = 0;
    return function(){
        n++;
        console.log("n="+n);
    }
}

f = extent();
f(); //n=1
f(); //n=2


//so, closure is a close environment structure that contain local variable 

function extend()
{
    return {
        val: 0,
        call: function() {
            this.val ++;
            console.log("val="+this.val);
        }
        }
}

f = extend();
f.call(); //val = 1
f.call(); //val = 2


