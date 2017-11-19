var handler = require ('../index');
var config = require('../config');
var debug = require('debug');
var async = require('asyncawait/async');
var await = require('asyncawait/await');

describe('Unit Tests', function() {
    beforeEach(function (done) {
        setTimeout(function() {
            done();
        }, 0);
    });

    afterEach(function () {
    });

    it('x', function (done) {
        this.timeout(10000);

    });
});