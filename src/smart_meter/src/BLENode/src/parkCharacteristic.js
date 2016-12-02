var util = require('util');
var bleno = require('bleno');

var BlenoCharacteristic = bleno.Characteristic;

var ParkCharacteristic = function() {
  ParkCharacteristic.super_.call(this, {
    uuid: 'ec0e',
    properties: ['read', 'write', 'notify'],
    value: null
  });

  var information = {
    "price_per_hour":3.5,
    "limit":2,
    "resolution":60
  }

  this._value = new Buffer(JSON.stringify(information), "utf-8");
  this._updateValueCallback = null;
};

util.inherits(ParkCharacteristic, BlenoCharacteristic);

ParkCharacteristic.prototype.onReadRequest = function(offset, callback) {
  console.log('ParkCharacteristic - onReadRequest: value = ' + this._value.toString("utf-8"));
  callback(this.RESULT_SUCCESS, this._value);
};

/*
ParkCharacteristic.prototype.onWriteRequest = function(data, offset, withoutResponse, callback) {
  this._value = data;
    console.log('ParkCharacteristic - onWriteRequest: value = ' + this._value.toString("utf-8"));

  if (this._updateValueCallback) {
    console.log('ParkCharacteristic - onWriteRequest: notifying');

    this._updateValueCallback(this._value);
  }

  callback(this.RESULT_SUCCESS);
};
*/

module.exports = ParkCharacteristic;