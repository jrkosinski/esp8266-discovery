
var profile = (process.env.PROFILE || ''); 

module.exports = {  
};

function getSetting(key, defaultValue){
    if (profile.length)
        key += '_' + profile;
    
    var value = process.env[key]; 
    if (value === null || value === undefined){
        value = defaultValue;
    }

    return value; 
}

function getBooleanSetting(key, defaultValue){
    var value = getSetting(key, defaultValue ? 'true' : 'false'); 
    return (value == 'true'); 
}

function getArraySetting(key, defaultValue, delimiter){
    if (!delimiter)
        delimiter = ',';
    var value = getSetting(key, '');  
    
    if (value && value.length) {
        return value.split(delimiter); 
    }

    var array = defaultValue.split(delimiter);
    return array;
}

function getLoggingLevel(key, defaultValue) {
    var sValue = getSetting(key, defaultValue);
    var output = sValue.trim().toLowerCase();

    if (sValue != 'all' && sValue != 'none') {
        output = output.split(',');
        for(var i=0; i<output.length; i++)
            output[i] = output[i].trim();
    }

    return output; 
}
