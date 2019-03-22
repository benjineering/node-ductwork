assert = require 'assert'
dw = require '../ductwork'
fs = require 'fs'
chai = require 'chai'

chai.should()

describe 'Ductwork', ->

  # Windows should prepend "//./pipes" to this
  desiredPath = "/tmp/#{Math.random()}.fifo"
  actualPath = null

  afterEach -> 
    fs.unlinkSync(actualPath) if (fs.existsSync(actualPath))
    actualPath = null

  describe '#create(path)', ->
    it 'should create a pipe and return the actual path to it', ->
      actualPath = dw.create desiredPath 
      fs.existsSync(actualPath).should.be.true

  describe '#readString()', ->
    beforeEach -> actualPath = dw.create desiredPath

    it 'should return a promise', ->
      dw.readString().should.be.a 'Promise'
