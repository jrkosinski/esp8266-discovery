'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var Netcat = require('node-netcat');
var config = require('../config');
var logger = require('../util/logger')('UDP');

var sendUdpBroadcast = async(function() {
    return new Promise((resolve, reject) => {

        var options = {
            timeout: 3000,
            // buffer, ascii, hex,utf8, base64
            read_encoding: 'ascii'
        }; 

        var client = Netcat.udpClient(8021, '127.0.0.1', [options]);

        client.on('message', (msg) => {
            resolve(JSON.parse(msg)); 
        });

        client.once('close', () => {
            resolve(null); 
        });

        client.once('open', () => {
            logger.info('open');
            client.send('hellos');
        });

        client.once('error', (err) => {
            resolve(null); 
        });

        client.send('hellos');

        setTimeout(() => {
            logger.info("timed out");
            client.close();
        }, 10000); 
    });
}); 

module.exports = {
    sendUdpBroadcast : sendUdpBroadcast
};