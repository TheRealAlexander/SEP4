import React from "react";
import { Navigate, Outlet } from "react-router-dom";

export const isAuthenticated = () => {
  const user = JSON.parse(localStorage.getItem("user"));
  return !!user;
};

const PrivateRoute = () => {
  return isAuthenticated() ? <Outlet /> : <Navigate to="/login" />;
};

export default PrivateRoute;
