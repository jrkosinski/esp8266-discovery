'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var dgram = require('dgram'); 
var config = require('../config');
var logger = require('../util/logger')('UDP');

var sendUdpBroadcast = async(function() {
    return new Promise((resolve, reject) => {
        var client = dgram.createSocket("udp4");
        await(client.bind(1212)); 
        client.setBroadcast(true);
        var message = "hello"; 
        logger.info('sending...');
        client.send(message, 0, message.length, 8021, "239.255.255.250");

        client.on('message', (data) => {
            var msg = new Buffer(data).toString('ascii');
            resolve(JSON.parse(msg)); 
        });

        client.once('close', () => {
            resolve(null); 
        });

        client.once('error', (err) => {
            resolve(null); 
        });

        setTimeout(() => {
            logger.info("timed out");
            client.close();
        }, 10000); 
    });
}); 

module.exports = {
    sendUdpBroadcast : sendUdpBroadcast
};