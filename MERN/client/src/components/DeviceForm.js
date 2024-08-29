import React, { useState } from 'react';
import axios from 'axios';
import { API_BASE_URL } from '../config'; // Import API base URL from the config file

const DeviceForm = ({ addDevice }) => {
  const [name, setName] = useState(''); // State for device name
  const [identifier, setIdentifier] = useState(''); // State for device identifier
  const [error, setError] = useState(''); // State for error messages

  // Validate if the value is numeric
  const isNumeric = (value) => /^\d+$/.test(value);

  // Handle form submission
  const handleSubmit = async (e) => {
    e.preventDefault(); // Prevent default form submission

    // Validate device identifier
    if (!isNumeric(identifier)) {
      setError('Device ID must be a number.'); // Set error if identifier is not numeric
      return;
    }

    try {
      // POST request to add a new device
      const response = await axios.post(`${API_BASE_URL}/devices`, { name, identifier, status: 'off' });
      addDevice(response.data); // Pass the new device to the parent component
      setName(''); // Clear name input
      setIdentifier(''); // Clear identifier input
      setError(''); // Clear error messages
    } catch (error) {
      // Handle API errors
      if (error.response && error.response.status === 400) {
        setError(error.response.data.message); // Set error message from server response
      } else {
        setError('An error occurred. Please try again.'); // Generic error message
      }
    }
  };

  return (
    <div className="device-form-container">
      <h2>Add New Device</h2>
      <form onSubmit={handleSubmit} className="device-form">
        <input
          type="text"
          placeholder="Device Name"
          value={name}
          onChange={(e) => setName(e.target.value)} // Update name state
          required
        />
        <input
          type="text"
          placeholder="Device ID (numeric)"
          value={identifier}
          onChange={(e) => setIdentifier(e.target.value)} // Update identifier state
          required
        />
        <button type="submit">Add Device</button>
        {error && <p className="error-message">{error}</p>} {/* Display error message */}
      </form>
    </div>
  );
};

export default DeviceForm;
