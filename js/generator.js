function* IdGenerator() {
    let id = 0;
    while(true) {
        yield ++id;
    }
}

function* DomTraversal(element) {
    yield element;

    element = element.firstElementChild;
    while(element) {
        yield* DomTraversal(element);
        element = element.nextElementSibling;
    }
}