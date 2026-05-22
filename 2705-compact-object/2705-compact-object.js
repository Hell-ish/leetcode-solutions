/**
 * @param {Object|Array} obj
 * @return {Object|Array}
 */
var compactObject = function(obj) {
    // Base case: primitive values
    if (obj === null || typeof obj !== "object") {
        return obj;
    }

    // Handle arrays
    if (Array.isArray(obj)) {
        return obj
            .filter(Boolean)
            .map(item => compactObject(item));
    }

    // Handle objects
    const result = {};

    for (const key in obj) {
        if (Boolean(obj[key])) {
            result[key] = compactObject(obj[key]);
        }
    }

    return result;
};