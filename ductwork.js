const ext = require('./build/Release/ductwork.node');

const VERSION = '1.0.0';

module.exports = {
  version: () => VERSION,
  hello: ext.hello
};
