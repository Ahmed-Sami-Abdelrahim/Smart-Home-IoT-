import React from 'react';
import PropTypes from 'prop-types';

const DeviceCard = ({ identifier, name, status, onDelete, onToggleStatus }) => {
  // Check if the device name is missing, and display an error message if so
  if (!name) {
    return <div>Error: Device name is missing.</div>;
  }

  // Determine the text color based on the device's status
  const statusColor = status === 'on' ? 'green' : 'red';

  return (
    <div className="device-card">
      {/* Display the device name */}
      <h3>{name}</h3>
      {/* Display the device identifier */}
      <p>ID: {identifier}</p>
      {/* Display the device status with the appropriate color */}
      <p style={{ color: statusColor }}>Status: {status}</p>
      {/* Button to toggle the device status */}
      <button onClick={onToggleStatus}>
        {status === 'on' ? 'Turn Off' : 'Turn On'}
      </button>
      {/* Button to delete the device, styled with a red background */}
      <button onClick={onDelete} style={{ marginTop: '10px', backgroundColor: 'red' }}>
        Delete
      </button>
    </div>
  );
};

// Define prop types for the component to ensure correct usage
DeviceCard.propTypes = {
  identifier: PropTypes.string.isRequired,  
  name: PropTypes.string.isRequired,        
  status: PropTypes.string.isRequired,      
  onDelete: PropTypes.func.isRequired,      
  onToggleStatus: PropTypes.func.isRequired 
};

export default DeviceCard;
