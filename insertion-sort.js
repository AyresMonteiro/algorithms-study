const { measureAlgorithm } = require("./measure-algorithm");

function logArrUntilTheIndex(arr, index, isEnd = false) {
  console.log(`[${isEnd ? "E" : "S"}] 0-${index}:`, arr.slice(0, index + 1));
}

function insertionSort(array) {
  for (let i = 1; i < array.length; i++) {
    const val = array[i];

    let j = i - 1;

    for (; j > -1 && array[j] > val; j--) array[j + 1] = array[j];

    array[j + 1] = val;
  }

  return array;
}

function generateArray(length) {
  const array = new Array(length).fill(0);

  array.forEach((_, i) => {
    array[i] = Math.ceil(Math.random() * Number.MAX_SAFE_INTEGER);
  });

  return array;
}

function test() {
  const testLoads = [10, 100, 1_000, 10_000, 100_000, 1_000_000];

  testLoads.forEach((load) => {
    measureAlgorithm(`insertion sort (${load})`, () => {
      const array = generateArray(load);

      insertionSort(array);
    });
  });
}

test();
