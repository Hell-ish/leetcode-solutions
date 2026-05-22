/**
 * @param {Object} obj
 * @param {...any} args
 * @return {any}
 */
Function.prototype.callPolyfill = function(obj, ...args) {
    const uniqueKey = Symbol();

    obj[uniqueKey] = this;

    const result = obj[uniqueKey](...args);

    delete obj[uniqueKey];

    return result;
};