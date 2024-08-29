
import React from 'react';
import './Header.css';


const Header = () => {
  return (
    <header>
      <div className="header-left">
        <div className="logo"></div> 
        <div className="title">Smart Home</div>
      </div>
      <div className="header-right">
        <div className="icon1"></div> 
        <div className="icon2"></div> 
        <div className="icon3"></div> 
        <div className="icon4"></div> 
        <div className="icon5"></div> 
        <div className="icon6"></div> 
      </div>
    </header>
  );
};

export default Header;
