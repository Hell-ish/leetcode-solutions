/**
 * @param {Generator} generator
 * @return {[Function, Promise]}
 */
var cancellable = function(generator) {
    let cancelled = false;

    let cancel = () => {
        cancelled = true;
    };

    const promise = new Promise((resolve, reject) => {
        function run(method, arg) {
            let result;

            try {
                result = method.call(generator, arg);
            } catch (err) {
                reject(err);
                return;
            }

            if (result.done) {
                resolve(result.value);
                return;
            }

            Promise.resolve(result.value).then(
                val => {
                    if (!cancelled) run(generator.next, val);
                },
                err => {
                    if (!cancelled) run(generator.throw, err);
                }
            );
        }

        cancel = () => {
            if (cancelled) return;
            cancelled = true;
            run(generator.throw, "Cancelled");
        };

        run(generator.next);
    });

    return [cancel, promise];
};