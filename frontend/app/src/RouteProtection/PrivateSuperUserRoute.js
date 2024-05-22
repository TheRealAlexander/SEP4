import React from "react";
import { Navigate, Outlet } from "react-router-dom";

export const isAuthenticated = () => {
    const user = JSON.parse(localStorage.getItem('user'));
    return user && user.role === 'superUser';
};

const PrivateSuperUserRoute = () => {
    return isAuthenticated() ? <Outlet /> : <Navigate to="/unauthorized" />;
}

export default PrivateSuperUserRoute;