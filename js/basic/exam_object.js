var assert = require('assert');

var book0 = {
    title: "reacforing",
    author: "Martin",
    edition: 2,
    toString: function() {
        return `title=${this.title}, author=${this.author}, edition=${this.edition}`;
    }

}
console.log("book0:", book0.toString());

var book1 = new Book("test driven development","Kent", 4);
console.log("book1:", book1.toString());


var book2 = new Book("feature driven development","Unknown", 1);
console.log("book2:", book2.toString());

var book3 = createBook("metrics driven development", "Walter", 1);
console.log("book3:", book3.toString());


function createBook(title, author, edition) {
    var obj = new Object();
    obj.title = title;
    obj.author = author;
    obj.edition = edition;

    obj.getAuthor = function() {
        return this.author;
    }
    obj.setAuthor = function(author) {
        this.author = author;
    }
    obj.toString = function() {
        return `title=${this.title}, author=${this.author}, edition=${this.edition}`;
    }
    return obj;
}


function Book( title, author, edition) {
    this.title = title;
    this.author = author;
    this.edition = edition;

    this.getAuthor = function() {
        return this.author;
    }
    this.setAuthor = function(author) {
        this.author = author;
    }
    this.toString = function() {
        return `title=${this.title}, author=${this.author}, edition=${this.edition}`;
    }
}

function EBook( title, author, edition, url) {
    Book.call(this, title, author, edition);
    this.url = url;

    this.getUrl = function() {
        return this.url;
    }
    this.setUrl = function(url) {
        this.url = url;
    }

    this.toString = function() {
        return `title=${this.title}, author=${this.author}, edition=${this.edition}, url=${this.url}`;
    }
}

Book.prototype.getEdition= function() {
    return this.edition;
}

console.log("book1.constructor: ",book1.constructor)

EBook.prototype = new Book();
ebook1 = new EBook("effective c++", "mayer", 3, "http://t.c");
console.log("ebook1.constructor: ",ebook1.constructor);

Object.defineProperty(EBook.prototype, "constructor", {
    enumrable: false,
    value: EBook,
    writable: true
})
console.log("ebook1.constructor: ",ebook1.constructor);
console.log("ebook1.edition: ", ebook1.getEdition());
console.log("ebook1: ", ebook1.toString());


assert(book1 instanceof Book);
assert(ebook1 instanceof EBook);


class User {
    constructor(name, age) {
        this.name = name;
        this.age = age;
    }

    isAlive() {
        return true;
    }

    static compare(user1, user2) {
        return user1.age - user2.age;
    }
}

var alice = new User("Alice", 20);
console.log("Alice: ", alice);

var bob = new User("Bob", 30);
console.log("Bob: ", bob);

assert(alice.isAlive());
assert(User.compare(alice, bob) < 0);

class Employee extends User {
    constructor(name, age, department) {
        super(name, age);
        this.department = department;
    }

    getDepartment() {
        return this.department;
    }
}

var carl = new Employee("carl", 40, "QA")
console.log("carl: ", carl);