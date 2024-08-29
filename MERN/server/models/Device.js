const mongoose = require('mongoose');

const deviceSchema = new mongoose.Schema({
  identifier: {
    type: String,
    required: true,
    unique: true,
    validate: {
      validator: function(v) {
        return /^\d+$/.test(v); // Ensure identifier is numeric
      },
      message: props => `${props.value} is not a valid ID!`
    }
  },
  name: {
    type: String,
    required: true,
  },
  status: {
    type: String,
    enum: ['on', 'off'],
    default: 'off',
  },
});

module.exports = mongoose.model('Device', deviceSchema);
