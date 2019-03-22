const dw = require('./build/Release/ductwork.node');

dw.readString = () => {
  return new Promise((resolve, reject) => {
    let result = dw.readStringSync();

    if (result === null)
      reject('timeout');
    else
      resolve(result);
  });
};

module.exports = dw;
