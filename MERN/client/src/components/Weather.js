import React, { useState } from 'react';
import axios from 'axios';
import { WEATHER_API_KEY } from '../config'; // Import the API key from the config file

const Weather = () => {
  // State to keep track of the city input by the user
  const [city, setCity] = useState('');
  // State to store the weather data fetched from the API
  const [weather, setWeather] = useState(null);
  // State to handle and display error messages
  const [error, setError] = useState('');

  // Function to fetch weather data based on the city name
  const fetchWeather = async (cityName) => {
    try {
      // Make an API call to the OpenWeatherMap API to get weather data
      const response = await axios.get(
        `http://api.openweathermap.org/data/2.5/weather?q=${cityName}&appid=${WEATHER_API_KEY}`
      );
      // Update the weather state with the data received from the API
      setWeather(response.data);
      setError(''); // Clear any previous errors
    } catch (error) {
      console.error("Error fetching the weather data:", error);
      // If an error occurs (e.g., city not found), reset the weather data and set an error message
      setWeather(null);
      setError('City not found. Please try again.');
    }
  };

  // Handler function to update the city state when the input changes
  const handleCityChange = (e) => {
    setCity(e.target.value);
  };

  // Handler function to submit the form and fetch the weather for the entered city
  const handleCitySubmit = (e) => {
    e.preventDefault(); // Prevent the default form submission behavior
    if (city) {
      fetchWeather(city); // Fetch weather data for the city entered by the user
    }
  };

  return (
    <div className="weather">
      <form onSubmit={handleCitySubmit}>
        {/* Input field for the user to enter a city name */}
        <input
          type="text"
          placeholder="Enter city"
          value={city}
          onChange={handleCityChange}
          required
        />
        {/* Button to submit the form and get the weather */}
        <button type="submit">Get Weather</button>
      </form>
      {/* Display error message if there is one */}
      {error && <p className="error-message">{error}</p>}
      {/* If weather data is available, display it; otherwise, show a default message */}
      {weather ? (
        <div>
          <h3>Weather in {weather.name}</h3>
          <p>{weather.weather[0].description}</p>
          <p>Temperature: {Math.round(weather.main.temp - 273.15)}°C</p>
        </div>
      ) : (
        !error && <p>Enter a city to get the weather.</p>
      )}
    </div>
  );
};

export default Weather;
