const dw = require('./build/Release/ductwork.node');

dw.modes = {
  READ: 'read',
  WRITE: 'write',
  READ_WRITE: 'read_write'
};

module.exports = dw;
