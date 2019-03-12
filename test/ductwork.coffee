assert = require 'assert'
dw = require '../ductwork'
fs = require 'fs'
chai = require 'chai'

chai.should()

describe 'Ductwork', ->
  # Windows should prepend "//./pipes" to this
  desiredPath = "/tmp/#{Math.random()}.fifo"
  actualPath = null
###
  afterEach -> 
    fs.unlink(actualPath) if (fs.existsSync(actualPath))
    actualPath = null
###
  describe '#create(path)', ->
    it 'should create a pipe and return the actual path to it', ->
      actualPath = dw.create desiredPath 
      fs.existsSync(actualPath).should.be.true

  describe '#modes.READ', ->
    it 'should return "read"', -> dw.modes.READ.should.equal 'read'

  describe '#modes.WRITE', ->
    it 'should return "write"', -> dw.modes.WRITE.should.equal 'write'

  describe '#modes.READ_WRITE', ->
    it 'should return "read"', -> dw.modes.READ_WRITE.should.equal 'read_write'

  describe '#wait(path, mode)', ->
    #beforeEach -> actualPath = dw.create desiredPath

    it 'should return a Promise', -> 
      dw.wait(actualPath, dw.modes.READ).should.be.a 'Promise'
