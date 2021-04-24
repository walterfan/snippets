function Task() {
    let priority;

    this.getPriority = () => priority;

    this.setPriority = value => { priority = value;};
}

const task = new Task();
task.setPriority(1);
console.log(task.getPriority());

var name = "walter";

var user = {
    name : "alice",

    getName: function() {
        //var me = this;
        return function() {
            return this.name;
        };
    }

};

console.log(user.getName()()); //undefined