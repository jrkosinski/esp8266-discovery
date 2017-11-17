'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var config = require('../config');

var getAppData = async(function() {
    return { ssid: 'mina', password:'HappyTime'};
}); 

var saveAppData = async(function(appData) {
}); 

module.exports = {
    getAppData : getAppData,
    saveAppData : saveAppData
};