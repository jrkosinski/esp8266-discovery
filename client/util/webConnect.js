'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var config = require('../config');
var logger = require('../util/logger')('WEB');
var http = require('http'); 

function doRequest(options, onResult)
{
    var req = http.request(options, function(res)
    {
        var output = '';
        console.log(options.host + ':' + res.statusCode);
        res.setEncoding('utf8');

        res.on('data', (chunk) => {
            output += chunk;
        });

        res.on('end', () => {
            var obj = JSON.parse(output);
            onResult(res.statusCode, obj);
        });
    });

    req.on('error', (err) => {
        //res.send('error: ' + err.message);
            onResult(500, null);
    });

    req.end();
};

var pingServer = async(function(ip) {    
    var options = {
        host: ip,
        port: 80,
        path: '/ping',
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    };

    return new Promise((resolve, reject) => {
        var onResult = (code, data) => {
            resolve(code == 200);
        };
        doRequest(options, onResult);
    });
}); 

var sendRequest = async(function(appData) {
    var options = {
        host: appData.ip,
        port: 80,
        path: '/set',
        method: 'GET',
        headers: {
            'Content-Type': 'application/json'
        }
    };
}); 

module.exports = {
    pingServer : pingServer,
    sendRequest : sendRequest
};