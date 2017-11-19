'use strict';

var async = require('asyncawait/async');
var await = require('asyncawait/await');
var wifi = require('node-wifi');
var logger = require('../util/logger')('WIFI');
var config = require('../config');

var initialized = false;

var scan = async(function() {

    if (!initialized) {
        wifi.init({
            iface : null // network interface, choose a random wifi interface if set to null 
        });
    }

    return new Promise((resolve, reject) => {
        var success = false;
        var ssid = null;
        logger.info('scanning wifi networks...');
        
        //scan networks 
        wifi.scan(function(err, networks) {
            if (err) {
                logger.error(err);
            } else {
                for(var n=0; n<networks.length; n++){
                    var net = networks[n];

                    //match ssid 
                    if (net && net.ssid){
                        if (net.ssid.startsWith('IoThing ')) {
                            ssid = net.ssid;
                            logger.info('found network ' + ssid + '; connecting....');
                        }
                    }
                }
            }
            
            //connect to network 
            if (ssid) {
                //wifi.disconnect(() => {
                    wifi.connect({ ssid : ssid, password : ""}, (err) => {
                        if (err) {
                            logger.error(err);
                            resolve(false);
                        }
                        else {
                            logger.info('connected to ' + ssid);
                            success = true;
                            resolve(true);
                        }
                    });
                //}); 
            }
            else
                resolve(false);
        });
    });
}); 

module.exports = {
    scan : scan
};