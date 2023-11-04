function measureAlgorithm(label, fn) {
  console.time(label);

  fn();

  console.timeEnd(label);
}

module.exports = { measureAlgorithm };
