'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var Storage = require('node-storage');
var config = require('../config');

var getAppData = async(function() {
    var file = new Storage('fs/data.js');
    var json = await(file.get('json'));
    if (json && json.length)
        return JSON.parse(json);
    
    return null;
}); 

var saveAppData = async(function(appData) {
    var file = new Storage('fs/data.js');
    await(file.put('json', JSON.stringify(appData)));
    return appData;
}); 

module.exports = {
    getAppData : getAppData,
    saveAppData : saveAppData
};