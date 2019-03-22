const repl = require('repl');
const fs = require('fs');

let context = repl.start({}).context;
let path = '/Users/ben/Desktop/dw.pipe';

fs.unlink(path, () => {
  context.dw = require('./ductwork');
  context.dw.create(path);
  context.dw.readString().then((str) => console.log(str));
});
