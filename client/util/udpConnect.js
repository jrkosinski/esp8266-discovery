'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var config = require('../config');

var sendUdpBroadcast = async(function() {
    return { ip: '192.168.1.1'}; 
}); 

module.exports = {
    sendUdpBroadcast : sendUdpBroadcast
};