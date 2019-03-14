const repl = require('repl');

repl.start({}).context.dw = require('./ductwork')
