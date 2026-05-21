/**
 * @param {Array<Function>} functions
 * @return {Promise}
 */
var promiseAll = function(functions) {
    return new Promise((resolve, reject) => {
        const results = new Array(functions.length);
        let completed = 0;

        for (let i = 0; i < functions.length; i++) {
            functions[i]()
                .then(value => {
                    results[i] = value;
                    completed++;

                    if (completed === functions.length) {
                        resolve(results);
                    }
                })
                .catch(error => {
                    reject(error);
                });
        }
    });
};