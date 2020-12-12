exam = require("./exam.js");

exam.print("----- true or false ---------");

exam.printBoolean(undefined);
exam.printBoolean(null);
exam.printBoolean(NaN);
exam.printBoolean('');
exam.printBoolean(false);
exam.printBoolean([]);
exam.printBoolean({});


exam.print("----- equals or not ---------");
exam.print('1 == "1"=', 1 == "1");
exam.print('1 === "1"=', 1 === "1");

