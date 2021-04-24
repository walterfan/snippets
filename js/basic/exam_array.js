const users = ["alice", "bob", "carl", "david"];
users.push("elain");
users.unshift("walter");
console.log("users: ", users);
users.pop();
users.shift();
console.log("users: ", users);

users[1000] = "finance";
console.log("users length: ", users.length);
console.log("--------- users ------------");
for(var i=0, len=users.length; i < len; i++) {
    if(users[i] === undefined) {
        continue;
    }
    console.log(i, "=>", users[i]);
}

console.log("--------- departments ------------");
//array contains any type
const departments = new Array("dev", "qa", "ops", 1.0, 2, []);

console.log(departments);
//no array boundary
console.log(users[10]); //print undefined
