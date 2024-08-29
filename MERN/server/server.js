const express = require('express');
const mongoose = require('mongoose');
const cors = require('cors');
const Device = require('./models/Device'); // Adjust path as needed
require('dotenv').config();


const app = express();
app.use(cors());
app.use(express.json());


// MongoDB connection
mongoose.connect(process.env.MONGODB_URI, {
  useNewUrlParser: true,
  useUnifiedTopology: true,
})
  .then(() => console.log('Connected to MongoDB'))
  .catch(err => console.error('Failed to connect to MongoDB', err));

// Routes

// Get all devices
app.get('/devices', async (req, res) => {
  try {
    const devices = await Device.find();
    res.json(devices);
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
});

// Add a new device
app.post('/devices', async (req, res) => {
  const { identifier, name, status } = req.body;

  if (!['on', 'off'].includes(status)) {
    return res.status(400).json({ message: 'Invalid status value. Use "on" or "off".' });
  }

  try {
    const existingDevice = await Device.findOne({ identifier });
    if (existingDevice) {
      return res.status(400).json({ message: 'Device with this ID already exists.' });
    }

    const device = new Device({
      identifier,
      name,
      status: status || 'off', // Default to 'off' if status is not provided
    });

    await device.save();
    res.status(201).json(device);
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
});

// Update a device
app.put('/devices/:identifier', async (req, res) => {
  const { identifier } = req.params;
  const { status } = req.body;

  if (!['on', 'off'].includes(status)) {
    return res.status(400).json({ message: 'Invalid status value. Use "on" or "off".' });
  }

  try {
    const updatedDevice = await Device.findOneAndUpdate(
      { identifier },
      { status },
      { new: true }
    );

    if (!updatedDevice) {
      return res.status(404).json({ message: 'Device not found' });
    }

    res.json(updatedDevice);
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
});

// Delete a device
app.delete('/devices/:identifier', async (req, res) => {
  const { identifier } = req.params;

  try {
    const deletedDevice = await Device.findOneAndDelete({ identifier });

    if (!deletedDevice) {
      return res.status(404).json({ message: 'Device not found' });
    }

    res.json({ message: 'Device deleted successfully' });
  } catch (error) {
    res.status(500).json({ message: error.message });
  }
});

// Start server
const PORT = process.env.PORT || 5000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
