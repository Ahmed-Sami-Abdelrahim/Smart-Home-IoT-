import React, { useState, useEffect } from 'react';
import axios from 'axios';
import DeviceForm from './components/DeviceForm';
import DeviceCard from './components/DeviceCard';
import Weather from './components/Weather';
import Header from './components/Header';
import './App.css';

// Import Raspberry pi 
import { API_BASE_URL, RASPBERRY_PI_IP ,RASPBERRY_PI_PORT, RASPBERRY_PI_URL } from './config'; 

const App = () => {
  const [devices, setDevices] = useState([]);

  // Fetch devices from the backend API
  const fetchDevices = async () => {
    try {
      const response = await axios.get(`${API_BASE_URL}/devices`);
      setDevices(response.data);
    } catch (error) {
      console.error('Error fetching devices:', error);
    }
  };

  // Fetch devices on component mount and set up polling
  useEffect(() => {
    fetchDevices(); // Initial fetch
    const intervalId = setInterval(fetchDevices, 1000); // Poll every 1 second

    return () => clearInterval(intervalId);
  }, []);

  // Add a new device
  const addDevice = async (device) => {
    try {
      const response = await axios.post(`${API_BASE_URL}/devices`, device);
      setDevices((prevDevices) => [...prevDevices, response.data]);
    } catch (error) {
      console.error('Error adding device:', error);
    }
  };

  // Delete a device
  const handleDelete = async (identifier) => {
    try {
      await axios.delete(`${API_BASE_URL}/devices/${identifier}`);
      setDevices((prevDevices) => prevDevices.filter((device) => device.identifier !== identifier));
    } catch (error) {
      console.error('Error deleting device:', error);
    }
  };

  // Toggle the status of a device and update the HW target "Raspberry Pi"
  const handleToggleStatus = async (identifier, currentStatus) => {
    const newStatus = currentStatus === 'on' ? 'off' : 'on';
    try {
      const response = await axios.put(`${API_BASE_URL}/devices/${identifier}`, { status: newStatus });
      const updatedDevice = response.data;

      // Update local state
      setDevices((prevDevices) =>
        prevDevices.map((device) =>
          device.identifier === identifier ? { ...device, status: updatedDevice.status } : device
        )
      );

      // Prepare payload with identifier, name, and status
      const payload = JSON.stringify({
        identifier: updatedDevice.identifier,
        name: updatedDevice.name,
        status: updatedDevice.status
      });

      // Send updated status to Raspberry Pi
      try {
        await axios.post(RASPBERRY_PI_URL, payload);
        console.log('Successfully sent status update to Raspberry Pi');
      } catch (error) {
        console.error('Error sending status to Raspberry Pi:', error);
      }

    } catch (error) {
      console.error('Error toggling device status:', error);
    }
  };

  return (
    <div className="app">
      <Header />
      <div className="content">
        <DeviceForm addDevice={addDevice} />
        <div className="device-container">
          {devices.length === 0 ? (
            <p className="no-devices">No devices available</p>
          ) : (
            devices.map((device) => (
              <DeviceCard
                key={device.identifier}
                identifier={device.identifier}
                name={device.name}
                status={device.status}
                onDelete={() => handleDelete(device.identifier)}
                onToggleStatus={() => handleToggleStatus(device.identifier, device.status)}
              />
            ))
          )}
        </div>
      </div>
      <Weather />
    </div>
  );
};

export default App;
