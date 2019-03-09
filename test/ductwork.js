const assert = require('assert');
const dw = require('../ductwork');

describe('Ductwork', () => {
  describe('#version()', () => {
    it('should return a string', () => {
      assert.equal(typeof(dw.version()), 'string');
    });
  });

  describe('#hello()', () => {
    it('should return "world"', () => {
      assert.equal(dw.hello(), 'world');
    });
  });
});
