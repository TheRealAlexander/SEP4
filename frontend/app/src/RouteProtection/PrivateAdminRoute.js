import React from 'react';
import { Navigate, Outlet } from 'react-router-dom';

const isAdmin = () => {
  const user = JSON.parse(localStorage.getItem('user'));
  return user && user.role === 'admin';
};

const PrivateAdminRoute = () => { // Redirect to the unauthorized page if the user is not an admin TODO: Create the unauthorized page
  return isAdmin() ? <Outlet /> : <Navigate to="/unauthorized" />; 
};

export default PrivateAdminRoute;